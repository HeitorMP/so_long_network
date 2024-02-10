/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:49:13 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/10 00:43:45 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <fstream>
# include <unistd.h>
# include <cstring>
# include <math.h>
# include <SFML/Graphics.hpp>
# include <SFML/Network.hpp>


/* collision.hpp */
bool   collisionLeft(int const &);
bool   collisionRight(int const &);
bool   collisionUp(int const &);
bool   collisionDown(int const &);
bool    spriteCollison(sf::Sprite const&, sf::Sprite const&);