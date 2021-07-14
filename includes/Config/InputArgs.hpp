#pragma once

# include <string>
# include <map>

# include "Logger.hpp"
# include "Utils.hpp"

class InputArgs {
	public:
		InputArgs(int argc, char **argv);
		~InputArgs();

		void parse();
		std::string helpText();
		LogLevel log();
		bool help();
		bool test();
		bool location();
		
		std::string &getPath() {return path_;};

	private:
		int argc_;
		char **argv_;
		std::string path_;
		LogLevel log_level_;
		std::map<std::string, bool> options_;
};
