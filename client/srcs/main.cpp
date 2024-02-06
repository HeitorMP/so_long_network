/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:47:51 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/06 12:16:47 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_client.hpp"

const int PORT = 3000;
const char* SERVER_IP = "127.0.0.1"; // Endereço IP do servidor

int main() {
    // Criar socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "Erro ao criar socket" << std::endl;
        return 1;
    }

    // Configurar endereço do servidor
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Conectar ao servidor
    if (connect(client_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "Erro ao conectar ao servidor" << std::endl;
        close(client_fd);
        return 1;
    }

    std::cout << "Conectado ao servidor. Digite 'sair' para encerrar a conexão." << std::endl;

    while (true) {
        std::string message;
        std::cout << "Digite uma mensagem: ";
        std::getline(std::cin, message);

        // Verificar se o usuário deseja sair
        if (message == "sair") {
            break;
        }

        // Enviar mensagem para o servidor
        if (send(client_fd, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Erro ao enviar mensagem para o servidor" << std::endl;
            close(client_fd);
            return 1;
        }

        // Receber resposta do servidor
        char buffer[1024];
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            std::cerr << "Erro ao receber resposta do servidor" << std::endl;
            close(client_fd);
            return 1;
        } else if (bytes_received == 0) {
            std::cout << "Conexão encerrada pelo servidor" << std::endl;
            break;
        }

        // Exibir resposta do servidor
        std::cout << "Resposta do servidor: " << std::string(buffer, bytes_received) << std::endl;
    }

    // Fechar o socket
    close(client_fd);

    return 0;
}