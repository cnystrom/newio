/******************************************************************************
 *
 *    buffer.c
 *
 *    Copyright (C) 2005-2007  Chris Nystrom
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
 *    E-Mail: cnystrom@newio.org
 *    Blog:   http://newio.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WIN32
#include <unistd.h>
#include <netinet/in.h>
#endif
#ifdef WIN32
#include <winsock2.h>
#endif
#include "nio_types.h"
#include "nio_log.h"
#include "str_lib.h"
#include "buffer.h"
#include "base64.h"

#define BUFF_ERR1 "buffer overflow"
#define BUFF_ERR2 "no data left"

void reset_buf(buffer_ptr b)
{
	b->len = 0;
	b->read_index = 0;
	b->data[0] = 0;
}

/*
void print_buffer(buffer_ptr b)
{
	printf("\nb->len = %d\n", b->len);
	printf("b->read_index = %d\n", b->read_index);
	printf("b->data = |%s|\n\n", b->data);
}
*/

int pack_int8(buffer_ptr b, int8 i)
{
	return (pack_int(b, (int) i));
}

int8 unpack_int8(buffer_ptr b)
{
	return ((int8) unpack_int(b));
}

int pack_int16(buffer_ptr b, int16 i)
{
	return (pack_int(b, (int) i));
}

int16 unpack_int16(buffer_ptr b)
{
	return ((int16) unpack_int(b));
}

int pack_int32(buffer_ptr b, int32 i)
{
	return (pack_int(b, (int) i));
}

int32 unpack_int32(buffer_ptr b)
{
	return ((int32) unpack_int(b));
}

#define INT_MAX_LEN (12)	// enough to hold string representation of MAX_INT

int pack_int(buffer_ptr b, int i)
{
	int j, len;
	char num[INT_MAX_LEN];
	byte *bp;

	if (b->len == 0) {
		sprintf(num, "%d", i);
	} else {
		sprintf(num, " %d", i);
	}

	len = strlen(num);

	if ((b->len + len) >= BUF_SIZE) {
		nio_log_print("pack_int(): %s\n", BUFF_ERR1);
		return (-1);
	}

	bp = (byte *) num;

	for (j = 0; j < len; j++) {
		b->data[b->len++] = *(bp++);
	}

	b->data[b->len] = 0;

//      printf("pack_int(): len  = %d\n", b->len);
//      printf("pack_int(): data = |%s|\n", b->data);

	return (0);
}

int unpack_int(buffer_ptr b)
{
	int i, count = 0;
	char num[INT_MAX_LEN];
	byte *bp;

	bp = (byte *) num;

	if (b->read_index > b->len) {
		return (-1);
	}

//      printf("unpack_int(): len        = %d\n", b->len);
//      printf("unpack_int(): read_index = %d\n", b->read_index);

	while (b->data[b->read_index] != ' ' && b->read_index < b->len) {

		i = b->read_index;

//              printf("unpack_int(): read_index = %d\n", i);
//              printf("unpack_int(): b->data[i] = %d %c\n", b->data[i],
//                      b->data[i]);

		*(bp++) = b->data[i];

		b->read_index++;

		count++;

//              printf("unpack_int(): count = %d\n", count);

		if (count >= INT_MAX_LEN || b->read_index > b->len) {
			nio_log_print("unpack_int(): buffer overrun\n");
			return (-1);
		}
	}

	*(bp) = 0;
	b->read_index++;

//      printf("unpack_int(): num = |%s|\n", num);

	return (atoi(num));
}

int pack_string(buffer_ptr b, const char *s)
{
	int i;
	int len;
	byte *bp;

	len = strlen((char *) s);

	if (pack_int(b, len)) {
		nio_log_print("pack_string(): pack_int() failed\n");
		return -2;
	}

	if ((b->len + len + 1) >= BUF_SIZE) {
		nio_log_print("pack_string(): %s\n", BUFF_ERR1);
		return (-1);
	}

	b->data[b->len++] = ' ';

	bp = (byte *) s;

	for (i = 0; i < len; i++) {
		b->data[b->len++] = *(bp++);
	}

	b->data[b->len] = 0;

	return (0);
}

int unpack_string(buffer_ptr b, char *s, int str_size)
{
	int i;
	int len;
	byte *bp;

	if ((b->read_index + INT32_SIZE) > b->len) {
		nio_log_print("unpack_string(): %s\n", BUFF_ERR2);
		return (-1);
	}

	len = unpack_int(b);

	if (len > str_size) {
		nio_log_print("unpack_string(): %s\n", BUFF_ERR2);
		return (-1);
	}

	if ((b->read_index + len) > b->len) {
		nio_log_print("unpack_string(): %s\n", BUFF_ERR2);
		return (-1);
	}

	bp = (byte *) s;

	for (i = 0; i < len; i++) {
		*(bp++) = b->data[b->read_index++];
	}

	*(bp) = 0;
	b->read_index++;

	return (0);
}

#define OUTBUFFERSIZE BUF_SIZE
static byte outbuffer[OUTBUFFERSIZE];

int pack_bytes(buffer_ptr b, byte * s, uint32 len)
{
	int i;
	byte *bp;
	uint32 outlen = OUTBUFFERSIZE;

	nio_log_print("pack_bytes(): size in is %d\n", len);

	if (len > BUF_SIZE * 3 / 4) {
		nio_log_print("pack_bytes(): bytes too big for buffer");
		return -1;
	}

	base64_encode(s, len, outbuffer, &outlen);

	nio_log_print("pack_bytes(): size out is %d\n", outlen);

	len = outlen;

	if (pack_int(b, len)) {
		nio_log_print("pack_bytes(): pack_int() failed\n");
		return -2;
	}

	if ((b->len + len + 1) >= BUF_SIZE) {
		nio_log_print("pack_bytes(): %s\n", BUFF_ERR1);
		return (-1);
	}

	b->data[b->len++] = ' ';

	bp = (byte *) outbuffer;

	for (i = 0; i < len; i++) {
		b->data[b->len++] = *(bp++);
	}

	b->data[b->len] = 0;

	return (0);
}

int unpack_bytes(buffer_ptr b, byte * s, uint32 * str_size)
{
	int i;
	uint32 len;
	byte *bp;
	uint32 decoded_length = *str_size;

	if ((b->read_index + INT32_SIZE) > b->len) {
		nio_log_print("unpack_bytes(): %s\n", BUFF_ERR2);
		return (-1);
	}

	len = unpack_int(b);

	if ((b->read_index + len) > b->len) {
		nio_log_print("unpack_bytes(): %s\n", BUFF_ERR2);
		return (-1);
	}

	bp = (byte *) outbuffer;

	for (i = 0; i < len; i++) {
		*(bp++) = b->data[b->read_index++];
	}

	*(bp) = 0;
	b->read_index++;

	nio_log_print("unpack_bytes(): size in is %d\n", len);

	base64_decode(outbuffer, len, s, &decoded_length);

	if (decoded_length > *str_size) {
		nio_log_print("unpack_bytes(): %s\n", BUFF_ERR2);
		return (-1);
	}

	*str_size = decoded_length;

	nio_log_print("unpack_bytes(): size out is %d\n", *str_size);

	return (0);
}
