/******************************************************************************
 *
 *    nio_ui_lib.h
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

#include "ui_spec.h"

#ifndef _NIO_UI_LIB_H
#define _NIO_UI_LIB_H

#define NIO_UI_LIB_VER  "0.01"

//nio_ui_lib basic functions
//void nio_ui_init(const char *script);
void nio_ui_init(const char *app_name, const char *app_ver);
void nio_ui_exit(const char *script);
void nio_server_script(void);
void nio_client_script(const char *script);

#endif
