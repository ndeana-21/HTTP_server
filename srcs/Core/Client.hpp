#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"
#include "Struct.hpp"


class Client
{
private:
	struct sockaddr_in		addr_info;
	time_t					time;
	int						client_fd;
public:
	Client();
	Client(const Client &copy);
	Client &operator=(Client const &other);
	virtual ~Client();

	time_t					get_time();
};

#endif