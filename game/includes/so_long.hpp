/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:49:13 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/11 12:56:13 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <fstream>
# include <unistd.h>
# include <cstring>
# include <math.h>
# include <map>
# include <SFML/Graphics.hpp>
# include <SFML/Network.hpp>


/* collision.hpp */
bool    collisionLeft(sf::Sprite, sf::Vector2i mask[50][50]);
bool    collisionRight(sf::Sprite, sf::Vector2i mask[50][50]);
bool    collisionUp(sf::Sprite, sf::Vector2i mask[50][50]);
bool    collisionDown(sf::Sprite, sf::Vector2i mask[50][50]);
bool    spriteCollison(sf::Sprite const&, sf::Sprite const&);