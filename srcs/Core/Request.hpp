#ifndef REQUEST_HPP
# define REQUEST_HPP
#include "Server.hpp"

// enum	method{
// 	GET, //0
// 	HEAD, //1
// 	POST, // 2
// 	PUT, //3
// 	DELETE, //4
// 	CONNECT, //5
// 	OPTIONS, //6
// 	TRACE //7
// };

class Request
{
	private:
		std::string							_method;
		std::string							_body;
		std::map<std::string, std::string>	_header;
		std::string							_version_http;
		std::string							_uri;
		int									_port;
		std::string 						_ip;
		// std::string		_cgi;

	public:
		Request();
		Request(Request const &copy);
		Request &operator=(Request const &other);
		~Request();

		std::string		get_method();
		std::string		get_uri();
		std::string		get_ip();
		std::string		get_version_http();

		void			request_init();
		void			print_request();
		// bool			is_close();
};

std::ostream &operator << (std::ostream &out, const Request &req);

#endif