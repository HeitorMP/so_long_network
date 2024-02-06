/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:59 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/06 12:44:01 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_server.hpp"
#include "Server.hpp"

Server::Server()
{
    ;
}

Server::~Server()
{
    ;
}

bool    Server::start_server()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Erro ao criar socket" << std::endl;
        return 0;
    }

    // Configurar endereço
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(3000);

    // Vincular socket ao endereço
    if (bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "Erro ao vincular socket ao endereço" << std::endl;
        close(server_fd);
        return 0;
    }

    // Iniciar escuta
    if (listen(server_fd, 10) == -1) {
        std::cerr << "Erro ao iniciar escuta" << std::endl;
        close(server_fd);
        return 0;
    }
    return 1;
}


/* GETTERS */

int Server::get_server_fd()
{
    return this->server_fd;
}