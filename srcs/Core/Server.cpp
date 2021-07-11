/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:12:23 by gselyse           #+#    #+#             */
/*   Updated: 2021/07/11 19:15:12 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(){
	Server::init_server();
}

Server::~Server(){}

void	Server::init_server(){
	int bytes_read;
	char buf[1024] = {'\0'};

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
	// this->accept_client();
	// int res, max_fd = 0;
	// struct timeval timeout;
	// timeout.tv_sec = 1;
	// timeout.tv_usec = 0;
	// for (;;){
	// 	FD_ZERO(&this->readset);
	// 	FD_ZERO(&this->writeset);
	// }

	std::set<int> clients;
	clients.clear();

	while (true) {
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
			exit(3);
		}
		if (FD_ISSET(this->server_fd, &readset))
			// int sock = accept(this->server_fd, NULL, NULL); 	//получили новый запрос на соединение, подтверждаем
			// if (sock < 0) {
			// 	perror("accept");
			// 	exit(4);
			// }
			// fcntl(sock, F_SETFL, O_NONBLOCK);
			// clients.insert(sock);
			int sock = accept_client();
		}
		for (std::set<int>::iterator it = clients.begin(); it != clients.end();) {
			if (FD_ISSET(*it, &readset)) { 
				bytes_read = recv(*it, buf, 1024, 0); 	//получили данные от клиента, читаем их
				if (bytes_read <= 0) {
					close(*it);							//соединение разорвано, закрываем
					clients.erase(it++);
					continue;
				}
				else {
					std::cout << buf << "\n";
					send(*it, buf, bytes_read, 0);
				}
				
			}
			++it;
		}
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

// int		Server::read_socket(){
	
// }

int		Server::get_fd(){
	return this->server_fd;
}

// time_t		Server::get_time(){
// 	return this->time;
// }

// void	Server::close_socket(int fd){
// 	close(fd);
// // if (req.find(fd) != req.end(){
// // 		req.erase(fd);
// //		std::cout << "request deleted";
// }

int		main(){
	Server();
	return 0;
}