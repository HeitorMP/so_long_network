/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:59 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 13:16:51 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_server.hpp"
#include "Server.hpp"

Server::Server()
{
    _playfield.append("1111111111\n"); //y * line lenght + x
    _playfield.append("1000000001\n");
    _playfield.append("1000000001\n");
    _playfield.append("1111111111\n");

    _client_num = 0;
}

Server::~Server()
{
    ;
}

bool    Server::start_server()
{
    if (listener.listen(3000) != sf::Socket::Done)
    {
        std::cout << "Error binding port\n" << std::endl;
        return 0;
    }
    listener.setBlocking(false);
    std::cout << "Sucesso no listening" << std::endl;
    return 1;
}

// int Server::send_message(int const &fd, std::string const & message)
// {
//     send(fd, message.c_str(), message.size(), 0);
//     // {
//     //     std::cerr << "Erro ao enviar mensagem ao cliente!" << std::endl;
//     //     return 1;
//     // }
//     return 0;
// }

int Server::add_client()
{
    _client_num++;
    return _client_num;
}

// int     Server::parse_client_info(int fd, std::string request)
// {
//     // temp format: x=1 y=2
//     std::stringstream   req(request);
//     std::string         token;
//     std::vector<std::string>    infos;
//     while(req >> token) 
//     {
//         // std::cout << "token: " << token << std::endl;
//         std::string temp = token.substr(2);
//         // std::cout << "temp: " << temp << std::endl;
//         infos.push_back(temp);
//     }
//     update_info(fd, atoi(infos[1].c_str()), atoi(infos[2].c_str()));
//     return 0;
// }

// int     Server::update_info(int fd, int new_x, int new_y)
// {
//     _clients_info[fd]->set_x(new_x);
//     _clients_info[fd]->set_y(new_y);
//     return 0;
// }

void    Server::print_clients()
{
    std::map<int, Client*>::iterator it;
    for (it = _clients_info.begin(); it != _clients_info.end(); ++it)
    {
        std::cout << *it->second << std::endl;
    }
}

/* GETTERS */

// int Server::get_server_fd()
// {
//     return this->_server_fd;
// }

bool Server::full_server()
{
    return (_client_num >= MAX_CLIENTS);
}

// size_t  Server::get_clients_number()
// {
//     return (_clients_info.size());
// }

std::string  Server::get_playfield()
{
    return (_playfield);
}