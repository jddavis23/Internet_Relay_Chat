/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filesender.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:09:05 by jdavis            #+#    #+#             */
/*   Updated: 2023/01/25 12:26:33 by jdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESENDER_HPP
#define FILESENDER_HPP

#include "irc.hpp"

class Filesender {
	char m_buf[BUFFSIZE];    /* current chunk of file */
	int m_buf_len;          /* bytes in buffer */
	int m_buf_used;         /* bytes used so far; <= m_buf_len */
	enum { IDLE, SENDING } m_state; /* what we're doing */
	int m_socket;

	public:
		Filesender();
		void sendFile(int socket);
		int handle_io(int m_fd);
};

#endif