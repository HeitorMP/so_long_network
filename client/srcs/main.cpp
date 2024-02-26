/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:20:47 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/26 16:11:40 by hmaciel-         ###   ########.fr       */
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
    Client          tmp_enemy;
    bool            window_focus = false;
    bool            chat_is_on = false;
    bool            start_game = false;
    Playfield       pf;

    std::cout << "Enter name: ";
    std::string name;
    std::cin >> name;
    self.set_name(name);
    self.set_position(sf::Vector2f(rand() % 800, rand() % 600));
    
    if ( game_socket.connect(ip, 3000) != sf::Socket::Done || chat_socket.connect(ip, 35000) != sf::Socket::Done)
    {
        std::cerr << "Error: Server connection!\n";
        exit (1);
    }

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
    self.apply_skin();
    tmp_enemy.apply_skin();

    //send the name to chat server
    sf::Packet chat_packet;
    chat_packet << name;
    chat_socket.send(chat_packet);
     
    game_socket.setBlocking(false);
    chat_socket.setBlocking(false);

    sf::RenderWindow    LobbyWindow(sf::VideoMode(800, 600, 32), self.get_name());
    
    sf::Sprite      lobby_background;
    sf::Texture     lobby_background_tx;

    lobby_background_tx.loadFromFile("assets/lobby_back.png");
    lobby_background.setTexture(lobby_background_tx);
    lobby_background.setPosition(0, 0);
    int players_ready = 0;

    LobbyWindow.draw(lobby_background);
    LobbyWindow.display();
    while(start_game == false)
    {
        sf::Event   Event;
        
        while(LobbyWindow.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    LobbyWindow.close();
                    exit (0);
                    break;
                case sf::Event::KeyReleased:
                    if(Event.key.code == sf::Keyboard::Escape)
                    {
                        LobbyWindow.close();
                        exit (0);
                    }
                    else if(Event.key.code == sf::Keyboard::F2 && self.get_ready() == false)
                    {
                        self.set_ready(true);
                        players_ready++;
                    }
                    break;
                default:
                    break;
            }
        }
        sf::Packet  send_my_status, request_status;
        send_my_status = self.get_player_info();
        game_socket.send(send_my_status);
        
        for (int i = 0; i < 1; i++)
        {
            if (game_socket.receive(request_status) == sf::Socket::Done)
            {   
                std::cout << "Pacote Recebido" << std::endl;
                Client    temp;
                temp.set_player_info(request_status);
                std::cout << temp << std::endl;
                if (temp.get_ready() == true && players_ready == 1)
                    start_game = true;
                std::cout << "players ready: " << players_ready << std::endl;
            }
        }
    }
    LobbyWindow.close();

    // Game window;
    sf::RenderWindow    Window(sf::VideoMode(800, 600, 32), "So Long");
    Window.setFramerateLimit(100);
    
    std::vector<sf::Text> chat;
    Window.setTitle(self.get_name());
    sf::Font    font;
    font.loadFromFile("client/chat/orbitron.ttf");

    sf::View gameView(sf::FloatRect(0, 0, 800, 600));
    sf::View chatView(sf::FloatRect(0, 0, 149, 149));
    
    // the game view (full window)
    gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    // mini-map (upper-right corner)
    chatView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

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
                        if (Event.text.unicode == '\b' && text.size() > 0)
                        {
                            text.pop_back();
                        }
                        else
                            text += Event.text.unicode;
                        if (text.find('\b') != std::string::npos)
                                text.erase(text.find('\b'), 1);
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
            self.movePlayer(); // move o player quando janela esta em foco apenas.
            self.update();
        }
        Window.setView(gameView); // seleciona a tela do game
        pf.drawPlayfield(Window);
        
        sf::Packet  send_my_position, request_received;
        send_my_position = self.get_player_pos_packet();
        game_socket.send(send_my_position);
        // receber dados do servidor

        if (game_socket.receive(request_received) == sf::Socket::Done)
        {   
            request_received >> tmp_enemy._position.x >> tmp_enemy._position.y;
            tmp_enemy.update();
        }

        if(chat_is_on)
        {
            Window.setView(chatView); // se chat on muda pra janela do chat executa acoes no chat
            Window.draw(sprite);
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

        Window.draw(self.sp1);
        Window.draw(tmp_enemy.sp1);
        Window.display();
    }

    sf::Packet  done;
    done << "CMD:BYE";
    chat_socket.send(done);
    chat_socket.disconnect();
    game_socket.disconnect();
    return 0;
}
