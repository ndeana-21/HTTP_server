#pragma once

# include <iostream>
# include <string>
# include <vector>
# include <stack>

# include <fcntl.h>

# include "get_next_line.hpp"
# include "Server.hpp"
# include "ServerConfig.hpp"
# include "StringUtils.hpp"
# include "Utils.hpp"

class Config
{
	public:
		Config(std::string &path);
		~Config();

		void parse();
		void clear();

		std::vector<ServerConfig> &getServers() {return servers_;};
		std::string &getFileContent() {return file_content_;};
		std::string &getPath() {return path_;};
		int getWorkers() {return workers_;};

	private:
		std::string path_;
		int fd_;

		int workers_;

		std::string file_content_;
		std::vector<std::string> tokens_;
		std::vector<ServerConfig> servers_;
		
		void tokenize();
};
