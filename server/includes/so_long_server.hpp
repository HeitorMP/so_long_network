/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_server.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:49:13 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/02/07 13:23:49 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include <sys/epoll.h>
# include <sys/socket.h>
# include <cstring>
# include <netinet/in.h>
# include <unistd.h>
# include <signal.h>