/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:05:15 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 13:17:00 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <map>
# include <iostream>
# include <sstream>
# include <cstring>
# include "Client.hpp"
# include <SFML/Network.hpp>


# define PORT 3000

class Server
{
    public:
        /* CONSTRUCTORS & DESTRUCTOR */
        Server();
        ~Server();
        sf::TcpListener             listener;

        /* METHODS */
        bool    start_server();
        bool    full_server();
      //  int     send_message(int const &, std::string const &);
       // int     update_info(int, int, int);
       // int     parse_client_info(int fd, std::string);
        void    print_clients();
        int     add_client();

        /* GETTERS */
        // int                         get_server_fd();
        // size_t                      get_clients_number();
        std::string                 get_playfield();
    
    protected:

        sf::TcpSocket             _client1_socket;
        sf::TcpSocket             _client2_socket;
        std::map<int, Client*>    _clients_info;

        int                       _client_num;
        std::string               _playfield;
};