/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filesender.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:09:02 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/25 12:26:56 by jdavis           ###   ########.fr       */
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
	int nwrite;
	int nread;

	if (m_state == IDLE)
		return 2;     /* nothing to do */
	/* If buffer empty, fill it */
	if (m_buf_used == m_buf_len)
	{
		/* Get one chunk of the file from disk */
		m_buf_len = read(m_fd, m_buf, BUFFSIZE);
		if (m_buf_len == 0) {
			/* All done; close the file and the socket. */
			close(m_fd);
			close(m_socket);
			m_state = IDLE;
			return 1;
		}
		m_buf_used = 0;
	}

	/* Send one chunk of the file */
	assert(m_buf_len > m_buf_used);
	nwrite = write(m_socket, m_buf + m_buf_used, m_buf_len - m_buf_used);
	if (nwrite < 0) 
		fatal_error("write failed");
	m_buf_used += nwrite;
	return 0;
}