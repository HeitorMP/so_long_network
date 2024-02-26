/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:44:49 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/17 14:51:06 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
    _unique_id = "";
    _name = "";
    _skin_id = 0;
    _score = 0;
    _position.x = 0;
    _position.y = 0;
    _update = false;

    key_up = false;
    key_down = false;
    key_left = false;
    key_right = false;
    
}

Client::~Client()
{
    ;
}

sf::Packet  Client::get_player_info()
{
    sf::Packet packet;
    packet << _unique_id << _name << _skin_id << _score << _position.x << _position.y << _update;
    return (packet);
}

sf::Packet  Client::get_player_pos_packet()
{
    sf::Packet packet;
    packet << _position.x << _position.y;
    return (packet);
}

void        Client::set_player_info(sf::Packet packet_from_server)
{
    packet_from_server >> _unique_id >> _name >> _skin_id >> _score >> _position.x >> _position.y >> _update;
    // checar valores e indicar possiveis erros;
}

void        Client::movePlayer()
{
    if (key_up)
        _position.y -= 1.0;
    if (key_down)
        _position.y += 1.0;
    if (key_left)
        _position.x -= 1.0;
    if (key_right)
        _position.x += 1.0;
}

void    Client::update()
{
    sp1.setPosition(_position);
}

void    Client::apply_skin()
{
    if (_skin_id == 1)
    {
        tx1.loadFromFile("assets/p1.png", sf::IntRect(0, 0, GRID_SIZE, GRID_SIZE));
        sp1.setTexture(tx1);
    }
    else
    {
        tx1.loadFromFile("assets/p2.png", sf::IntRect(0, 0, GRID_SIZE, GRID_SIZE));
        sp1.setTexture(tx1);
    }
}


/* GETTERS & SETTERS */
std::string     Client::get_unique_id() const
{
    return (this->_unique_id);
}
std::string     Client::get_name() const
{
    return (this->_name);
}
int             Client::get_skin_id() const
{
    return (this->_skin_id);
}
int             Client::get_score() const
{
    return (this->_score);
}
sf::Vector2f    Client::get_position() const
{
    return (this->_position);
}

void            Client::set_unique_id(std::string const &new_id)
{
    this->_unique_id = new_id;
}
void            Client::set_name(std::string const &new_name)
{
    this->_name = new_name;
}
void            Client::set_skin_id(int const &new_skin_id)
{
    this->_skin_id = new_skin_id;
}
void            Client::set_score(int const &new_score)
{
    this->_score = new_score;
}
void            Client::set_position(sf::Vector2f const &new_position)
{
    this->_position = new_position;
}

std::ostream &  operator<<( std::ostream & o, Client & i )
{
	o << "Unique id: " << i.get_unique_id() << std::endl;
	o << "Player Name: " << i.get_name() << std::endl;
	o << "Skin Id: " << i.get_skin_id() << std::endl;
	o << "Score: " << i.get_score() << std::endl;
	o << "Position: x -> " << i.get_position().x << " | y -> " << i.get_position().y;
    
	return o;
}