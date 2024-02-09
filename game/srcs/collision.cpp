/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:13:55 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/09 13:33:40 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"
#include "setup.hpp"

// only screen limits, more collisions in the future.
bool    collisionLeft(int const &x)
{
     return (x < 0);
}
bool    collisionRight(int const &x)
{
     return (x > SCREEN_WIDTH - SPRITES_SIZE);
}
bool    collisionUp(int const &y)
{
     return (y < 0);
}
bool    collisionDown(int const &y)
{
     return (y > SCREEN_HEIGHT - SPRITES_SIZE);
}

