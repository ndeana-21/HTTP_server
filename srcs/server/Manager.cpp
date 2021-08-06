#include "server/Manager.hpp"

Manager::Manager(Data *data) {
	_data = data;
	_cgi = new Cgi();
	_request = new Request(_data);
	_response = new Response(_data, _cgi);
	_server = &data->getServers();
	FD_ZERO(&_readSet);
	FD_ZERO(&_writeSet);
	_funcMap.insert(std::make_pair(action::e_recvHeaders, &Manager::recvHeaders));
	_funcMap.insert(std::make_pair(action::e_recvContentBody, &Manager::recvContentBody));
	_funcMap.insert(std::make_pair(action::e_recvChunkBody, &Manager::recvChunkBody));
	_funcMap.insert(std::make_pair(action::e_sendResponse, &Manager::sendResponse));
}

Manager::Manager(const Manager &other):	_data(other._data),
										_cgi(other._cgi),
										_request(other._request),
										_response(other._response),
									   	_server(other._server),
									   	_clients(other._clients),
									   	_readSet(other._readSet),
									  	_writeSet(other._writeSet),
										_funcMap(other._funcMap) {}

Manager &Manager::operator=(const Manager &other) {
	if (this != &other) {
		_data = other._data;
		_cgi = other._cgi;
		_request = other._request;
		_response = other._response;
		_server = other._server;
		_clients = other._clients;
		_readSet = other._readSet;
		_writeSet = other._writeSet;
		_funcMap = other._funcMap;
	}
	return (*this);
}

Manager::~Manager() {
	delete _cgi;
	delete _request;
	delete _response;
	for (Client::_clientIt clientIt = _clients.begin(); clientIt != _clients.end();)
		closeConnection(clientIt);
}

int& Manager::getSignal() {
	static int signal = 0;
	return (signal);
}

void Manager::signalCtrlC(int signal) {
	if (signal == SIGINT)
	{
		getSignal() = signal;
		std::cout << "\b\bClosing webserv!" << std::endl;
	}
}

void Manager::signalMain() {
	signal(SIGINT, signalCtrlC);
}

void Manager::recvHeaders(Client *client) {
	_request->recvHeaders(client);
}

void Manager::recvContentBody(Client *client) {
	_request->recvContentBody(client);
}

void Manager::recvChunkBody(Client *client) {
	_request->recvChunkBody(client);
}

void Manager::sendResponse(Client *client) {
	_response->sendResponse(client);
}

void Manager::closeConnection(Client::_clientIt &clientIt) {
	if (ft::getDebug())
		std::cout << "close = " << (*clientIt)->_socket << std::endl;

	if (close((*clientIt)->_socket) == -1)
		TraceException("close failed");
	delete *clientIt;
	_clients.erase(clientIt++);
}

void Manager::initSet(Client *client) {
	if (client->_flag == action::e_sendResponse)
		FD_SET(client->_socket, &_writeSet);
	else
		FD_SET(client->_socket, &_readSet);
}

