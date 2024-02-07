/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:59 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 00:18:56 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_server.hpp"
#include "Server.hpp"

Server::Server()
{
    _playfield.append("1111111111\n");
    _playfield.append("1000000001\n");
    _playfield.append("1000000001\n");
    _playfield.append("1111111111\n");
}

Server::~Server()
{
    if (_server_fd)
        close(_server_fd);
}

bool    Server::start_server()
{
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd == -1) {
        std::cerr << "Erro ao criar socket" << std::endl;
        return 0;
    }

    // Configurar endereço
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);


    const int trueFlag = 1;
	setsockopt( _server_fd, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int) );

    // Vincular socket ao endereço
    if (bind(_server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "Erro ao vincular socket ao endereço" << std::endl;
        close(_server_fd);
        return 0;
    }

    // Iniciar escuta
    if (listen(_server_fd, 10) == -1) {
        std::cerr << "Erro ao iniciar escuta" << std::endl;
        close(_server_fd);
        return 0;
    }
    
    return 1;
}

int Server::send_message(int const &fd, std::string const & message)
{
    send(fd, message.c_str(), message.size(), 0);
    // {
    //     std::cerr << "Erro ao enviar mensagem ao cliente!" << std::endl;
    //     return 1;
    // }
    return 0;
}

int Server::create_client(int const &fd, std::string const &name, int x, int y)
{
    
    _clients_info.insert(std::make_pair(fd, new Client(fd, name, x, y)));
    return 0;
}

int     Server::parse_client_info(int fd, std::string request)
{
    // temp format: x=1 y=2
    std::stringstream   req(request);
    std::string         token;
    std::vector<std::string>    infos;
    while(req >> token) 
    {
        // std::cout << "token: " << token << std::endl;
        std::string temp = token.substr(2);
        // std::cout << "temp: " << temp << std::endl;
        infos.push_back(temp);
    }
    update_info(fd, atoi(infos[1].c_str()), atoi(infos[2].c_str()));
    return 0;
}

int     Server::update_info(int fd, int new_x, int new_y)
{
    _clients_info[fd]->set_x(new_x);
    _clients_info[fd]->set_y(new_y);
    return 0;
}

void    Server::print_clients()
{
    std::map<int, Client*>::iterator it;
    for (it = _clients_info.begin(); it != _clients_info.end(); ++it)
    {
        std::cout << *it->second << std::endl;
    }
}

/* GETTERS */

int Server::get_server_fd()
{
    return this->_server_fd;
}

bool Server::full_server()
{
    return (_clients_info.size() >= 2);
}

size_t  Server::get_clients_number()
{
    return (_clients_info.size());
}

std::string  Server::get_playfield()
{
    return (_playfield);
}