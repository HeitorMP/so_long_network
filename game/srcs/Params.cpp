/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Params.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:05:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/08 22:06:03 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Params.hpp"

Params::Params()
{
    ;
}

Params::~Params()
{
    ;
}

bool        Params::isGoodClient(std::string mode, std::string ip, std::string port)
{
    return (isModeValid(mode) && isIPValid(ip) && isPortValid(port));
}

bool        Params::isGoodServer(std::string mode, std::string port)
{
    return (isModeValid(mode) && isPortValid(port));
}

bool Params::isPortValid(std::string port)
{
     for (char c : port) {
        if (!std::isdigit(c))
            return (false);
    }

    int p = stoi(port);
    if (p < 1 || p > 65535)
        return (false);
    
    return (true);
}
bool Params::isIPValid(std::string ip)
{
    std::istringstream iss(ip);
    std::string segment;
    std::vector<int> segments;
    
    while (std::getline(iss, segment, '.')) {
        // Verifica se a parte do IP é um número válido
        if (segment.empty() || segment.size() > 3)
            return (false);
        for (char c : segment) {
            if (!std::isdigit(c))
                return (false);
        }
        int num = std::stoi(segment);
        if (num < 0 || num > 255)
            return (false);
        segments.push_back(num);
    }
    
    // Verifica se o IP tem 4 partes
    if (segments.size() != 4)
        return (false);
    
    return (true);
}
bool Params::isModeValid(std::string mode)
{
    return (mode == "-s" || mode == "-c");
}