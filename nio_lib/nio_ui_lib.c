/******************************************************************************
 *
 *    nio_ui_lib.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>

#ifdef UNIX
#include <sys/param.h>
#include <unistd.h>
#endif

#ifdef WIN32
#include <winsock2.h>
#include "win32_lib.h"
#endif

#include "nio_lib.h"		// would rather not include this, only needed for randomize()

#include "nio.h"
#include "nio_ui_lib.h"
#include "nio_log.h"		// ../common/nio_log/nio_log.h
#include "msg_lib.h"		// ../common/msg_lib/msg_lib.h

//nio_ui_lib base/core functions

/* either nio_ui_init OR nio_app_init will be called.
 * ui_init will indicate we continue with AGAR
 * app_init will indicate we shut down AGAR and use
 * traditional nio_lib.
 */
/*void nio_ui_init(const char *script)
{
     msg_set_num(NIO_UI_INIT);
     msg_pack_string(script);
     msg_send();
}*/

#ifdef UNIX
PRIVATE void sig_usr_ui(int signo)
{
	if (signo == SIGUSR1) {
		nio_log_print("received SIGUSR1\n");

		msg_stop_server();
//              msg_kill_server();
//              nio_StopEventQueue();
		nio_log_print("calling nio_log_close()...\n");
		nio_log_close();
		exit(0);
	}
}
#endif

void nio_ui_init(const char *app_name, const char *app_ver)
{
	char nio_ver[8] = NIO_UI_LIB_VER;
	char hostname[MAXHOSTNAMELEN];
	char cwd[256];
	char s[BUFSIZ];

	snprintf(s, BUFSIZ, "%s.%s.log", app_name, app_ver);
	nio_log_open(s);
	nio_log_print("nio_app_init(): log file |%s| opened.\n", s);

#ifdef UNIX
	if (signal(SIGUSR1, sig_usr_ui) == SIG_ERR)
		nio_log_print("can't catch SIGUSR1\n");
#endif

#ifdef WIN32
	init_winsock();
#endif

	//nio_StartEventQueue();
	//nio_log_print("nio_app_init(): Event queue started.\n", s);

	//msg_init_server(STDIN, STDOUT);

	gethostname(hostname, MAXHOSTNAMELEN);

	getcwd(cwd, sizeof(cwd));

	msg_set_num(NIO_UI_INIT);
	msg_pack_string(nio_ver);
	msg_pack_string(hostname);
	msg_pack_string(app_name);
	msg_pack_string(app_ver);
	msg_pack_string(cwd);
	msg_send();

	randomize();
}

void nio_ui_exit(const char *script)
{
	msg_set_num(NIO_UI_EXIT);
	msg_pack_string(script);
	msg_send();
}

/* nio_server_scripts
 messages from the client (ie events)
 */
void nio_server_scripts(void)
{
	struct json_tokener *tok;
	struct json_object *new_obj;
	char script[8000];

	msg_unpack_string(script, 8000);

	tok = json_tokener_new();
	new_obj = json_tokener_parse_ex(tok, script, 8000);
	json_tokener_free(tok);

	if (new_obj && !is_error(new_obj)) {
		ui_spec_eventHandle(new_obj);
	};
}

void nio_client_script(const char *script)
{
	msg_set_num(NIO_CLIENT_SCRIPT);
	msg_pack_string(script);
	msg_send();
}
