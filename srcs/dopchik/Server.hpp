/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 22:41:47 by gselyse           #+#    #+#             */
/*   Updated: 2021/06/21 03:23:50 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <list>
# include <iostream>
# include <string>
# include <sys/socket.h>
# include <signal.h>


class Server
{
	public:
		Server();
		Server(const Server &copy);
		Server &operator=(const Server &other);
		~Server();
	private:
		typedef struct sockaddr_in sock_addr;
};

#endif