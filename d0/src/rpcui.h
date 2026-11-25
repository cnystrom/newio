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
 *
 */

#ifndef _NIO_RPCUI_H
#define _NIO_RPCUI_H

#ifndef SCRIPT_LEN
#define SCRIPT_LEN  (8000)
#endif

void nio_ui_init_1(void);
void nio_ui_exit_1(void);
void nio_client_script_1(void);
void nio_server_script_1(void);

#endif				// _NIO_RPCUI_H
