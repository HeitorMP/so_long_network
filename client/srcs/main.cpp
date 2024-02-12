/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:20:47 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/12 19:02:29 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.hpp"

// client
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    sf::IpAddress   ip = sf::IpAddress(argv[1]);
    sf::TcpSocket   game_socket;
    sf::TcpSocket   chat_socket;
    std::string     text = "";
    Client          self;
    bool            window_focus = false;
    bool            chat_is_on = false;
    Playfield       pf;

    std::cout << "Enter name: ";
    std::string name;
    std::cin >> name;
    self.set_name(name);
    game_socket.connect(ip, 3000);
    chat_socket.connect(ip, 35000);

    sf::RenderWindow    Window(sf::VideoMode(800, 600, 32), "So Long");
    std::vector<sf::Text> chat;

    // send client info to game server
    sf::Packet game_packet;
    game_packet = self.get_player_info();
    game_socket.send(game_packet);
    std::cout << self << std::endl; // should print the client without unique id

    // receive the response from game server with the unique id
    sf::Packet  game_first_receive;
    game_socket.receive(game_first_receive);
    self.set_player_info(game_first_receive);
    std::cout << self << std::endl; // should print the client with unique id

    //send the name to chat server
    sf::Packet chat_packet;
    chat_packet << name;
    chat_socket.send(chat_packet);
     
    game_socket.setBlocking(false);
    chat_socket.setBlocking(false);

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

    pf.generatePlayfield();

    while(Window.isOpen())
    {
        sf::Event   Event;
        
        while(Window.pollEvent(Event))
        {
            if (chat_is_on)
            {
                switch (Event.type)
                {
                    case sf::Event::Closed:
                        Window.close();
                        break;
                    case sf::Event::KeyReleased:
                        if (Event.key.code == sf::Keyboard::F1)
                            chat_is_on = !chat_is_on;
                        else if(Event.key.code == sf::Keyboard::Escape)
                            Window.close();
                        else if(Event.key.code == sf::Keyboard::Return)
                        {  
                            sf::Packet text_packet;
                            text_packet << (self.get_name() + ": " + text);
                            chat_socket.send(text_packet);
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
                        chat_is_on = !chat_is_on;
                    if (Event.key.code == sf::Keyboard::W)
                        self.key_up = false;
                    if (Event.key.code == sf::Keyboard::S)
                        self.key_down = false;
                    if (Event.key.code == sf::Keyboard::A)
                        self.key_left = false;
                    if (Event.key.code == sf::Keyboard::D)
                        self.key_right = false;
                }
                else if(Event.type == sf::Event::KeyPressed)
                {
                    if (Event.key.code == sf::Keyboard::W)
                        self.key_up = true;
                    if (Event.key.code == sf::Keyboard::S)
                        self.key_down = true;
                    if (Event.key.code == sf::Keyboard::A)
                        self.key_left = true;
                    if (Event.key.code == sf::Keyboard::D)
                        self.key_right = true;
                }
            }
        }

        Window.clear();
        if (window_focus)
        {
            self.movePlayer();
            std::cout << "up: " << self.key_up <<std::endl;
            std::cout << "down: " << self.key_down <<std::endl;
            std::cout << "left: " << self.key_left <<std::endl;
            std::cout << "right: " << self.key_right <<std::endl;
        }
        Window.setView(gameView);
        pf.drawPlayfield(Window);
        Window.draw(self.sp1);

        if(chat_is_on)
        {
            Window.setView(chatView);
            sf::Packet  text_packet;
            chat_socket.receive(text_packet);

            std::string tempText;
            if(text_packet >> tempText)
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

        // receber dados do servidor
        // printar inimigos
        Window.display();
    }

    sf::Packet  done;
    done << "CMD:BYE";
    chat_socket.send(done);
    chat_socket.disconnect();
    game_socket.disconnect();
    return 0;
}
