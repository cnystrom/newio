/******************************************************************************
 *
 *    queue.h
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

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "buffer.h"

#define	QUEUE_SIZE 25

typedef struct {
	int length;
	int head;
	int tail;
	buffer_t buf[(25)];
} que;

void init_que(que * q);
int que_full(que * q);
int que_empty(que * q);
int enque(que * q, buffer_t * val);
int deque(que * q, buffer_t * val);
int peek_que(que * q, buffer_t * val);

#endif				/* __QUEUE_H__ */
