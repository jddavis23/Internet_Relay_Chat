/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filesender.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:09:02 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/26 17:00:25 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filesender.hpp"

Filesender::Filesender()
{
	m_state = IDLE;     /* not doing anything initially */
};

/* Start sending a file on the given socket.
* Set the socket to be nonblocking.
* 'filename' is the name of the file to send.
* 'socket' is an open network connection.
*/
void Filesender::sendFile(int socket)
{
	m_buf_len = 0;
	m_buf_used = 0;
	m_socket = socket;
	m_state = SENDING;
}

/* Continue sending the file started by sendFile().
* Call this periodically.
* Returns nonzero when done.
*/
int Filesender::handle_io(int m_fd)
{
	///int nwrite;
	int nread;

	if (m_state == IDLE)
		return 2;
	while (1)
	{
		m_buf_len = recv(m_fd, m_buf, BUFFSIZE,  0);
		std::cout << m_fd << "\n";
		if (m_buf_len < 0)
		{
			m_state = IDLE;
			if (errno != EWOULDBLOCK)
            {
				std::cout << std::strerror(errno) << "\n";
				exit(0);
            }
            return -1;
		}
		if (m_buf_len == 0)
		{
			std::cout << "  Connection closed\n";
			return -1;
		}
		nread = m_buf_len;
		m_buf_len = send(2, m_buf, BUFFSIZE, 0);
		if (m_buf_len < 0)
		{
			std::cout << "  send() failed\n";
			return -1;
		}
		if (m_buf_len == 0)
			return 0;
	}
	return 0;
}