/******************************************************************************
 *
 *    bitqueue.c
 *
 *    Copyright (C) 20057  Chris Nystrom
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

/*
 *
 * Following code derived from:
 * "Using predicate waits with Win32 threads",
 *  D. Howard, C/C++ Users Journal, May 2000 
 *
 */

#if defined(UNIX) || defined(__MINGW32__)
#include <unistd.h>
#endif

#include "bitqueue.h"

int BoundedInterthreadQueueCreate(PINTERTHREADQUEUE itq)
{
	int i;

	// initialize the critical section protecting the deque
	itq->m_csec = SDL_CreateMutex();
	if (itq->m_csec == 0) {
		// panic
		return 1;
	}
	// create the 'put' counter semaphore
	itq->m_semSpaceAvailable = SDL_CreateSemaphore(QUEUE_SIZE);

	if (itq->m_semSpaceAvailable == 0) {
		// panic
		return 1;
	}
	// create the 'get' counter semaphore
	itq->m_semElementAvailable = SDL_CreateSemaphore(QUEUE_SIZE);

	if (itq->m_semElementAvailable == 0) {
		// panic
		return 1;
	}

	init_que(&itq->q);

	// no elements available initially
	for (i = 0; i < QUEUE_SIZE; i++) {
		SDL_SemWait(itq->m_semElementAvailable);
	}

	return 0;
}

void BoundedInterthreadQueuePut(PINTERTHREADQUEUE itq, buffer_t * p)
{
	SDL_SemWait(itq->m_semSpaceAvailable);

	// several threads can get this far, but only one at a time
	// will get by the critical section
	SDL_mutexP(itq->m_csec);

	if (!que_full(&itq->q)) {
		enque(&itq->q, p);
	}

	SDL_mutexV(itq->m_csec);

	// signal element is available
	SDL_SemPost(itq->m_semElementAvailable);
}

buffer_t *BoundedInterthreadQueueGet(PINTERTHREADQUEUE itq, buffer_t * p)
{
	// wait for available element
	SDL_SemWait(itq->m_semElementAvailable);

	// several threads can get this far, but only one at a time
	// will get by the critical section
	SDL_mutexP(itq->m_csec);

	if (!que_empty(&itq->q)) {
		deque(&itq->q, p);
	} else {
		p->len = 0;
		p->read_index = 0;
		p->data[0] = 0;
	}

	SDL_mutexV(itq->m_csec);

	// signal element is available
	SDL_SemPost(itq->m_semSpaceAvailable);

	return p;
}

int BoundedInterthreadQueueEmpty(PINTERTHREADQUEUE itq)
{
	int flag;

	SDL_mutexP(itq->m_csec);
	flag = que_empty(&itq->q);
	SDL_mutexV(itq->m_csec);

	return flag;
}

void BoundedInterthreadQueueDestroy(PINTERTHREADQUEUE itq)
{
//      Why are we putting something in the queue when destroying?
	BoundedInterthreadQueuePut(itq, &itq->q.buf[0]);

	usleep(10000);

	if (itq->m_semSpaceAvailable != 0) {
		SDL_DestroySemaphore(itq->m_semSpaceAvailable);
	}

	if (itq->m_semElementAvailable != 0) {
		SDL_DestroySemaphore(itq->m_semElementAvailable);
	}

	if (itq->m_csec != 0) {
		SDL_DestroyMutex(itq->m_csec);
	}
}

void BoundedInterthreadQueueKill(PINTERTHREADQUEUE itq)
{
	if (itq->m_semSpaceAvailable != 0) {
		SDL_DestroySemaphore(itq->m_semSpaceAvailable);
	}

	if (itq->m_semElementAvailable != 0) {
		SDL_DestroySemaphore(itq->m_semElementAvailable);
	}

	if (itq->m_csec != 0) {
		SDL_DestroyMutex(itq->m_csec);
	}
}
