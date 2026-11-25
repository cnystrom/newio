/******************************************************************************
 *
 *    nio.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
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

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _NIO_H
#define _NIO_H

#define VERSION                  (1)

// NIO Function Numbers
#define		NIO_NOP						0
#define		NIO_OUT_INIT					1
#define		NIO_OUT_EXIT					2
#define		NIO_OUT_CHAR_TO_STDOUT				3
#define		NIO_OUT_STRING_TO_STDOUT			4
#define		NIO_OUT_INT_TO_STDOUT				5
//#define		NIO_OUT_PUT_CHAR				6
//#define		NIO_OUT_SYSTEM_LOCAL				7
#define		NIO_OUT_LOAD_FONT				8
#define		NIO_OUT_LOAD_SYS_FONT				9
#define		NIO_OUT_FREE_FONT				10
#define		NIO_OUT_DRAW_TEXT				11
#define		NIO_OUT_SET_SCREEN				12
#define		NIO_OUT_CLEAR_SCREEN				13
#define		NIO_OUT_DRAW_RECTANGLE_RGB			14
#define		NIO_OUT_DRAW_POINT_RGB				15
#define		NIO_OUT_DRAW_LINE_RGB				16
#define		NIO_OUT_DRAW_ARC_RGB				17
#define		NIO_OUT_SOUND					18
#define		NIO_OUT_BEEP					19
#define		NIO_OUT_LOAD_MUSIC				20
#define		NIO_OUT_PLAY_MUSIC				21
#define		NIO_OUT_STOP_MUSIC				22
#define		NIO_OUT_LOAD_SOUND				23
#define		NIO_OUT_PLAY_SOUND				24
#define		NIO_OUT_FREE_SOUND				25
#define		NIO_OUT_LOAD_MOVIE				26
#define		NIO_OUT_PLAY_MOVIE				27
#define		NIO_OUT_LOAD_IMAGE				28
#define		NIO_OUT_DRAW_IMAGE				29
#define		NIO_OUT_FREE_IMAGE				30
//#define		NIO_OUT_TERM_INIT				31
//#define		NIO_OUT_PRINT					32
//#define		NIO_OUT_PRINT_AT				33
#define		NIO_OUT_PAINT					34
#define		NIO_OUT_CURSOR					35
#define		NIO_OUT_DRAW_IMAGE_SRC				36
#define		NIO_OUT_STOP_SOUND				37
#define		NIO_OUT_ACTIVATION_EVENT_CONTROL		38
#define		NIO_OUT_KEY_EVENT_CONTROL			39
#define		NIO_OUT_MOUSE_EVENT_CONTROL			40
#define		NIO_OUT_JOYSTICK_EVENT_CONTROL 			41
#define		NIO_OUT_ANTIALIASING_CONTROL			42
#define     	NIO_UI_INIT                    			43
#define     	NIO_UI_EXIT                    			44
#define     	NIO_SERVER_SCRIPT              			45
#define     	NIO_CLIENT_SCRIPT              			46
#define     	NIO_SEND_FILE_CHUNK            			47
#define     	NIO_CLOSE_FILE                 			48
#define     	NIO_LOAD_RESOURCE              			49
#define		_NUM_NIO_COMMANDS_				50

//#define _NIO_REPLY                (1024)

#define	NIO_IN_KEY                  (1)
#define NIO_IN_MOUSE_BUTTON         (2)
#define NIO_IN_MOUSE_MOVE           (3)
#define NIO_IN_MUSIC_PLAYING        (4)
#define NIO_IN_EVENT                (5)

#endif				// _NIO_H

#ifdef  __cplusplus
}
#endif
