#pragma once

#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <exception>
#include <ctime>
#include <cstring>

#include <arpa/inet.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include "server.hpp"

struct s_ipport
{
	int			port;
	std::string	ip;
};

bool    operator==(s_ipport const &a, s_ipport const &b) {return (a.ip == b.ip && a.port == b.port);}
bool    operator!=(s_ipport const &a, s_ipport const &b) {return (!(a == b));}

struct s_request_header
{
	size_t					error;
	size_t					content_len;
	std::string				method;
	std::string				path;
	std::string				protocol;
	std::string				date;
	std::string				host;
	std::string				referer;
	std::string				transfer_encoding;
	std::list<std::string>	accept_charset;
	std::list<std::string>	accept_language;
	std::list<std::string>	authorization;
	std::list<std::string>	content_type;
	std::list<std::string>	user_agent;
	std::list<std::string>	save_headers;
};

void    reset_header(s_request_header *h);

std::ostream& operator<<(std::ostream& os, s_request_header const &src);

struct s_similar_get_req
{
    int             client_priority;
    std::string     host;
    std::string     respons;
    std::string     path_respons;
    std::string     original_path;
    s_ipport const  *ipport;
    time_t          last_state_change;
};

void    reset_similar(s_similar_get_req *simi);

struct s_socket
{
    int              		client_fd;
    int              		entry_socket;
    bool             		is_read_ready;
    bool             		is_write_ready;
    bool             		is_header_read;
    bool             		is_status_line_read;
    bool             		is_callback_created;
    sockaddr         		client_addr;
    s_ipport const   		*ipport;
    c_server const			*server;
    s_request_header 		headers;
    std::list<char*> 		buf_header;
};

void    reset_socket(s_socket *s);

std::ostream    &operator<<(std::ostream &o, s_socket const &i);
std::ostream    &operator<<(std::ostream& os, const std::list<s_socket>& v);
