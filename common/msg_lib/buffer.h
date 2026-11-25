/******************************************************************************
 *
 *    buffer.h
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _BUFFER_H
#define _BUFFER_H

#ifndef _TYPES_H
#include "nio_types.h"
#endif				// _TYPES_H

#ifndef BUF_SIZE
#define BUF_SIZE (81920)
#endif

#define BUF_SIZE_LEN (5)	/* 5 chars in above num */

typedef struct {
	byte data[BUF_SIZE];
	int len;
	int read_index;
} buffer_t;

typedef buffer_t *buffer_ptr;

void reset_buf(buffer_ptr);
void print_buffer(buffer_ptr b);

int pack_int8(buffer_ptr, int8);
int8 unpack_int8(buffer_ptr);

int pack_int16(buffer_ptr, int16);
int16 unpack_int16(buffer_ptr);

int pack_int32(buffer_ptr, int32);
int32 unpack_int32(buffer_ptr);

int pack_int(buffer_ptr, int);
int unpack_int(buffer_ptr);

int pack_string(buffer_ptr, const char *s);
int unpack_string(buffer_ptr, char *s, int str_size);

int pack_bytes(buffer_ptr b, byte * s, uint32 len);
int unpack_bytes(buffer_ptr b, byte * s, uint32 * str_size);
#endif				// _BUFFER_H
