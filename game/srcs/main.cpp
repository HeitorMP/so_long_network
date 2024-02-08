/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:22:34 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/08 22:04:17 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"
#include "Network.hpp"
#include "Params.hpp"

int main(int argc, char const *argv[])
{

    if (argc < 3 && argc > 4)
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
    
    sf::RectangleShape rect1, rect2;

    rect1.setSize(sf::Vector2f(20,20));
    rect2.setSize(sf::Vector2f(20,20));

    rect1.setFillColor(sf::Color::Red);
    rect2.setFillColor(sf::Color::Blue);

    sf::RenderWindow    Window(sf::VideoMode(800, 600, 32), "So Long Network");
    
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
        
        prevPosition = rect1.getPosition();

        if (update) // move apenas para a janela em foco
        {            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                rect1.move(0.1f, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                rect1.move(-0.1f, 0.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                rect1.move(0.0f, 0.1f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                rect1.move(0.0f, -0.1f);
        }

        sf::Packet packet;
        
        if (prevPosition != rect1.getPosition())
        {
            packet << rect1.getPosition().x << rect1.getPosition().y; // alimentando o pacote;
            net.socket.send(packet);
        }

        net.socket.receive(packet);
        if (packet >> p2Position.x >> p2Position.y)
        {
            rect2.setPosition(p2Position);
        }
        
        Window.clear();

        for (int col = 0; col < loadCounter.x; col++)
        {
            for (int line = 0; line < loadCounter.y; line++)
            {
                if (playfield[col][line].x != -1 && playfield[col][line].y != -1)
                {
                    tiles.setPosition(col * 32, line * 32);
                    tiles.setTextureRect(sf::IntRect(playfield[col][line].x * 32, playfield[col][line].y * 32, 32, 32));
                    Window.draw(tiles);
                }
            }
        }

        Window.draw(rect1);
        Window.draw(rect2);
        Window.display();
    }

    return 0;
}
