/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientServerServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:33:35 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/16 09:30:20 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <fstream>
# include <unistd.h>
# include <cstring>
# include <SFML/Graphics.hpp>
# include <SFML/Network.hpp>

class ClientServer{
    private:
        
        std::string     _unique_id;
        std::string     _name;
        int             _skin_id;
        int             _score;      
        sf::Vector2f    _position;
        bool            _ready; // can be status in the future
    
    public:

        ClientServer();
        ~ClientServer();

       sf::Packet       get_player_info();
       sf::Packet       get_player_pos_packet();
       void             set_player_info(sf::Packet);

        /* GETTERS & SETTERS */
        std::string     get_unique_id() const;
        std::string     get_name() const;
        int             get_skin_id() const;
        int             get_score() const;
        sf::Vector2f    get_position() const;
        bool            get_ready() const;

        void            set_unique_id(std::string const &);
        void            set_name(std::string const &);
        void            set_skin_id(int const &);
        void            set_score(int const &);
        void            set_position(sf::Vector2f const &);
        void            set_ready(bool const &);
};

std::ostream &  operator<<( std::ostream & o, ClientServer & i );