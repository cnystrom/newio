/******************************************************************************
 *
 *    buf_test.c
 *
 *    Copyright (C) 2007  Chris Nystrom
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
 *
 *    Soli Deo Gloria
 *
 */

#include <limits.h>
#include <stdio.h>
#ifdef UNIX
#include <stdlib.h>
#endif
#include "nio_types.h"
#include "buffer.h"

void display_buf(buffer_ptr b)
{
	int i;

	printf("\n----\n");
	printf("buffer =\n");
	for (i = 0; i < b->len; i++) {
		printf("buf[%d] = %d ", i, b->data[i]);

		if (b->data[i] > 32) {
			printf("%c\n", b->data[i]);
		} else {
			printf("\n");
		}
	}
	printf("----\n\n");
}

/*
bool cmp_buf(buffer_ptr b, char *s)
{
	int len;

	len = strlen(s);

	if (strncmp(b->data, s, len) == 0) {
		return (TRUE);
	} else {
		return (FALSE);
	}
}
*/

/*
void copy_buf(buffer_ptr b_in, buffer_ptr b_out)
{
	reset_buf(b_out);

	strlcpy(b_out->data, b_in->data, b_in->len);

	b_out->len = b_in->len;
}
*/

void pack_buffer(buffer_ptr b)
{
	int8 v1 = CHAR_MAX;
	int16 w1 = SHRT_MAX;
	int32 x1 = INT_MAX;
	char s1[] = "Test";

	printf("\n");
	printf("v1 = %d\n", v1);
	printf("w1 = %d\n", w1);
	printf("x1 = %d\n", x1);
	printf("s1 = |%s|\n", s1);

	reset_buf(b);

	pack_int8(b, v1);
	pack_int16(b, w1);
	pack_int32(b, x1);
	pack_string(b, s1);
}

#define STR_SIZE (16)

void unpack_buffer(buffer_ptr b)
{
	int8 v2 = 0;
	int16 w2 = 0;
	int32 x2 = 0;
	char s2[STR_SIZE] = "";

	v2 = unpack_int8(b);
	w2 = unpack_int16(b);
	x2 = unpack_int32(b);
	unpack_string(b, s2, STR_SIZE);

	printf("v2 = %d\n", v2);
	printf("w2 = %d\n", w2);
	printf("x2 = %d\n", x2);
	printf("s2 = |%s|\n\n", s2);
}

int main(void)
{
	buffer_t b;

	pack_buffer(&b);

	printf("\n|%s|\n\n", b.data);

//	display_buf(&b);

	unpack_buffer(&b);

	exit(0);
}
