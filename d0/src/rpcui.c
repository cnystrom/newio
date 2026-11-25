/******************************************************************************
 *
 *    rpcui.c
 *
 *    Copyright (C) 2007  Jason Reynolds
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/gpl.html
 *
 *    Contact Author at:
 *
 *    Jason Reynolds
 *    E-Mail: Jason@newio.org
 *    Blog:   http://www.promethean-tech.com/
 *    AIM:    UbiquitousEther
 *
 *    "Don't look at the way the world is and ask 'why?', look at the way that 
 *           the world could be and ask 'why not?'"
 */

#include <stdlib.h>
#include <string.h>
#include "msg_lib/msg_lib.h"
#include "audio_lib/audio_lib.h"
#include "event_lib/event_lib.h"
#include "event_lib/user_event.h"
#include "term_lib/term_lib.h"
#include "color_lib/color_lib.h"
#include "font_lib/font_lib.h"
#include "screen_lib/screen_lib.h"
#include "image_lib/image_lib.h"
#include "movie_lib/movie_lib.h"
#include "file_xfr.h"
#include "done.h"
#include "nio_events.h"
#include "rpcui.h"

/*
#include [agar library shit goes here]
#include [serializer library shit goes here]
#include ANY OTHER LIBS NEEDED HERE
*/

void nio_ui_init_1(void)
{
	char NSCRIPT[SCRIPT_LEN];
	msg_unpack_string(NSCRIPT, SCRIPT_LEN);
	//NSCRIPT now holds the value of your JSON string
	//I'm assuming you do serializer and other shit
	//here.
}

void nio_ui_exit_1(void)
{
	char EXCODE[SCRIPT_LEN];	//For now, using this as a script containing exit
	//code information?
	msg_unpack_string(EXCODE, SCRIPT_LEN);

	//EXCODE now holds value of Error/Exit code info
	//do random exit shit here
}

void nio_client_script_1(void)
{
	char nioscript[SCRIPT_LEN];
	msg_unpack_string(nioscript, SCRIPT_LEN);
	//Do shit with serializer and superswitch here
}

void nio_server_script_1(void)
{
	//This function sends small json scripts back to the server
	char nioscript[SCRIPT_LEN];
	/*
	   here you should somehow figure out a way
	   to get data from another buffer contianing the
	   JSON script updates and send it back to the 
	   server where it can be handled by our logging 
	   apparatus.  nioscript is the json script updates 
	   string.

	   nioscript="?";
	 */

	msg_pack_string(nioscript);
}
