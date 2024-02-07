/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:15:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 13:23:19 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, std::string name, int x, int y) : _fd(fd), _x(x), _y(y), _score(0), _name(name)
{
    std::cout << _name << " joined the server!" << std::endl;
}

Client::~Client()
{
    if (_fd)
        close(_fd);
}


/* GETTERS & SETTERS */
std::string Client::get_name()
{
    return (this->_name);
}

int         Client::get_fd()
{
    return (this->_fd);
}

int         Client::get_x()
{
    return (this->_x);
}

int         Client::get_y()
{
    return (this->_y);
}

void    Client::set_name( std::string name )
{
    this->_name =  name;
}
void    Client::set_x( int x )
{
    this->_x =  x;
}

void    Client::set_y( int y )
{
    this->_y =  y;
}

std::ostream &	operator<<( std::ostream & o, Client & i )
{
	o << "name: " << i.get_name() << std::endl;
	o << "fd: " << i.get_fd() << std::endl;
	o << "x: " << i.get_x() << std::endl;
	o << "y: " << i.get_y() << std::endl;
	return o;
}