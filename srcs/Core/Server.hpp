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
#include <set>
#include <map>
#include <algorithm>

#include "Struct.hpp"
#include "Client.hpp"

class Client;

class Server
{
	private:
		struct sockaddr_in			serv_addr;
		// typedef struct s_ipport		ipport;
		std::string					server_name;
		int							server_fd;
		time_t						time;
	public:
		Server();
		Server(Server const &copy);
		virtual ~Server();

		// void	init_server(struct s_ipport ipport);
		void	init_server();
		// void	set_Addr();
		// void	close_socket();
		time_t	get_time();
		void	close_socket();

};

#endif