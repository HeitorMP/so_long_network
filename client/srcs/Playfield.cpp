/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Playfield.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:00:43 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/12 19:11:27 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Playfield.hpp"

bool    is_wall(sf::Vector2i wall_candidate) // nao escalavel e momentaneo.
{
    return (wall_candidate.y == 0 || wall_candidate.y == 1 || wall_candidate.y == 4 \
        || wall_candidate.x == 0 || wall_candidate.x == 5);
}

Playfield::Playfield()
{
    _map1file.open("./server_game/maps/map1.txt");
    std::cout << _map1file.is_open() << std::endl;
}

Playfield::~Playfield()
{
    ;
}

void    Playfield::generatePlayfield()
{
    if (_map1file.is_open())
    {
        std::cout << "File is open: maps/map1.txt" << std::endl;
        std::string tileLocation;
        _map1file >> tileLocation;
        std::cout << "first line: " << tileLocation << std::endl;
        _tileTexture.loadFromFile(tileLocation); // primeira linha pega o caminho para o png, carrega a imagem completa do tileset
        _tiles.setTexture(_tileTexture); // cria sprite tiles com a imagem inteira do arquivo png
        while(!_map1file.eof())
        {
            std::string str;
            _map1file >> str;
            char x = str[0];
            //str[1] vai ser igual a ','
            char y = str[2];
            if (!isdigit(x) || !isdigit(y))
                _playfield[_loadCounter.x][_loadCounter.y] = sf::Vector2i(-1, -1);
            else
            {
                _playfield[_loadCounter.x][_loadCounter.y] = sf::Vector2i(x - '0', y - '0');
                if (is_wall(_playfield[_loadCounter.x][_loadCounter.y]))
                    _collisions_mask[_loadCounter.x][_loadCounter.y] = _playfield[_loadCounter.x][_loadCounter.y];
                else
                    _collisions_mask[_loadCounter.x][_loadCounter.y] = sf::Vector2i(-1,-1);
            }
            if (_map1file.peek() == '\n')
            {
                _loadCounter.x = 0;
                _loadCounter.y++;
            }
            else
                _loadCounter.x++;
        }
        _loadCounter.y++;
    } else {
        std::cout << "nao abriu\n";
    }
}

void    Playfield::drawPlayfield(sf::RenderWindow &Window)
{
    for (int col = 0; col < _loadCounter.x; col++)
    {
        for (int line = 0; line < _loadCounter.y; line++)
        {
            if (_playfield[col][line].x != -1 && _playfield[col][line].y != -1)
            {
                _tiles.setPosition(col * GRID_SIZE, line * GRID_SIZE);
                _tiles.setTextureRect(sf::IntRect(_playfield[col][line].x * GRID_SIZE, _playfield[col][line].y * GRID_SIZE, GRID_SIZE, GRID_SIZE));
                Window.draw(_tiles);
            }
        }
    }
}