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
class Request;
class Responce;

class Server
{
	private:
		struct sockaddr_in			serv_addr;
		// typedef struct s_ipport		ipport;
		std::string					server_name;
		int							server_fd;
		Request						req
		// Responce					_responce;
		// std::map<int, Client*>		clients;
		fd_set						readset;
		fd_set						writeset;
		// time_t						time;
	public:
		Server();
		Server(Server const &copy);
		Server &operator = (Server const &other) =default;
		virtual ~Server();

		int				get_fd();
		std::string		get_name();

		// void	init_server(struct s_ipport ipport);
		void	setup_server();
		void	run_server();
		int		accept_client();
		int		read_socket();
		// int		write_socket();
		// void	set_Addr();
		// void	close_socket();
		time_t	get_time();
		void	close_socket(int fd);

};

#endif