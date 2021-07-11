#include "Request.hpp"

Request::Request(){}

Request::Request(Request const &copy){
	*this = copy;
}

Request &Request::operator=(Request const &other){
	this->_method = other._method;
	this->_uri = other._uri;
	this->_body = other._body;
	this->_header = other._header;
	this->_version_http = other._version_http;
	this->_port = other._port;
	this->_ip = other._ip;
	return *this;
}

Request::~Request(){}

void			Request::request_init(){
	this->_method = "";
	this->_body = "";
	this->_uri = "";
	this->_version_http = "1.1";
	// this->_ip
	this->_port = 80;
	this->_header.clear();
}

std::string		Request::get_method(){
	return this->_method;
}

std::string		Request::get_uri(){
	return this->_uri;
}

// bool			Request::is_close(){
// 	return 
// }

void			Request::print_request(){
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "version - " << this->_version_http << std::endl;
}