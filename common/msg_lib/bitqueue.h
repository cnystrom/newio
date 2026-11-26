/******************************************************************************
 *
 *    bitqueue.h
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

/*
 *
 * Following code derived from:
 * "Using predicate waits with Win32 threads",
 *  D. Howard, C/C++ Users Journal, May 2000 
 *
 */

#ifndef __BITQUEUE_H__
#define __BITQUEUE_H__

#ifdef WIN32
#include <SDL_thread.h>
#else
#include <SDL/SDL_thread.h>
#endif

#include "queue.h"

typedef struct BoundedInterthreadQueue {
	SDL_mutex *m_csec;	// data store lock
	SDL_sem *m_semSpaceAvailable;	// semaphore
	SDL_sem *m_semElementAvailable;	// semaphore
	que q;
} INTERTHREADQUEUE;

typedef INTERTHREADQUEUE *PINTERTHREADQUEUE;

int BoundedInterthreadQueueCreate(PINTERTHREADQUEUE itq);

void BoundedInterthreadQueuePut(PINTERTHREADQUEUE itq, buffer_t * p);
buffer_t *BoundedInterthreadQueueGet(PINTERTHREADQUEUE itq, buffer_t * p);
int BoundedInterthreadQueueEmpty(PINTERTHREADQUEUE itq);
void BoundedInterthreadQueueDestroy(PINTERTHREADQUEUE itq);
void BoundedInterthreadQueueKill(PINTERTHREADQUEUE itq);

#endif				/* __BITQUEUE_H__ */
