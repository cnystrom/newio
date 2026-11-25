/******************************************************************************
 *
 *    sock_lib.h
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _SOCK_LIB_H
#define _SOCK_LIB_H

#ifdef WIN32
#include <stdio.h>
#include <winsock.h>
#undef errno
#define errno WSAGetLastError()
#else				/*  */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <unistd.h>
#endif				/*  */

#ifndef _TYPES_H
#include "nio_types.h"
#endif				/*  */

#if defined(WIN32) && !defined(socklen_t)
#define socklen_t int
#endif				/*  */

#ifndef PRIVATE
#define PRIVATE static
#endif				/*  */

#ifndef PUBLIC
#define PUBLIC
#endif				/*  */

#ifndef SOCKET
#define SOCKET int
#endif				/*  */

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif				/*  */

#define TCPSENDBUFFERSIZE 131072
#define TCPRECEIVEBUFFERSIZE 131072

SOCKET establish_socket(uint16 portnum);
SOCKET open_socket(uint16 portnum);
SOCKET accept_socket(SOCKET s);
void close_socket(SOCKET s);
void puts_socket(SOCKET s, char *str);
u_int gets_socket(SOCKET s, char *str, u_int max_len);
SOCKET init_tcp_server(int port_num);
SOCKET init_tcp_client(const char *hostname, unsigned short portnum);
int read_socket(SOCKET s, byte * buf, int n);
int write_socket(SOCKET s, byte * buf, int n);

typedef struct {
	int sockid;
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
	int connected;
} udp_sock;

typedef udp_sock *udp_sock_ptr;

PUBLIC int init_udp_server(udp_sock_ptr s, int port);
PUBLIC int init_udp_inetd_server(udp_sock_ptr s);
PUBLIC int init_udp_client(udp_sock_ptr s, const char *hostname, int port);
PUBLIC int connect_udp(udp_sock_ptr s);
PUBLIC int read_udp(udp_sock_ptr s, byte_ptr msg, int len);
PUBLIC int write_udp(udp_sock_ptr s, const byte_ptr msg, int len);
PUBLIC void close_udp(udp_sock_ptr s);

#endif				/* _SOCK_LIB_H */