int Manager::runWebserver() {
	Client *client;
	const std::string *host;
	struct sockaddr_in	listenAddr,
						acptAddr;
	socklen_t addrlen = sizeof(listenAddr);
	int	listenSocket,
		acceptSocket,
		clientSocket,
		clientFlag,
		tmp,
		reuse = 1,
		maxSocket = -1;
	long port;
	timeval	selectTimeout;
	selectTimeout.tv_sec = 1;
	selectTimeout.tv_usec = 0;

	for (Server::_svrsType::const_iterator it = _server->begin(); it != _server->end();) {
		port = it->_listenPort;
		host = &it->_host;

		memset(&listenAddr, '\0', sizeof(sockaddr_in));
		listenAddr.sin_family = AF_INET;
		listenAddr.sin_addr.s_addr = *host == "localhost" ? INADDR_ANY : inet_addr((*host).c_str());
		listenAddr.sin_port = htons(port);

		try {
			if (((listenSocket) = socket(AF_INET, SOCK_STREAM, 0)) == -1)
				TraceException("socket failed");
			if ((fcntl(listenSocket, F_SETFL, O_NONBLOCK)) == -1)
				TraceException("fcntl failed");
			if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
				TraceException("setsockopt failed");
			if (bind(listenSocket, (struct sockaddr *) &listenAddr, sizeof(listenAddr)) == -1)
				TraceException("bind failed");
			if (listen(listenSocket, SOMAXCONN) == -1)
				TraceException("listen failed");
			_clients.push_back(new Client(&*it, listenSocket, action::e_listenSocket));
			_clients.back()->_listenAddr = listenAddr;
			it++;
		}
		catch (std::runtime_error &runtimeError) {
			std::cerr << "runtimeError: " << runtimeError.what() << std::endl;
			sleep(1);
		}
		if (getSignal() == SIGINT)
			break;
	}

	while (true)
	{
		FD_ZERO(&_readSet);
		FD_ZERO(&_writeSet);

		for (Client::_clientIt clientIt = _clients.begin(); clientIt != _clients.end();) {
			try {
				if ((*clientIt)->_flag == action::e_closeConnection ||
					((*clientIt)->_flag != action::e_listenSocket && (*clientIt)->isTimeout()))
					closeConnection(clientIt);
				else
					clientIt++;
			}
			catch (std::runtime_error &runtimeError) {
				std::cerr << "runtimeError: " << runtimeError.what();
			}
		}

		for (Client::_clientIt clientIt = _clients.begin(); clientIt != _clients.end(); clientIt++) {
			tmp = (*clientIt)->_socket;
			maxSocket = std::max(tmp, maxSocket);
			initSet(*clientIt);
		}
		
		if (select(maxSocket + 1, &_readSet, &_writeSet, NULL, &selectTimeout) == -1)
			continue;

		for (Client::_clientIt clientIt = _clients.begin(); clientIt != _clients.end(); clientIt++) {
			client = (*clientIt);
			clientSocket = client->_socket;
			clientFlag = client->_flag;

			if (clientFlag == action::e_listenSocket) {
				if (FD_ISSET(clientSocket, &_readSet)) {
					if ((acceptSocket = accept(clientSocket, (struct sockaddr *)&acptAddr, &addrlen)) == -1)
						continue;
					else {
						_clients.push_back(new Client(client->_acptSvr, acceptSocket, action::e_recvHeaders));
						_clients.back()->_acptAddr = acptAddr;
						if (fcntl(acceptSocket, F_SETFL, O_NONBLOCK) == -1)
							_clients.back()->_flag = action::e_closeConnection;
					}
				}
			}
			else {
				if (FD_ISSET(clientSocket, &_readSet) ||
					FD_ISSET(clientSocket, &_writeSet)) {
					try {
						(this->*_funcMap.find(clientFlag)->second)(*clientIt);
					}
					catch (HttpStatusCode &httpStatusCode) {
						client->_httpStatusCode = httpStatusCode;
						client->_flag = action::e_sendResponse;
					}
					catch (std::exception &exception) {
						std::cerr << "Exception : " << exception.what() << std::endl;
						client->_flag = action::e_closeConnection;
					}
				}
			}
		}
		if (getSignal() == SIGINT)
			break;
	}
	return (0);
}

void Manager::launchManager() {
	while (true) {
		try {
			Data data;
			data.parseMimeTypes();
			data.parseConfiguration();
			Cgi cgi;
			Manager manager(&data);

			signalMain();

			std::cout << "Enter Ctrl-C to exit" << std::endl;
			manager.runWebserver();
		}
		catch (std::exception &exception) {
			std::cerr << "Exception : " << exception.what() << std::endl;
			sleep(1);
		}
		if (getSignal() == SIGINT)
			break;
	}
}
