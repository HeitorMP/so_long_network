/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:40:53 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/08 22:01:31 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "so_long.hpp"

class Network
{
    private:
        const unsigned short    _PORT;
        std::string             _mode;
        
    public:

        sf::TcpSocket           socket;
        sf::TcpListener         listener;
        sf::IpAddress           _IP;
        Network(std::string const&, std::string const&, unsigned short const&);
        Network(char const&, unsigned short const&);
        ~Network();

        bool    start();
};