/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:01:39 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/13 11:42:18 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_chat.hpp"

void    broadcast(std::string message, std::vector<sf::TcpSocket*> clients)
{
    if (message.size() > 0)
    {
        for (size_t curr_cli = 0; curr_cli < clients.size(); curr_cli++)
        {
            sf::Packet broadcast;
            std::string final_message = "Server: " + message;
            broadcast << final_message;
            clients[curr_cli]->send(broadcast);
        }
    }
    std::cerr << "Error: broadcast: Empty message\n";
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    sf::TcpListener             listener;
    sf::SocketSelector          selector;
    bool                        done = false;
    std::vector<sf::TcpSocket*> clients_sockets;

    listener.listen(35000);
    selector.add(listener);
    std::string name;
    
    std::cout << "Chat server on\n";
    while(!done)
    {
        std::cout << "size: " << clients_sockets.size() << std::endl;
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket   *socket = new sf::TcpSocket;
                
                listener.accept(*socket);
                sf::Packet first_receive;
                if (socket->receive(first_receive) == sf::Socket::Done)
                {
                    first_receive >> name;
                    std::cout << name << " has connected to the server" << std::endl;
                }
                clients_sockets.push_back(socket);
                selector.add(*socket);
            }
            else
            {
                for (size_t curr_cli = 0; curr_cli < clients_sockets.size(); curr_cli++)
                {
                    if (selector.isReady(*clients_sockets[curr_cli]))
                    {        
                        {    
                            sf::Packet chat_packet, sendChatPacket;
                            if(clients_sockets[curr_cli]->receive(chat_packet) == sf::Socket::Done)
                            {
                                std::string text = "";
                                chat_packet >> text;
                                std::cout << text << std::endl;
                                if (text.find("CMD:BYE") != std::string::npos)
                                {
                                    broadcast("client disconnected\n", clients_sockets);
                                    selector.remove(*clients_sockets[curr_cli]);
                                    auto it = find(clients_sockets.begin(), clients_sockets.end(), clients_sockets[curr_cli]);
                                    if (it != clients_sockets.end())
                                        clients_sockets.erase(it);
                                }
                                else
                                {    
                                    sendChatPacket << text;
                                    for (size_t other_cli = 0; other_cli < clients_sockets.size(); other_cli++)
                                    {
                                        if (curr_cli != other_cli)
                                            clients_sockets[other_cli]->send(sendChatPacket);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (std::vector<sf::TcpSocket*>::iterator it = clients_sockets.begin(); it != clients_sockets.end(); it++)
        delete *it;
    
    return 0;
}
