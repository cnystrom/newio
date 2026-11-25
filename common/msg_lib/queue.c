/******************************************************************************
 *
 *    queue.c
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
 *    Blog:   http://newio.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include "queue.h"

void init_que(que * q)
{
	q->length = 0;
	q->head = 0;
	q->tail = 0;
}

int que_full(que * q)
{
	return ((QUEUE_SIZE) == q->length);
}

int que_empty(que * q)
{
	return (0 == q->length);
}

int enque(que * q, buffer_t * val)
{
	if ((QUEUE_SIZE) == q->length) {
		return -1;
	}

	q->length++;
	q->buf[q->tail] = *val;
	q->tail = ((q->tail + 1) % (QUEUE_SIZE));

	return 0;
}

int deque(que * q, buffer_t * val)
{
	if (0 == q->length) {
		return -1;
	}

	q->length--;
	*val = q->buf[q->head];
	q->head = (q->head + 1) % (QUEUE_SIZE);

	return 0;
}

int peek_que(que * q, buffer_t * val)
{
	if (0 == q->length) {
		return -1;
	}

	*val = q->buf[q->head];

	return 0;
}
