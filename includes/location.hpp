#pragma once

#include "structures.hpp"

class c_location
{
	private:
		std::string					request;
		std::string					root;
		int							autoindex;
		int							save_file;
		std::string					cgi_pass;
		long						user_body_size;
		std::vector<std::string>	server_name;
		std::string					index;
		std::pair<std::string, std::string>	redirection;

	public:
		std::map<int, std::string>	error_pages;
		c_location(std::string request);
		std::vector<std::string>	allowed_requests;// different type of requests - GET, POST, etc.
		~c_location();

	//GET
		std::string	getRequest();
		std::vector<std::string>	getAlllowedMethods();
		std::vector<std::string> getServerNames();
		std::string	getRoot();
		int		getAutoindex();
		int		getSaveFile();
		std::string	getCGIPath();
		long	getUserBodySize();
		std::map<int, std::string>	getErrorPaths();
		std::string	getDefaultPage();
		std::string	getIndex();
		std::pair<std::string, std::string>	getRedir();
		bool	isSetAllowedReq();
		bool	isSetRedir();
		bool	isSetErrPage(int err_number);

	//SET
		void	setRoot(std::string new_root);
		void	setErrPage(size_t err_number, std::string err_path);
		void	setAutoIndex(std::string autoind);
		void	setSaveFile(std::string save);
		void	setCGIPath(std::string path);
		int		setBodySize(std::string ubs);
		void	setRedirection(std::string redir_type, std::string path);
		void	setDefaultUBS(long server_ubs);
		void	setDefaultRoot(std::string server_root);
		void	setDefPage(std::string page_name);
		void	setDefaultAllowedMethods();
		void	setDefaultIndex(std::string server_index);
		void	setDefaultAutoindex();
		void	setDefaultSaveFile();
		void	setServerNames(std::vector<std::string> server_names);
		void	setIndex(std::string new_index);
		
		void	insertDefaultErrPages(std::map<int, std::string> to_insert);
		int		addRequest(std::string request);
		void	addErrPagesRootPath();
		int		checkRedirType(std::string redir_type);
		int		checkErrType(std::string err_type);
		void	showLocationInfo();
};