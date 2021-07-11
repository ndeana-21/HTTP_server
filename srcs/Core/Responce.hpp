#ifndef RESPONCE_HPP
# define RESPONCE_HPP

#include "Request.hpp"
#include "Server.hpp"

class Request;

class Responce
{
	private:
		std::string 	_body;
		std::string		_head; 

	public:
		Responce();
		Responce(const Responce &copy);
		Responce &operator=(Responce const &other);
		~Responce();

		std::string		get_body();
		std::string		get_head();

		void	set_file(std::string file_path);
};

#endif