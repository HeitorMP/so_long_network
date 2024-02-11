/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:01:39 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/11 16:39:40 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_server.hpp"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    sf::TcpListener             listener;
    sf::SocketSelector          selector;
    bool                        done = false;
    std::vector<sf::TcpSocket*> clients;

    listener.listen(3000);
    selector.add(listener);
    
    while(!done)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket *socket = new sf::TcpSocket;
                listener.accept(*socket);
                sf::Packet packet;
                std::string id;
                if (socket->receive(packet) == sf::Socket::Done)
                    packet >> id;
                    
                std::cout << id << " has connected to the server" << std::endl;
                clients.push_back(socket);
                selector.add(*socket);
            }
            else
            {
                for (size_t curr_cli = 0; curr_cli < clients.size(); curr_cli++)
                {
                    if (selector.isReady(*clients[curr_cli]))
                    {
                        std::cout << "cliente antigo aqui\n";
                        sf::Packet packet, sendPacket;
                        if(clients[curr_cli]->receive(packet) == sf::Socket::Done)
                        {
                            std::string text;
                            packet >> text;
                            sendPacket << text;
                            std::cout << "size: " << clients.size() << std::endl;
                            for (size_t other_cli = 0; other_cli < clients.size(); other_cli++)
                            {
                                if (curr_cli != other_cli)
                                    clients[other_cli]->send(sendPacket);
                            }
                        }
                    } 
                }
            }
        }
    }

    
    return 0;
}