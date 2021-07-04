#ifndef STRUCT_HPP
# define STRUCT_HPP

#include "Server.hpp"

// struct s_request_header {
//     size_t                 error; 
//     size_t                 content_length;
//     std::string            method;
//     std::string            path;
//     std::string            protocol;
//     std::string            date;
//     std::string            host;
//     std::string            referer;
//     std::string            transfer_encoding;
//     std::list<std::string> accept_charset;
//     std::list<std::string> accept_language;
//     std::list<std::string> authorization;
//     std::list<std::string> content_type;
//     std::list<std::string> user_agent;
//     std::list<std::string> saved_headers;
// };

struct	s_ipport{
	int			port;
	std::string	ip;
};

// struct s_socket{
// 	int				client_fd;
// 	int				entry_socket;
// 	bool			is_read_ready;
// 	bool			is_write_ready;
// 	bool			is_header_read;
// 	bool			is_status_line_read;
// 	bool			is_callback_created;
// 	// sockaddr		client_addr;
// 	// s_ipport const	*ipport;
// 	// Server		*server;
// 	s_request_header headers;
// 	std::list<char*> buf_header;
// };

#endif