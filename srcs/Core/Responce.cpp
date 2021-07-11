#include "Responce.hpp"
#include "Server.hpp"


Responce::Responce(){}

Responce::Responce(Responce const &copy){}

Responce::~Responce(){}

Responce &Responce::operator=(Responce const &other){}


void		Responce::set_file(std::string file_path){
	if (file_path.empty())
		return ;
}

std::string		Responce::get_head(){
	return this->_head;
}

std::string		Responce::get_body(){
	return this->_body;
}