/******************************************************************************
 *
 *    event.c
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

#include "nio.h"
#include "nio_log.h"
#include "nio_types.h"
#include "nio_events.h"
#include "msg_lib.h"

//#include "queue.h"
#include "event.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
//#include "reply.h"

#define	IOQUEUESIZE 50


//QUEUETYPE(IOEvent, SDL_Event, IOQUEUESIZE);
//QUEUECODE(static __inline__, IOEvent, SDL_Event, IOQUEUESIZE);
typedef struct {
	int length;
	int head;
	int tail;
	SDL_Event buf[(50)];
} IOEventQue;;

static __inline void InitIOEventQue(IOEventQue * q)
{
	q->length = 0;
	q->head = 0;
	q->tail = 0;
}

static __inline int IOEventQueFull(IOEventQue * q)
{
	return ((50) == q->length);
}

static __inline int IOEventQueEmpty(IOEventQue * q)
{
	return (0 == q->length);
}

static __inline int EnqueIOEvent(IOEventQue * q, SDL_Event * val)
{
	if ((50) == q->length) {
		return -1;
	}
	q->length++;
	q->buf[q->tail] = *val;
	q->tail = ((q->tail + 1) % (50));
	return 0;
}

static __inline int DequeIOEvent(IOEventQue * q, SDL_Event * val)
{
	if (0 == q->length) {
		return -1;
	}
	q->length--;
	*val = q->buf[q->head];
	q->head = (q->head + 1) % (50);
	return 0;
}

static __inline int PeekqueIOEvent(IOEventQue * q, SDL_Event * val)
{
	if (0 == q->length) {
		return -1;
	}
	*val = q->buf[q->head];
	return 0;
};

// BOUNDED INTERTHREAD QUEUE
typedef struct IOEventQueue {
	SDL_mutex *m_csec;	// data store lock
	IOEventQue q;
} IOEVENTQUEUE;
typedef IOEVENTQUEUE *PIOEVENTQUEUE;

PRIVATE IOEVENTQUEUE eq;

PRIVATE int IOEventQueueCreate(PIOEVENTQUEUE ioeq)
{
	// initialize the critical section protecting the deque
	ioeq->m_csec = SDL_CreateMutex();
	if (ioeq->m_csec == 0) {
		// panic
		return 1;
	}
	InitIOEventQue(&ioeq->q);
	return 0;
}

PRIVATE void IOEventQueuePut(PIOEVENTQUEUE ioeq, SDL_Event * p)
{
	SDL_mutexP(ioeq->m_csec);
	if (!IOEventQueFull(&ioeq->q)) {
		EnqueIOEvent(&ioeq->q, p);
	}
	SDL_mutexV(ioeq->m_csec);
}

PRIVATE int IOEventQueueGet(PIOEVENTQUEUE ioeq, SDL_Event * p)
{
	int flag = TRUE;
	SDL_mutexP(ioeq->m_csec);
	if (!IOEventQueEmpty(&ioeq->q)) {
		DequeIOEvent(&ioeq->q, p);
	} else {
		flag = FALSE;
	}
	SDL_mutexV(ioeq->m_csec);
	return flag;
}

PRIVATE int IOEventQueuePeek(PIOEVENTQUEUE ioeq, SDL_Event * p)
{
	int flag = TRUE;
	SDL_mutexP(ioeq->m_csec);
	if (!IOEventQueEmpty(&ioeq->q)) {
		PeekqueIOEvent(&ioeq->q, p);
	} else {
		flag = FALSE;
	}
	SDL_mutexV(ioeq->m_csec);
	return flag;
}

PRIVATE void IOEventQueueDestroy(PIOEVENTQUEUE ioeq)
{
	if (ioeq->m_csec != 0) {
		SDL_DestroyMutex(ioeq->m_csec);
	}
}

PRIVATE int music_status = FALSE;
PUBLIC void handle_music_status(int flag)
{
	nio_log_print("handle_music_status(): %d\n", flag);
	music_status = flag;
}

PRIVATE int file_xfer_status = -1;
PUBLIC void handle_file_xfer_status(int flag)
{
	nio_log_print("handle_file_xfer_status(): %d\n", flag);
	file_xfer_status = flag;
}

PUBLIC void reset_file_xfer_status()
{
	file_xfer_status = -1;
}

PUBLIC int get_file_xfer_status()
{
	return file_xfer_status;
}

PRIVATE int file_xfer_end = -1;
PUBLIC void handle_file_xfer_end(int flag)
{
	nio_log_print("handle_file_xfer_end(): %d\n", flag);
	file_xfer_end = flag;
}

PUBLIC void reset_file_xfer_end()
{
	file_xfer_end = -1;
}

PUBLIC int get_file_xfer_end()
{
	return file_xfer_end;
}

PUBLIC int get_music_status()
{
	return music_status;
}

PUBLIC void handle_event(void)
{
	SDL_Event event;

	event.type = msg_unpack_int8();

//      nio_log_print("handle_event(): type = %d\n", event.type);

	switch (event.type) {
	case SDL_ACTIVEEVENT:
//              nio_log_print("handle_event(): active event\n");
		event.active.gain = msg_unpack_int8();	// Uint 8
		event.active.state = msg_unpack_int8();	// Uint 8
//      wlog("PUT  active %x %x\n",event.active.gain,event.active.state);
		break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
//              nio_log_print("handle_event(): key event\n");
		event.key.state = msg_unpack_int8();	// Uint8
		event.key.keysym.scancode = msg_unpack_int8();	// Uint8
		event.key.keysym.sym = (SDLKey) msg_unpack_int32();	// Uint32
		event.key.keysym.mod = (SDLMod) msg_unpack_int32();	// Uint32
		event.key.keysym.unicode = msg_unpack_int16();	// Uint16
//      wlog("PUT  key %x %x %x %x %x\n",event.key.state,event.key.keysym.scancode,event.key.keysym.sym,event.key.keysym.mod,event.key.keysym.unicode);
		handle_key_press(&event);
		break;
	case SDL_MOUSEMOTION:
//              nio_log_print("handle_event(): mouse motion event\n");
		event.motion.state = msg_unpack_int8();	// Uint8 
		event.motion.x = msg_unpack_int16();	// Uint16
		event.motion.y = msg_unpack_int16();	// Uint16
		event.motion.xrel = msg_unpack_int16();	// Sint16
		event.motion.yrel = msg_unpack_int16();	// Sint16
//      wlog("PUT  mouse motion %x %x %x %x %x\n",event.motion.state,event.motion.x,event.motion.y,event.motion.xrel,event.motion.yrel);
		handle_mouse_move(&event);
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
//              nio_log_print("handle_event(): mouse button event\n");
		event.button.button = msg_unpack_int8();	// Uint8 
		event.button.state = msg_unpack_int8();	// Uint8 
		event.button.x = msg_unpack_int16();	// Uint16 
		event.button.y = msg_unpack_int16();	// Uint16 
//      wlog("PUT  mouse button %x %x %x %x\n",event.button.button,event.button.state,event.button.x,event.button.y);
		handle_mouse_button(&event);
		break;
	case SDL_JOYAXISMOTION:
//              nio_log_print("handle_event(): joystick axis event\n");
		event.jaxis.which = msg_unpack_int8();	// Uint8 
		event.jaxis.axis = msg_unpack_int8();	// Uint8 
		event.jaxis.value = msg_unpack_int16();	// Sint16
//      wlog("PUT  joy axis %x %x %x\n",event.jaxis.which,event.jaxis.axis,event.jaxis.value);
		handle_joy_move(&event);
		break;
	case SDL_JOYBALLMOTION:
//              nio_log_print("handle_event(): joystick ball event\n");
		event.jball.which = msg_unpack_int8();	// Uint8  
		event.jball.ball = msg_unpack_int8();	// Uint8  
		event.jball.xrel = msg_unpack_int16();	// Sint16 
		event.jball.yrel = msg_unpack_int16();	// Sint16 
//      wlog("PUT  joy ball %x %x %x %x\n",event.jball.which,event.jball.ball,event.jball.xrel,event.jball.yrel);
		handle_joyball_move(&event);
		break;
	case SDL_JOYHATMOTION:
//              nio_log_print("handle_event(): joystick hat event\n");
		event.jhat.which = msg_unpack_int8();	// Uint8 
		event.jhat.hat = msg_unpack_int8();	// Uint8 
		event.jhat.value = msg_unpack_int8();	// Uint8 
//      wlog("PUT  joy hat %x %x %x\n",event.jhat.which,event.jhat.hat,event.jhat.value);
		handle_joyhat_move(&event);
		break;
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
//              nio_log_print("handle_event(): joystick button event\n");
		event.jbutton.which = msg_unpack_int8();	// Uint8 
		event.jbutton.button = msg_unpack_int8();	// Uint8 
		event.jbutton.state = msg_unpack_int8();	// Uint8 
//      wlog("PUT  joy button %x %x %x\n",event.jbutton.which,event.jbutton.button,event.jbutton.state);
		handle_joy_button(&event);
		break;
	case SDL_QUIT:
//              nio_log_print("handle_event(): quit event\n");
//      wlog("PUT  quit\n");
		break;
	case SDL_VIDEORESIZE:
//              nio_log_print("handle_event(): video resize event\n");
		event.resize.w = msg_unpack_int32();	// Uint32 
		event.resize.h = msg_unpack_int32();	// Uint32 
//      wlog("PUT  resize %x %x\n",event.resize.w,event.resize.h);
		break;
	case SDL_USEREVENT:
//              nio_log_print("handle_event(): user event\n");
		event.user.code = msg_unpack_int32();	// Uint32 
		event.user.data1 = (void *) msg_unpack_int32();	// Uint32 
		event.user.data2 = (void *) msg_unpack_int32();	// Uint32 
//      wlog("PUT  user event %x %x %x\n",event.user.code,event.user.data1,event.user.data2);

/*
		if (event.user.code == NIO_EVENT_REPLY) {
			handle_reply((int32) event.user.data1,
				     (int32) event.user.data2);
			return;
		}
*/
		if (event.user.code == NIO_MUSIC_STATUS) {
			handle_music_status((int32) event.user.data1);
			return;
		}
		if (event.user.code == NIO_FILE_XFER_STATUS) {
			handle_file_xfer_status((int32) event.user.data1);
			return;
		}
		if (event.user.code == NIO_FILE_XFER_END) {
			handle_file_xfer_end((int32) event.user.data1);
			return;
		}
		break;
	default:
		nio_log_print("handle_event(): unknown event\n");
		break;
	}

	IOEventQueuePut(&eq, &event);
	return;
}

