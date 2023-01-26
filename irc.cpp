/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:33:12 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/26 13:03:15 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Filesender.hpp"

void checkPassword(char *pwd, int fd)
{
	int ret;
	char m_buf[BUFFSIZE];
	int i;
	
	while (1)
	{
		ret = send(fd, "Enter password: ", 17, 0);
		if (ret < 0)
		{
			std::cout << std::strerror(errno);
			close(fd);
			return;
		}
		i = 0;
		while (ret > 0)
		{
			ret = recv(fd, m_buf, BUFFSIZE,  0);
			if (ret <= 0)
			{
				if (ret == 0 && i < (int)sizeof(pwd))
					std::cout << "Wrong password\n";
				break ;
			}
			while (i < ret)
			{
				if (pwd[i] != m_buf[i])
				{
					std::cout << "Wrong password\n";
					break ;
				}
				++i;
			}
		}
	}


}

int main(int argc, char *argv[])
{
	int sockfd;
	int port_nmb;
	int bind_rt;
	struct sockaddr_in addr;
	struct sockaddr_in cli_addr;
	int sockfd_chld;
	socklen_t clilen;
	int lst_rt;
	int nfds;
	int current_size;
	int i;
	Filesender	file;

	//char BUFF[buff_size];
	int ret;
	struct pollfd mypoll[MAX_CLIENT];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (argc != 3 || !argv[0] || sockfd < 0 )
	{
		std::cout << "usage: ./ircserv <port number> <password>\n";
		return (-1);
	}
	int status = fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
	if (status == -1)
		std::cout << "fcntl error\n";
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	port_nmb = atoi(argv[1]);
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port_nmb);
	bind_rt = bind(sockfd, (const struct sockaddr *) &addr, sizeof(addr));
	if (bind_rt < 0)
	{
		std::cout << "bind couldnt occur\n" << bind_rt << " " << std::strerror(errno) << "\n";
		return 0;
	}
	lst_rt = listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	mypoll[0].fd = sockfd;
  	mypoll[0].events = POLLIN;
	nfds = 1;
	while (1)
	{
		current_size = nfds;
		ret = poll(mypoll, nfds, 300);
		if (ret < 0)
		{
			std::cout << "poll() failed\n";
			return 0;
		}
		if (ret > 0)
		{
			i = 0;
			while (i < current_size)
			{
				if (mypoll[i].revents == POLL_IN)
				{
					file.sendFile(sockfd);
					file.handle_io(mypoll[i].fd);
				}
				++i;
			}
		}
		while (1 && nfds < MAX_CLIENT)
		{
			sockfd_chld = accept(sockfd, NULL, NULL);//(struct sockaddr *) &cli_addr, &clilen);
			if (sockfd_chld < 0 && errno != EAGAIN)
			{
				std::cout << std::strerror(errno);
				exit(0);
				break ;
			}
			if (sockfd_chld > 0)
			{
				std::cout << "  New incoming connection\n";
				checkPassword(argv[2], sockfd_chld);
				mypoll[nfds - 1].fd = sockfd_chld;
				mypoll[nfds - 1].events = POLLIN;
				nfds++;
			}
		}
	}
	std::cout << "here\n";
	// int flags = fcntl(sockfd_chld, F_GETFL, 0);
	// std::cout << flags << "\n";
	// memset(&mypoll, 0, sizeof(mypoll));
	// mypoll.fd = sockfd_chld;
	// mypoll.events = POLL_IN;
	// while (1)
	// {
	// 	if (poll(&mypoll, 1, 100) == 1)
	// 	{
	// 		//ret = read(sockfd_chld, BUFF, buff_size);
	// 		recv(sockfd_chld, buff, buff_size, int flags)

	// }
	return (0);
}