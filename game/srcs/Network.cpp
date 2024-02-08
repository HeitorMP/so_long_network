/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:47:15 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/08 19:57:58 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Network.hpp"

Network::Network(std::string const& mode, std::string const& IP, unsigned short const& PORT) : _PORT(PORT), _mode(mode), _IP(IP)
{
    if (_mode == "-s")
    {
        _IP = sf::IpAddress::getLocalAddress();
    }
    else if(_mode == "-c")
    {
       _IP = IP;
    }
}

Network::~Network()
{
    ;
}

bool    Network::start()
{
    if (_mode == "-s")
    {
        listener.listen(_PORT);
        listener.accept(socket);
        std::cout << "Connected as server" << std::endl;
    }
    else if(_mode == "-c")
    {
        socket.connect(_IP, _PORT); 
        std::cout << "Connected as client" << std::endl;
    }

    socket.setBlocking(false);

    return 1;
}
