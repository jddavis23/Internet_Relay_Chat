/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:33:12 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/23 16:00:47 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main(int argc, char *argv[])
{
	int sockfd;

	sockfd = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (argc != 3)
	{
		std::cout << "usage: ./ircserv <port number> <password>\n";
		return (-1);
	}
	if (sockfd)
		std::cout << "it worked\n" <<  argv[0];
	else
		std::cout << "it didnt work\n";	
	return (0);
}