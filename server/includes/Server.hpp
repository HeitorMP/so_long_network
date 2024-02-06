/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:05:15 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/06 12:41:47 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <iostream>
# include <cstring>
# include <netinet/in.h>

# define PORT 3000
# define MAX_EVENTS 100

class Server
{
    public:
        /* CONSTRUCTORS & DESTRUCTOR */
        Server();
        ~Server();

        /* METHODS */
        bool start_server();

        /* GETTERS */
        int get_server_fd();
    
    protected:

        int                         server_fd;
        int                         client1;
        int                         client2;

        std::vector<std::string>    playfield;
};