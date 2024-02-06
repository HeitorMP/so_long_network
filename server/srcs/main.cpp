/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:50:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/06 12:41:08 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_server.hpp"
#include "Server.hpp"

int main(void)
{

    Server SL_SERVER;

    if ( !SL_SERVER.start_server() )
    {
        std::cerr << "Falha ao criar o servidor!" << std::endl;
        return 1;
    }

    int server_fd = SL_SERVER.get_server_fd();
    
    // Criar epoll
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cerr << "Erro ao criar epoll" << std::endl;
        close(server_fd);
        return 1;
    }

    // Adicionar o socket do servidor ao epoll
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        std::cerr << "Erro ao adicionar o socket do servidor ao epoll" << std::endl;
        close(server_fd);
        close(epoll_fd);
        return 1;
    }
    std::cout << "Servidor iniciado. Aguardando conexões..." << std::endl;
    
    epoll_event events[100];
    while (true) {
        int num_events = epoll_wait(epoll_fd, events, 100, -1);
        if (num_events == -1) {
            std::cerr << "Erro ao esperar eventos epoll" << std::endl;
            break;
        }

        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == server_fd) {
                // Nova conexão de cliente
                sockaddr_in client_addr;
                socklen_t client_addr_size = sizeof(client_addr);
                int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_size);
                if (client_fd == -1) {
                    std::cerr << "Erro ao aceitar conexão de cliente" << std::endl;
                    continue;
                }
                std::cout << "Novo cliente conectado" << std::endl;

                // Adicionar o socket do cliente ao epoll
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1) {
                    std::cerr << "Erro ao adicionar o socket do cliente ao epoll" << std::endl;
                    close(client_fd);
                    continue;
                }
            } else {
                // Dados recebidos de um cliente
                char buffer[1024];
                int bytes_received = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    // Erro ou conexão fechada pelo cliente
                    if (bytes_received == 0) {
                        std::cout << "Cliente desconectado" << std::endl;
                    } else {
                        std::cerr << "Erro ao receber dados do cliente" << std::endl;
                    }
                    close(events[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                } else {
                    // Enviar mensagem recebida de volta ao cliente
                    send(events[i].data.fd, buffer, bytes_received, 0);
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);

    return 0;
}

