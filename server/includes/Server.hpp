/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:05:15 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 00:17:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <map>
# include <iostream>
# include <sstream>
# include <cstring>
# include <netinet/in.h>
# include "Client.hpp"

# define PORT 3000
# define MAX_EVENTS 100

class Server
{
    public:
        /* CONSTRUCTORS & DESTRUCTOR */
        Server();
        ~Server();

        /* METHODS */
        bool    start_server();
        bool    full_server();
        int     send_message(int const &, std::string const &);
        int     update_info(int, int, int);
        int     parse_client_info(int fd, std::string);
        void    print_clients();
        int     create_client(int const &, std::string const &, int, int);

        /* GETTERS */
        int                         get_server_fd();
        size_t                      get_clients_number();
        std::string                 get_playfield();
    
    protected:

        int                         _server_fd;

        std::string                 _playfield;
        std::map<int, Client*>      _clients_info;
};