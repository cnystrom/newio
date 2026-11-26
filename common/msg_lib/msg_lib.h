/******************************************************************************
 *
 *    msg_lib.h
 *
 *    Copyright (C) 2005  Chris Nystrom
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
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _MSG_LIB_H
#define _MSG_LIB_H

#ifndef _TYPES_H
#include "nio_types.h"
#endif

typedef sint32 msg_num_t;

#define MSG_BUF_EMPTY   (-1)
#define MSG_STOP        (-2)

extern void do_data_in(void);
extern int read_data(int fd, char *p, int len, int block);
extern int write_data(int fd, char *p, int len);

int msg_init_server(int in, int out);
int msg_init_client(int in, int out);

void msg_stop_server(void);
void msg_stop_client(void);
void msg_stop_ssh_client(void);

void msg_set_num(msg_num_t mn);
msg_num_t msg_get_num(void);

void msg_pack_string(const char *s);
void msg_unpack_string(char *s, int str_size);

void msg_pack_int32(int32 i32);
int32 msg_unpack_int32(void);
void msg_pack_int16(int16 i16);
int16 msg_unpack_int16(void);
void msg_pack_int8(int8 i8);
int8 msg_unpack_int8(void);

void msg_send(void);

void msg_pack_bytes(byte * s, uint32 str_size);
void msg_unpack_bytes(byte * s, uint32 * str_size);


#endif				/* _MSG_LIB_H */
