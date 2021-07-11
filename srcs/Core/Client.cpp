#include "Client.hpp"

Client::Client(){
	Client::init_client();
};

Client::Client(Server *serv, int fd, struct sockaddr_in addr_info){
	this->client_fd = fd;
	this->addr_info = addr_info;
	// this->time = time(0);
}

Client::~Client(){};

time_t		Client::get_time(){
	return time;
}

int			Client::get_fd(){
	return client_fd;
}

void	Client::init_client(){
	char message[1024];
	// struct sockaddr_in addr;
	char buf[1024];
	int read_bytes = 0;

	this->client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->client_fd < 0) {
		perror("socket");
		exit(1);
	}
	addr_info.sin_family = AF_INET;
	addr_info.sin_port = htons(3425);
	addr_info.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (connect(this->client_fd, (struct sockaddr*)&addr_info, sizeof(addr_info)) < 0) {
		perror("connect");
		exit(2);
	}
	
	std::string str;
	while (true) {
		std::cin >> str;
		strcpy(message, str.c_str());
		send(this->client_fd, message, sizeof(message), 0);
		recv(this->client_fd, buf, 1024, 0);
		std::cout << "Server answer: " << buf << std::endl;
	}
	close(this->client_fd); //возможно перенести в отдельную функцию
	return ;
}

int		main(){
	Client();
	return 0;
}