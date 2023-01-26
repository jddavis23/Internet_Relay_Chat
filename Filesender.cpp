/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filesender.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:09:02 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/26 12:18:06 by jdavis           ###   ########.fr       */
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
		return 2;     /* nothing to do */
	/* If buffer empty, fill it */
	while (1)
	{
		/* Get one chunk of the file from disk */
		m_buf_len = recv(m_fd, m_buf, BUFFSIZE,  MSG_WAITALL);
		if (m_buf_len < 0)
		{
			/* All done; close the file and the socket. */
			//close(m_socket);
			m_state = IDLE;
			if (errno != EWOULDBLOCK)
            {
				std::cout << "  recv() failed\n";
				close(m_fd);
            }
            return -1;
		}
		if (m_buf_len == 0)
		{
			std::cout << "  Connection closed\n";
			close(m_fd);
			return -1;
		}
		nread = m_buf_len;
		m_buf_len = send(1, m_buf, BUFFSIZE, 0);
		if (m_buf_len < 0)
		{
			std::cout << "  send() failed\n";
			close(m_fd);
			return -1;
		}
		if (m_buf_len == 0)
			return 0;
	}
	return 0;
}