/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Params.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:10:23 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/08 22:02:13 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <vector>
# include <string>
# include <sstream>

class Params
{
    private:
        Params();
        
    public:
        ~Params();
        
        static bool isGoodClient(std::string, std::string, std::string);
        static bool isGoodServer(std::string, std::string);
        static bool isModeValid(std::string);
        static bool isIPValid(std::string);
        static bool isPortValid(std::string);

        char            getFormattedMode(std::string);
        int             getFormattedPort(std::string);
        std::string     getFormattedIP(std::string);
};