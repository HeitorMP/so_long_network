/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:01:26 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 11:42:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <unistd.h>
# include <SFML/Network.hpp>


class Client {
    
    private:
        int                 _x;
        int                 _y;
        int                 _score;

        std::string         _name;

    public:
        Client(std::string, int, int);
        ~Client();

        /* GETTERS & SETTERS */
        std::string get_name();
        int         get_fd();
        int         get_x();
        int         get_y();

        void        set_name(std::string);
        void        set_x(int);
        void        set_y(int);
                     
};

std::ostream &	operator<<( std::ostream & o, Client & i );