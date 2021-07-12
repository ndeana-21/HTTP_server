#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"
#include "Struct.hpp"

class Server;
class Client
{
	private:
		struct sockaddr_in		addr_info;
		time_t					time;
		int						client_fd;
	public:
		Client();
		Client(Server *serv, int fd, struct sockaddr_in addr_info);
		Client(const Client &copy);
		Client &operator=(Client const &other);
		virtual ~Client();

		// Responce				*_responce;
		// Request				*_request;
		Server					*_server;	


		time_t					get_time();
		int						get_fd();
		void					init_client();
};

#endif