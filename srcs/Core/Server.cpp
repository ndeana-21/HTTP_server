/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:12:23 by gselyse           #+#    #+#             */
/*   Updated: 2021/07/12 21:17:09 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(){
	Server::setup_server();
	// Server::accept_client();
	Server::run_server();
}

Server::Server(Server const &copy){
	*this = copy;
}

Server::~Server(){}

int		Server::get_fd(){
	return this->server_fd;
}

std::string		Server::get_name(){
	return this->server_name;
}


void	Server::setup_server(){
	this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_fd < 0) {
		perror("socket");
		exit(1);
	}
	else{
		std::cout << "Socket created\n";
		std::cout << "Socket fd " << get_fd() << std::endl;
	}
	int reuse = 1;
	setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	fcntl(this->server_fd, F_SETFL, O_NONBLOCK); //делаем сокет неблокирующим
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(3425);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(this->server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("bind");
		exit(2);
	}
	if (listen(this->server_fd, 1000) < 0){
		perror("listen");
		close(this->server_fd);
		exit(1);
	}
}

void		Server::run_server(){
	int bytes_read;
	char buf[1024] = {'\0'};
	std::set<int> servers;
	std::set<int> clients;
	// clients.clear();

	while (true) {
		// std::cout << "Hello server" << std::endl;
		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(this->server_fd, &readset);

		for (std::set<int>::iterator it = clients.begin(); it != clients.end(); it++) {
			FD_SET(*it, &readset);
		}
		timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		int mx = std::max(this->server_fd, *std::max_element(clients.begin(), clients.end()));
		if (select(mx + 1, &readset, NULL, NULL, &timeout) < 0) {
			perror("select");
			clients.clear();
			exit(3);
		}
		for (std::set<int>::iterator it = servers.begin(); it != servers.end(); it++){
			if (FD_ISSET(this->server_fd, &readset)){
				int sock = accept_client();
				clients.insert(sock);
				break ;
			}
		}
		for (std::set<int>::iterator it = clients.begin(); it != clients.end();) { //socket_read + request
			if (FD_ISSET(*it, &readset)) { 
				std::cout << "Connection" << std::endl;
				// bytes_read = recv(*it, buf, 1024, 0);
				bytes_read = read_socket();	//получили данные от клиента, читаем их
				if (bytes_read <= 0) {
					close(*it);							//соединение разорвано, закрываем
					clients.erase(it++);
					continue;
				}
				else {
					std::cout << buf << "\n";
					send(*it, buf, bytes_read, 0);
					break ;
				}
				
			}
			++it;
		}
	}
	std::cout << "Connection" << std::endl;
	return ;
}

int		Server::accept_client(){
	struct sockaddr_in new_addr;
	socklen_t len_newaddr = sizeof(sockaddr_in);
	int new_fd;
	std::cout << "New connection";
	if ((new_fd = accept(this->get_fd(), (struct sockaddr *)&new_addr, &len_newaddr))){
		perror("accept");
		exit(1);
	}
	else{
		std::cout << "Connection accepted" << std::endl;
		std::cout << "Client fd " << new_fd << std::endl;
	}
	fcntl(new_fd, F_SETFL, O_NONBLOCK);
	return new_fd;
}

int		Server::read_socket(){
	int res;
	char buf[1024];

	res = recv(this->server_fd, buf, 1024, 0);
	if (res > 0){
		//request
		//responce
	}
	else if (res < 0){
		std::cout << "Error: Reading" << std::endl;
	}
	else
		std::cout << "Closed socket" << std::endl;
	this->close_socket(this->server_fd);
	return 0;
}

// time_t		Server::get_time(){
// 	return this->time;
// }

void	Server::close_socket(int fd){
	close(fd);
// if (req.find(fd) != req.end(){
// 		req.erase(fd);
//		std::cout << "request deleted";
}

int		main(){
	Server();
	return 0;
}