/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:20:47 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/11 23:29:05 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"

// client
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    sf::IpAddress   ip = sf::IpAddress(argv[1]);
    sf::TcpSocket   socket;
    std::string     text = "";
    Client          self;
    bool            is_chat_on = false;
    bool            window_focus = false;
    
    std::cout << "Enter name: ";
    std::string name;
    std::cin >> name;
    self.set_name(name);
    std::cout << self << std::endl;
    socket.connect(ip, 3000);

    sf::RenderWindow    Window(sf::VideoMode(800, 600, 32), "So Long");
    std::vector<sf::Text> chat;

    sf::Packet packet;
    packet = self.get_player_info();
    socket.send(packet);

    sf::Packet  first_receive;
    socket.receive(first_receive);
    self.set_player_info(first_receive);
    std::cout << self << std::endl;
     
    socket.setBlocking(false);

    Window.setTitle(self.get_name());
    sf::Font    font;
    font.loadFromFile("client/chat/orbitron.ttf");

    sf::View gameView(sf::FloatRect(0, 0, 800, 600));
    sf::View chatView(sf::FloatRect(0, 0, 149, 149));
    
    // the game view (full window)
    gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    // mini-map (upper-right corner)
    chatView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

    sf::Sprite sprite1;
    sf::Texture texture1;
    texture1.loadFromFile("assets/p1.png", sf::IntRect(0, 0, 32, 32));
    sprite1.setTexture(texture1);

    sf::Texture texture;
    texture.loadFromFile("assets/5183000.jpg");
    sf::Sprite sprite;
    sf::Vector2u size = texture.getSize();
    sprite.setTexture(texture);  //This is where you add an & to designate texture as a pointer
    sprite.setOrigin(size.x / 2, size.y / 2);

    while(Window.isOpen())
    {
        sf::Event   Event;
        while(Window.pollEvent(Event))
        {
            if (is_chat_on)
            {
                switch (Event.type)
                {
                    case sf::Event::Closed:
                        Window.close();
                        break;
                    case sf::Event::KeyReleased:
                        if (Event.key.code == sf::Keyboard::F1)
                            is_chat_on = !is_chat_on;
                        else if(Event.key.code == sf::Keyboard::Escape)
                            Window.close();
                        else if(Event.key.code == sf::Keyboard::Return)
                        {
                            sf::Packet packet;
                            packet << (self.get_name() + ": " + text);
                            socket.send(packet);
                            sf::Text displayText(text, font, FONT_SIZE);
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
            } else {
                if(Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
                    Window.close();
                else if(Event.type == sf::Event::GainedFocus) // garante que seja a janela selecionada
                    window_focus = true;
                else if(Event.type == sf::Event::LostFocus)
                    window_focus = false;
                else if(Event.type == sf::Event::KeyReleased)
                {
                    if (Event.key.code == sf::Keyboard::F1)
                        is_chat_on = !is_chat_on;
                }
            }
        }

        if (window_focus)
        {
            std::cout << "moving here\n";
        }
        Window.setView(gameView);
        Window.draw(sprite1);

        if(is_chat_on)
        {
            Window.setView(chatView);
            sf::Packet  packet;
            socket.receive(packet);

            std::string tempText;
            if(packet >> tempText)
            {
                sf::Text displayText(tempText, font, FONT_SIZE);
                displayText.setFillColor(sf::Color::Blue);
                chat.push_back(displayText);
            }
            size_t i;
            for (i = 0; i < chat.size(); i++)
            {
                chat[i].setPosition(0, i * FONT_SIZE);
                Window.draw(chat[i]);
            }
            sf::Text   drawText(text, font, FONT_SIZE);
            drawText.setFillColor(sf::Color::Red);
            drawText.setPosition(0, i * FONT_SIZE);
            Window.draw(drawText);
        }
        Window.display();
        Window.clear();
    }

    sf::Packet  done;
    done << "CMD:BYE";
    socket.send(done);
    socket.disconnect();
    return 0;
}
