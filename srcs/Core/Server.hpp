#ifndef SERVER_HPP
#define SERVER_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "Struct.hpp"
#include "Client.hpp"

class Clien;

class Server
{
	private:
		struct sockaddr_in			serv_addr;
		// typedef struct s_ipport		ipport;
		std::string					server_name;
		int							server_fd;
		int							r;
		time_t						time;
	public:
		Server();
		Server(Server const &copy);
		virtual ~Server();

		// void	init_server(struct s_ipport ipport);
		void	init_server();
		time_t	get_time();
};




#endif