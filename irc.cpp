/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:33:12 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/24 11:49:38 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main(int argc, char *argv[])
{
	int sockfd;
	int port_nmb;
	int bind_rt;
	struct sockaddr_in addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (argc != 3 || !argv[0] || sockfd < 0 )
	{
		std::cout << "usage: ./ircserv <port number> <password>\n";
		return (-1);
	}
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	port_nmb = atoi(argv[1]);
	bind_rt = bind(sockfd, (const struct sockaddr *) &addr, sizeof(addr));
	if (bind_rt < 0)
	{
		std::cout << "bind couldnt occur\n" << bind_rt << " " << std::strerror(errno) << "\n";
		return 0;
	}
	std::cout << sockfd << "\n";	
	return (0);
}