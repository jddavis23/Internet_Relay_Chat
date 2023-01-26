/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:56:07 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/26 13:06:55 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main (int argc, char *argv[])
{
	int sockfd, portno;//, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char m_buf[BUFFSIZE];
	int ret;

	//char buffer[255];
	if (argc < 3)
	{
		std::cout << "usage\n";
		return 0;
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cout << "error\n";
		return 0;
	}
	server = gethostbyname(argv[1]);
	if (!server)
	{
		std::cout << "error no server\n";
		return 0;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << std::strerror(errno) << "\n";
		return 0;
	}
	else
		std::cout << "connection made\n";
	while (1)
	{
		ret = recv(sockfd, m_buf, BUFFSIZE,  0);
		send(1, m_buf, ret, 0);
	}
	return 0;
}