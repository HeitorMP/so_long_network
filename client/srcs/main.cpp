/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:20:47 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/11 16:17:53 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    sf::IpAddress   ip = sf::IpAddress("127.0.0.1");
    sf::TcpSocket   socket;
    std::string     id;
    std::string     text = "";
    
    std::cout << "Enter name: ";
    std::cin >> id;

    socket.connect(ip, 3000);

    sf::RenderWindow    Window(sf::VideoMode(800, 600, 32), "So Long");
    std::vector<sf::Text> chat;

    sf::Packet packet;
    packet << id;
    socket.send(packet);
    socket.setBlocking(false);

    Window.setTitle(id);

    sf::Font    font;
    font.loadFromFile("client/chat/orbitron.ttf");

    while(Window.isOpen())
    {
        sf::Event   Event;
        while(Window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    Window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(Event.key.code == sf::Keyboard::Escape)
                        Window.close();
                    else if(Event.key.code == sf::Keyboard::Return)
                    {
                        sf::Packet packet;
                        packet << id + ": " + text;
                        sf::Text displayText(text, font, 20);
                        displayText.setFillColor(sf::Color::Green);
                        chat.push_back(displayText);
                        text = "";
                    }
                    break;
                case sf::Event::TextEntered:
                    text += Event.text.unicode;
                    break;
                default:
                    break;
            }
        }
        sf::Packet  packet;
        socket.receive(packet);

        std::string tempText;
        if(packet >> tempText)
        {
            sf::Text displayText(text, font, 20);
            displayText.setFillColor(sf::Color::Blue);
            chat.push_back(displayText);
        }
        size_t i;
        for (i = 0; i < chat.size(); i++)
        {
            chat[i].setPosition(0, i * 20);
            Window.draw(chat[i]);
        }
        sf::Text   drawText(text, font, 20);
        drawText.setFillColor(sf::Color::Red);
        drawText.setPosition(0, i * 20);
        Window.draw(drawText);
        
        Window.display();
        Window.clear();
    }
    
    return 0;
}
