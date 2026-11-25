/*	Public domain	*/

/* nio_ui consists of two parts: spec and do.
 * spec is the API in nio_lib to build an interface on the client
 * do takes commands from spec and translates them into calls to the
 *  AGAR interface library.
 *
 * Between the two are JSON strings (http://json.org/), implemented by the
 * library JSON_C (http://oss.metaparadigm.com/json-c/), which is required.
 * 
 * 
 */

#ifndef _NIOUI_H
#define _NIOUI_H

#include "json.h"

/* UNIVERSAL FLAGS */
#define UI_HFILL		0x1
#define UI_VFILL		0x2
#define UI_EXPAND		(UI_HFILL|UI_VFILL)
#define UI_DISABLED		0x4
#define UI_HIDDEN		0x8
/* WINDOW FLAGS */
#define UI_WINDOW_MODAL         0x00010 // Place in foreground
#define UI_WINDOW_KEEPABOVE     0x00020 // Keep window above
#define UI_WINDOW_KEEPBELOW     0x00040 // Keep window below
#define UI_WINDOW_DENYFOCUS     0x00080 // Widgets cannot gain focus
#define UI_WINDOW_NOTITLE       0x00100 // Disable the titlebar
#define UI_WINDOW_NOBORDERS     0x00200 // Disable the window borders
#define UI_WINDOW_NOHRESIZE     0x00400 // Disable horizontal resize
#define UI_WINDOW_NOVRESIZE     0x00800 // Disable vertical resize
#define UI_WINDOW_NOCLOSE       0x01000 // Disable close button
#define UI_WINDOW_NOMINIMIZE    0x02000 // Disable minimize button
#define UI_WINDOW_NOMAXIMIZE    0x04000 // Disable maximize button
#define UI_WINDOW_NOBACKGROUND  0x08000 // Don't fill the background
//#define UI_WINDOW_NOUPDATERECT  0x10000 // Don't update rectangle
#define UI_WINDOW_NORESIZE      (UI_WINDOW_NOHRESIZE|UI_WINDOW_NOVRESIZE)
#define UI_WINDOW_PLAIN         (UI_WINDOW_NOTITLE|UI_WINDOW_NOBORDERS)
/* BOX FLAGS */
#define UI_BOX_HOMOGENOUS  0x10  // Divide space evenly
#define UI_BOX_FRAME       0x20  // Display a frame
/* FIXED FLAGS */
//define UI_FIXED_NO_UPDATE	0x04	/* Don't call WINDOW_UPDATE() */
#define UI_FIXED_FILLBG		0x10	/* Fill background */
#define UI_FIXED_BOX		0x20	/* Draw a box */
#define UI_FIXED_INVBOX		0x40	/* Draw a box (inverted) */
#define UI_FIXED_FRAME		0x80	/* Draw a frame */
/* LABEL FLAGS */
/* BUTTON FLAGS */
#define UI_BUTTON_STICKY        0x10    // Toggle state
/* CHECKBOX FLAGS */
/* RADIO FLAGS */
/* TEXTBOX FLAGS */
#define UI_TEXTBOX_MULTILINE		0x0010	/* Multi-line input mode */
#define UI_TEXTBOX_PASSWORD			0x0020	/* Password (hidden) input */
#define UI_TEXTBOX_ABANDON_FOCUS	0x0040	/* Abandon focus on return */
#define UI_TEXTBOX_READONLY			0x0080	/* Equivalent to WidgetDisable() */
#define UI_TEXTBOX_INT_ONLY			0x0100	/* Accepts only valid strtol() input */
#define UI_TEXTBOX_FLT_ONLY			0x0200	/* Accepts only valid strtof() input */
#define UI_TEXTBOX_CATCH_TAB		0x0400	/* Enter literal tabs into text */
/* NOTEBOOK FLAGS */



enum widget_kind {
	WID_GENERIC,
	/* container objects */
	WID_WINDOW = 1,
	WID_BOXHORI = 2,
	WID_BOXVERT = 3,
	WID_FIXED = 4,
	/* embeddable objects */
	WID_LABEL = 8,
	WID_BUTTON = 9,
	WID_CHECKBOX = 10,
	WID_RADIO = 11,
	WID_SCROLLBAR,
	WID_TEXTBOX = 13,
	WID_MENU = 15, /* menu bar */
	WID_MENUNODE = 16, /* menu popup */
	WID_MENUITEM = 17, /* menu item */
	WID_NOTEBOOK = 18,
	WID_NOTEBOOKTAB = 19,
	WID_COMBO,
	WID_UCOMBO,
	WID_SEPARATOR,
	WID_PANE,
	WID_TLIST,
	WID_TOOLBAR
};

#define UI_KEY_IS(key, is) (!strncmp(key, is, sizeof(is)))
#define UI_NAME_MAX 64
#define UI_KIND_CONTAINER(kind)	\
	(kind == WID_WINDOW		||	kind == WID_FIXED		|| \
	 kind == WID_BOXHORI	||	kind == WID_BOXVERT		|| \
	 kind == WID_MENU		||	kind == WID_MENUNODE	|| \
	 kind == WID_NOTEBOOK	||	kind == WID_NOTEBOOKTAB	)

#endif // _NIOUI_H