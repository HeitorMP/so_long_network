/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:33:35 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/16 10:55:45 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <fstream>
# include <unistd.h>
# include <cstring>
# include <SFML/Graphics.hpp>
# include <SFML/Network.hpp>
# include "so_long.hpp"

class Client {
    private:
        /* Packet */
        std::string     _unique_id;
        std::string     _name;
        int             _skin_id; // numero do sprite imagem a ser renderizada.
        int             _score;      
        bool            _update;
        
    public:

           /* Sprite */
        sf::Sprite      sp1;
        sf::Texture     tx1;
        sf::Vector2f    _position;

        bool            key_up;
        bool            key_down;
        bool            key_left;
        bool            key_right;
        
        
        Client();
        ~Client();

        void            movePlayer();
        void            update();
        void            apply_skin();

        /* PACKET */
        sf::Packet      get_player_info();
        sf::Packet      get_player_pos_packet();
        void            set_player_info(sf::Packet);

        /* GETTERS & SETTERS */
        std::string     get_unique_id() const;
        std::string     get_name() const;
        int             get_skin_id() const;
        int             get_score() const;
        sf::Vector2f    get_position() const;

        void            set_unique_id(std::string const &);
        void            set_name(std::string const &);
        void            set_skin_id(int const &);
        void            set_score(int const &);
        void            set_position(sf::Vector2f const &);
};

std::ostream &  operator<<( std::ostream & o, Client & i );