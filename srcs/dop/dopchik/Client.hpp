/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:59:55 by gselyse           #+#    #+#             */
/*   Updated: 2021/06/23 18:27:55 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"

// ip and port
struct	s_ipport{
	int			port;
	std::string	ip;
};


//запрос
struct s_request_header {
    size_t                 error; 
    size_t                 content_length;
    std::string            method;
    std::string            path;
    std::string            protocol;
    std::string            date;
    std::string            host;
    std::string            referer;
    std::string            transfer_encoding;
    std::list<std::string> accept_charset;
    std::list<std::string> accept_language;
    std::list<std::string> authorization;
    std::list<std::string> content_type;
    std::list<std::string> user_agent;
    std::list<std::string> saved_headers;
};

//socket
struct s_socket{
	int				client_fd;
	int				entry_socket;
	bool			is_read_ready;
	bool			is_write_ready;
	bool			is_header_read;
	bool			is_status_line_read;
	bool			is_callback_created;
	sockaddr		client_addr;
	s_ipport const	*ipport;
	server		*server;
	s_request_header headers;
	std::list<char*> buf_header;
};		

void	init_socket();


class client{
	public:
		client();
		client(client const &copy);
		client &operator=(client const &other);
		~client();

		void	init_client();
};

#endif