PUBLIC int nio_PollEvent(SDL_Event * event)
{
	int res = IOEventQueueGet(&eq, event);
	if (res) {
		switch (event->type) {
		case SDL_ACTIVEEVENT:
//      wlog("GET active %x %x\n",event->active.gain,event->active.state);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
//      wlog("GET key %x %x %x %x %x\n",event->key.state,event->key.keysym.scancode,event->key.keysym.sym,event->key.keysym.mod,event->key.keysym.unicode);
			break;
		case SDL_MOUSEMOTION:
//      wlog("GET mouse motion %x %x %x %x %x\n",event->motion.state,event->motion.x,event->motion.y,event->motion.xrel,event->motion.yrel);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
//      wlog("GET mouse button %x %x %x %x\n",event->button.button,event->button.state,event->button.x,event->button.y);
			break;
		case SDL_JOYAXISMOTION:
//      wlog("GET joy axis %x %x %x\n",event->jaxis.which,event->jaxis.axis,event->jaxis.value);
			break;
		case SDL_JOYBALLMOTION:
//      wlog("GET joy ball %x %x %x %x\n",event->jball.which,event->jball.ball,event->jball.xrel,event->jball.yrel);
			break;
		case SDL_JOYHATMOTION:
//      wlog("GET joy hat %x %x %x\n",event->jhat.which,event->jhat.hat,event->jhat.value);
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
//      wlog("GET joy button %x %x %x\n",event->jbutton.which,event->jbutton.button,event->jbutton.state);
			break;
		case SDL_QUIT:
//      wlog("GET quit\n");
			break;
		case SDL_VIDEORESIZE:
//      wlog("GET resize %x %x\n",event->resize.w,event->resize.h);
			break;
		case SDL_USEREVENT:
//      wlog("GET user event %x %x %x\n",event->user.code,event->user.data1,event->user.data2);
			break;
		default:
			break;
		}
	}
	return res;
}

PUBLIC int nio_PeekEvent(SDL_Event * event)
{
	return IOEventQueuePeek(&eq, event);
}

PUBLIC void nio_StartEventQueue()
{
	IOEventQueueCreate(&eq);
}

PUBLIC void nio_StopEventQueue()
{
	IOEventQueueDestroy(&eq);
}
