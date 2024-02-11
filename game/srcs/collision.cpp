/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:13:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/11 13:18:48 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"
#include "setup.hpp"

// only screen limits, more collisions in the future.
bool collisionRight(sf::Sprite s1, sf::Vector2i mask[50][50])
{
     int  x = s1.getPosition().x;
     int  y = s1.getPosition().y;
     
     if (x > SCREEN_WIDTH - SPRITES_SIZE) // screen limits
          return (true);
     
     int  next_position = x + SPRITES_SIZE + 1;
     int  next_x_grid = next_position / SPRITES_SIZE;
     int  y_grid = y / SPRITES_SIZE;
     if ( mask[next_x_grid][y_grid].x != -1 && mask[next_x_grid][y_grid].y != -1)
          return (true);
     return (false);
}

bool collisionLeft(sf::Sprite s1, sf::Vector2i mask[50][50])
{
     int  x = s1.getPosition().x;
     int  y = s1.getPosition().y;
     
     if (x < 0) // screen limits
          return (true);
     
     int  next_position = x - 1;
     int  next_x_grid = next_position / SPRITES_SIZE;
     int  y_grid = y / SPRITES_SIZE;
     if ( mask[next_x_grid][y_grid].x != -1 && mask[next_x_grid][y_grid].y != -1)
          return (true);
     return (false);
}

bool collisionUp(sf::Sprite s1, sf::Vector2i mask[50][50])
{
     int  x = s1.getPosition().x;
     int  y = s1.getPosition().y;
     
     if (y < 0) // screen limits
          return (true);
          
     int  next_position = y - 1;
     int  next_y_grid = next_position / SPRITES_SIZE;
     int  x_grid = x / SPRITES_SIZE;
     if ( mask[x_grid][next_y_grid].x != -1 && mask[x_grid][next_y_grid].y != -1)
          return (true);
     
     return (false);
}

bool collisionDown(sf::Sprite s1, sf::Vector2i mask[50][50])
{
     int  x = s1.getPosition().x;
     int  y = s1.getPosition().y;
     
     if (y > SCREEN_HEIGHT - SPRITES_SIZE) // screen limits
          return (true);
          
     int  next_position = y + SPRITES_SIZE + 1;
     int  next_y_grid = next_position / SPRITES_SIZE;
     int  x_grid = x / SPRITES_SIZE;
     if ( mask[x_grid][next_y_grid].x != -1 && mask[x_grid][next_y_grid].y != -1)
          return (true);
     
     return (false);
}

bool spriteCollison(sf::Sprite const& sp1, sf::Sprite const& sp2)
{
     return (sp1.getGlobalBounds().intersects(sp2.getGlobalBounds()));
}

// funcao para loop em todos os sprites.

// paredes array com 1;

