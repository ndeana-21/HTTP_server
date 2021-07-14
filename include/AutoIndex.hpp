#pragma once

#include "Server.hpp"
#include "include.hpp"
#include <iostream>
#include <dirent.h>
#include <vector>

class Server;

class AutoIndex
{
	public:
		/* CONSTRUCTORS | DESTRUCTOR */
		AutoIndex(std::string const & url, std::string const & dirPath);
		~AutoIndex();

		/* CORE FUNCTIONS */
		void					createIndex(void);

		/* GETTERS | SETTERS */
		std::string	const &		getIndex(void) const;

	private:
		std::string						_url;
		std::string						_dirPath;
		std::vector<std::string>		_filenames;
		std::vector<std::string>		_entries;

		std::string						_index;

		/* PRIVATE HELPERS : PROCESSING CURRENT DIRECTORY */
		void				getFilenames(void);
		void				processFilenames(void);
		void				createEntries(void);
		void				addIndexLine(int line);

		/* PRIVATE HELPERS : COMPARING FILENAMES */
		static bool			compareFilenames(std::string const & entry_a, std::string const & entry_b);

};
