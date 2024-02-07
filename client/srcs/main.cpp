// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.cpp                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/06 09:47:51 by hmaciel-          #+#    #+#             */
// /*   Updated: 2024/02/07 01:42:26 by hmaciel-         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/so_long_client.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::TcpSocket socket;

	sf::Socket::Status status = socket.connect("127.0.0.1", 3000);
	if (status != sf::Socket::Done)
	{
		std::cout << "error connecting to the server\n";
		return 1;
	}
	socket.setBlocking(false);

	char data[100];
	std::size_t received;
	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "erro recebendo dados\n";
	}
	if (data[0] == 'F')
	{
		socket.disconnect();
		return 1;
	}

	std::string	message = "name=heitor x=1 y=2";
	socket.send((char *)message.c_str(), message.size());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if (socket.receive(data, 100, received) != sf::Socket::Done)
		{
			std::cout << "erro recebendo dados\n";
		}
        window.clear();
        window.draw(shape);
        window.display();
    }
}