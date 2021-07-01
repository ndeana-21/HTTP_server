#pragma once

#include "structures.hpp"

const std::string default_index = "index.html";
const std::string default_ip = "0.0.0.0";
const std::string default_port = "80";
const std::string default_root = "/html";
const std::string default_UBS = "100000";

class c_location;

class c_serverConf
{
	private:
		int							port;
		std::string					ip;
		std::vector<std::string>	server_name;
		long						user_body_size;
		std::string					root;
		std::map<int, std::string>	error_pages;
		std::string					index;

		std::vector<c_location*>		locations;

	public:
		c_serverConf();
		~c_serverConf();
		void checkDefaultType(std::map<int, std::string> def_map);
		
		c_serverConf(c_serverConf& obj);
		c_serverConf& operator=(c_serverConf& obj);
	// GET
		std::string	getIP();
		int			getPort();
		std::vector<std::string> getServerNames();
		long	getUBS();
		std::string	getRoot();
		std::map<int, std::string>	getErrorPages();
		std::string	getIndex();
		std::vector<c_location*>	getLocations();
		bool	isSetErrPage(int err_number);
		bool	isSetServerNames();
	// SET
		int		setPort(std::string user_port);
		int		setIP(std::string user_ip);
		int		setBodySize(std::string ubs_string);
		void	setRoot(std::string new_root);
		void	setErrPage(size_t err_number, std::string err_path);
		void	setIndex(std::string index);
		void	setDefaultsForLocations();
		
		void	addServerName(std::string new_name);
		void	addLocation(c_location* loc);
		void	addServerPlusPort();
		void	addErrPagesRootPath();
		bool	checkLocationPresence();
		bool	checkOriginLocations(std::string loc_name);
		void	mergeLocations(std::vector<c_location*>	loc);
		void	fillDefaultErrorPages();
		void	showServerInfo();
};
