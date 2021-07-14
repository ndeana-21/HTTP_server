#pragma once

#include "Server.hpp"
#include "Console.hpp"
#include <utility>
#include <vector>
#include <map>

class	ConnexionManager
{
	public:

		/* --- CONSTRUCTORS / DESTRUCTOR --- */
		ConnexionManager();
		~ConnexionManager();

		/* --- CORE FUNCTIONS ---*/
		int						setup(void);
		void					run(void);
		void					clean(void);

		/* --- UTILITY FUNCTIONS --- */
		void							addServer(Server toAdd);

		/* --- GETTERS | SETTERS ---*/
		std::vector<Server> &			getServers(void);

	private:
		ConnexionManager(ConnexionManager const & src);
		ConnexionManager &			operator=(ConnexionManager const & rhs);
		void						handleIncompleteRequests(fd_set reading_set);

		std::vector<Server>			_vecServers;
		std::map<long,Server *>		_listen_fds;
		std::map<long,Server *>		_read_fds;
		std::vector<int>			_write_fds;
		std::map<long,time_t>		_incompleteRequests;

		fd_set						_fd_set;
		unsigned int				_fd_size;
		long						_max_fd;

};
