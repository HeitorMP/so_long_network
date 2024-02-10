/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:22:34 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/10 00:36:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"
#include "Network.hpp"
#include "Params.hpp"
#include "setup.hpp"


int main(int argc, char const *argv[])
{
    std::cout << argc;
    if (argc < 3 || argc > 4)
    {
        std::cout << "usage for server: ./so_long -s PORT" << std::endl;
        std::cout << "usage for client: ./so_long -c IP PORT" << std::endl;
        std::cout << "./so_long -c 127.0.0.1 3000" << std::endl;
        return 1;
    }
    
    std::string mode = "";
    std::string ip = "";
    std::string port = "";
    
    if (argc == 4)
    {
        if(Params::isGoodClient(argv[1], argv[2], argv[3]) == false)
        {
            std::cerr << "Bad params!" << std::endl;
            return (1);
        }
        ip = argv[2];
        port = argv[3];
    }
    else
    {
       if(Params::isGoodServer(argv[1], argv[2]) == false)
       {
            std::cerr << "Bad params!" << std::endl; 
            return (1);
       }
       port = argv[2];
    }
    mode = argv[1];
   
    Network net(mode, ip, stoi(port));
    net.start();

    bool update = false;

    /* TILE */
    sf::Vector2i playfield[50][50];
    sf::Vector2i loadCounter = sf::Vector2i(0, 0);

    sf::Texture tileTexture;
    sf::Sprite  tiles;
    std::ifstream   map1file("maps/map1.txt");

    if (map1file.is_open())
    {
        std::cout << "File is open: maps/map1.txt" << std::endl;
        std::string tileLocation;
        map1file >> tileLocation;
        std::cout << "first line: " << tileLocation << std::endl;
        tileTexture.loadFromFile(tileLocation); // primeira linha pega o caminho para o png
        tiles.setTexture(tileTexture); // cria sprite tiles com a imagem inteira do arquivo png
        while(!map1file.eof())
        {
            std::string str;
            map1file >> str;
            char x = str[0];
            //str[1] vai ser igual a ','
            char y = str[2];
            if (!isdigit(x) || !isdigit(y))
                playfield[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
            else
                playfield[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
            
            if (map1file.peek() == '\n')
            {
                loadCounter.x = 0;
                loadCounter.y++;
            }
            else
                loadCounter.x++;
        }
        loadCounter.y++;
    }
    
    sf::Sprite sprite1;
    sf::Texture texture1;
    sf::Sprite sprite2;
    sf::Texture texture2;

    if (mode == "-s")
    {
        texture1.loadFromFile("assets/p1.png", sf::IntRect(0, 0, SPRITES_SIZE, SPRITES_SIZE));
        sprite1.setTexture(texture1);
        texture2.loadFromFile("assets/p2.png", sf::IntRect(0, 0, SPRITES_SIZE, SPRITES_SIZE));
        sprite2.setTexture(texture2);
        sprite1.setPosition(sf::Vector2f(1 * SPRITES_SIZE , 3 * SPRITES_SIZE));
        sprite2.setPosition(sf::Vector2f(23 * SPRITES_SIZE, 15 * SPRITES_SIZE));
    }
    else
    {
        texture1.loadFromFile("assets/p2.png", sf::IntRect(0, 0, SPRITES_SIZE, SPRITES_SIZE));
        sprite1.setTexture(texture1);
        texture2.loadFromFile("assets/p1.png", sf::IntRect(0, 0, SPRITES_SIZE, SPRITES_SIZE));
        sprite2.setTexture(texture2);
        sprite1.setPosition(sf::Vector2f(23 * SPRITES_SIZE, 15 * SPRITES_SIZE));
        sprite2.setPosition(sf::Vector2f(1 * SPRITES_SIZE, 3 * SPRITES_SIZE));
    }

    sf::RenderWindow    Window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "So Long Network");
    
    sf::Vector2f prevPosition, p2Position;

    while(Window.isOpen())
    {
        sf::Event Event;
        while(Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
                Window.close();
            else if(Event.type == sf::Event::GainedFocus) // garante que seja a janela selecionada
                update = true;
            else if(Event.type == sf::Event::LostFocus)
                update = false;
        }
        
        prevPosition = sprite1.getPosition();

        if (update) // move apenas para a janela em foco
        {            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !collisionRight(sprite1.getPosition().x))
                sprite1.move(0.1f, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !collisionLeft(sprite1.getPosition().x))
                sprite1.move(-0.1f, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !collisionDown(sprite1.getPosition().y))
                sprite1.move(0.0f, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !collisionUp(sprite1.getPosition().y))
                sprite1.move(0.0f, -0.1f);
        }

        sf::Packet packet;
        
        if (prevPosition != sprite1.getPosition())
        {
            packet << sprite1.getPosition().x << sprite1.getPosition().y; // alimentando o pacote;
            net.socket.send(packet);
        }

        net.socket.receive(packet);
        if (packet >> p2Position.x >> p2Position.y)
        {
            sprite2.setPosition(p2Position);
        }
        
        Window.clear();

        for (int col = 0; col < loadCounter.x; col++)
        {
            for (int line = 0; line < loadCounter.y; line++)
            {
                if (playfield[col][line].x != -1 && playfield[col][line].y != -1)
                {
                    tiles.setPosition(col * SPRITES_SIZE, line * SPRITES_SIZE);
                    tiles.setTextureRect(sf::IntRect(playfield[col][line].x * SPRITES_SIZE, playfield[col][line].y * SPRITES_SIZE, SPRITES_SIZE, SPRITES_SIZE));
                    Window.draw(tiles);
                }
            }
        }

        Window.draw(sprite1);
        Window.draw(sprite2);
        Window.display();
    }

    return 0;
}
