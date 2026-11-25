/******************************************************************************
 *
 *    linuxq2.h
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

/*
 *
 * Following code derived from:
 * "Using predicate waits with Win32 threads",
 *  D. Howard, C/C++ Users Journal, May 2000 
 *
 *
 */

#ifndef __LINUXQ2_H__
#define __LINUXQ2_H__

#ifdef WIN32
#include <SDL_thread.h>
#else
#include <SDL/SDL_thread.h>
#endif

#include "queue.h"
#define	QUEUESIZE 25
QUEUETYPE(Interthread, buffer_t, QUEUESIZE);
QUEUECODE(static __inline__, Interthread, buffer_t, QUEUESIZE);

// BOUNDED INTERTHREAD QUEUE
typedef struct BoundedInterthreadQueue {
	SDL_mutex *m_csec;	// data store lock
	SDL_sem *m_semSpaceAvailable;	// semaphore
	SDL_sem *m_semElementAvailable;	// semaphore
	InterthreadQue q;
} INTERTHREADQUEUE;
typedef INTERTHREADQUEUE *PINTERTHREADQUEUE;

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
	itq->m_semSpaceAvailable = SDL_CreateSemaphore(QUEUESIZE);
	if (itq->m_semSpaceAvailable == 0) {
		// panic
		return 1;
	}
	// create the 'get' counter semaphore
	itq->m_semElementAvailable = SDL_CreateSemaphore(QUEUESIZE);
	if (itq->m_semElementAvailable == 0) {
		// panic
		return 1;
	}
	InitInterthreadQue(&itq->q);

	// no elements available initially
	for (i = 0; i < QUEUESIZE; i++) {
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
	if (!InterthreadQueFull(&itq->q)) {
		EnqueInterthread(&itq->q, p);
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
	if (!InterthreadQueEmpty(&itq->q)) {
		DequeInterthread(&itq->q, p);
	} else {
		p->index = 0;
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
	flag = InterthreadQueEmpty(&itq->q);
	SDL_mutexV(itq->m_csec);

	return flag;
}

void BoundedInterthreadQueueDestroy(PINTERTHREADQUEUE itq)
{
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
#endif
