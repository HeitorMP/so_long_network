/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Playfield.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:52:41 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/12 09:21:08 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <fstream>
# include <unistd.h>
# include <cstring>
# include "so_long.hpp"
# include <SFML/Graphics.hpp>

class Playfield
{
    private:
        sf::Vector2i    _collisions_mask[50][50]; // walls and colletables


    public:
        
        sf::Texture     _tileTexture;
        sf::Sprite      _tiles;
        std::ifstream   _map1file;
        sf::Vector2i    _playfield[50][50];
        sf::Vector2i    _loadCounter = sf::Vector2i(0, 0);
        Playfield();
        ~Playfield();
        
        void            generatePlayfield();
        void            drawPlayfield(sf::RenderWindow &Window);
};