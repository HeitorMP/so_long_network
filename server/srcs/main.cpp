/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:50:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 13:19:34 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_server.hpp"
#include "Server.hpp"

bool    stop_server = false;

void    handle_signals( int signal )
{
        if ( signal == SIGINT || signal == SIGQUIT )
                stop_server = true;
}

int main(void)
{

    signal(SIGINT, handle_signals);
    Server SL_SERVER;

    if ( !SL_SERVER.start_server() )
    {
        std::cerr << "Falha ao criar o servidor!" << std::endl;
        return 1;
    }
    while(stop_server == false)
    {
        sf::TcpSocket client;
        if (SL_SERVER.full_server() == false)
        {
            if (SL_SERVER.listener.accept(client) != sf::Socket::Done)
            {
               continue ;
            }
            std::cout << "Cliente: " << client.getRemoteAddress() << std::endl;
        
            std::cout << SL_SERVER.add_client() << std::endl;
        }
        else
        {
            sf::TcpSocket refused_client;
            if (SL_SERVER.listener.accept(client) != sf::Socket::Done)
            {
               continue ;
            }
            std::string message = "F";
            std::cout << "Cliente sere deconectado server full: " << refused_client.getRemoteAddress() << std::endl;
            refused_client.send(message.data(), message.size());
            refused_client.disconnect();
        }
    }

    SL_SERVER.listener.close();
    

    return 0;
}

