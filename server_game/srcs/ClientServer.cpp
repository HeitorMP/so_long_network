/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientServer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:44:49 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/16 09:29:20 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientServer.hpp"

ClientServer::ClientServer()
{
    ;
}

ClientServer::~ClientServer()
{
    ;
}

sf::Packet  ClientServer::get_player_info()
{
    sf::Packet packet;
    packet << _unique_id << _name << _skin_id << _score << _position.x << _position.y << _ready;
    return (packet);
}

sf::Packet  ClientServer::get_player_pos_packet()
{
    sf::Packet packet;
    packet << _position.x << _position.y;
    return (packet);
}

void        ClientServer::set_player_info(sf::Packet packet_from_server)
{
    packet_from_server >> _unique_id >> _name >> _skin_id >> _score >> _position.x >> _position.y >> _ready;
    // checar valores e indicar possiveis erros;
}


/* GETTERS & SETTERS */
std::string     ClientServer::get_unique_id() const
{
    return (this->_unique_id);
}
std::string     ClientServer::get_name() const
{
    return (this->_name);
}
int             ClientServer::get_skin_id() const
{
    return (this->_skin_id);
}
int             ClientServer::get_score() const
{
    return (this->_score);
}
sf::Vector2f    ClientServer::get_position() const
{
    return (this->_position);
}
bool            ClientServer::get_ready() const
{
    return (this->_ready);
}

void            ClientServer::set_unique_id(std::string const &new_id)
{
    this->_unique_id = new_id;
}
void            ClientServer::set_name(std::string const &new_name)
{
    this->_name = new_name;
}
void            ClientServer::set_skin_id(int const &new_skin_id)
{
    this->_skin_id = new_skin_id;
}
void            ClientServer::set_score(int const &new_score)
{
    this->_score = new_score;
}
void            ClientServer::set_position(sf::Vector2f const &new_position)
{
    this->_position = new_position;
}
void            ClientServer::set_ready(bool const &new_status)
{
    this->_ready = new_status;
}

std::ostream &  operator<<( std::ostream & o, ClientServer & i )
{
	o << "Unique id: " << i.get_unique_id() << std::endl;
	o << "Player Name: " << i.get_name() << std::endl;
	o << "Skin Id: " << i.get_skin_id() << std::endl;
	o << "Score: " << i.get_score() << std::endl;
	o << "Position: x -> " << i.get_position().x << " | y -> " << i.get_position().y << std::endl;
    o << "Ready: " << i.get_ready();
    
	return o;
}
