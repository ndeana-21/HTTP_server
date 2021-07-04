/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:12:23 by gselyse           #+#    #+#             */
/*   Updated: 2021/07/04 16:54:04 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(){
};

// void	Server::init_server(s_ipport ipport)
void	Server::init_server(){
	// struct sockaddr addr;
	if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		std::cout << "Error: created socket\n";
		return ;
	}
	this->r = 0;
	if ((r = setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&this->r, sizeof(this->r))) < 0){
		std::cout << "Error: setsockopt() call failed\n";
		return ;
	}
	std::cout << "Hello world";
	memset(&serv_addr, '0', sizeof(serv_addr));
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(5000);
	if (bind(this->server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		std::cout << "Error: bind\n";
		return ;
	}
	if (listen(this->server_fd, 4096) < 0){
		std::cout << "Error: listen\n";
		return ;
	}
	int connfd = 0;
	time_t tims;
	while (1){
		connfd = accept(this->server_fd, (struct sockaddr *)NULL, NULL);
		// tims = time(NULL);
		close(connfd);
		sleep(10000);
	}
}

time_t		Server::get_time(){
	return this->time;
}

// int		main(){
// 	int sock_fd;
// 	s_ipport ipport;
// 	Server *tmp = NULL;
// 	// Server();
// 	// Server();
// 	tmp->init_server();
// 	std::cout << "Hello\n";
// 	return 0;
// }
