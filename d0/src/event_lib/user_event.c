
#ifndef WIN32
#include <unistd.h>
#endif				/*  */
#include <SDL.h>
#ifdef WIN32
#include "win32_lib.h"
#endif				/*  */
#include "screen_lib.h"
#include "nio_types.h"
#include "user_event.h"

static int busy;
static int x;
static int y;
static int color;
static int cursor_status;

PUBLIC void setup_screen_resize_event(int x1, int y1, int c)
{
    x = x1;
    y = y1;
    color = c;
    busy = TRUE;
}

PUBLIC void event_resize(void)
{
    resize_screen(x, y);
    clear_screen(color);
    busy = FALSE;
}

PUBLIC void setup_mouse_cursor_event(int i)
{
    cursor_status = i;
    busy = TRUE;
}

PUBLIC void mouse_cursor(void)
{
    SDL_ShowCursor(cursor_status);
    busy = FALSE;
}

PUBLIC void event_busy(void)
{
    while (busy) {
	usleep(10000);
    }
}
