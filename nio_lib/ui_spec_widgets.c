/******************************************************************************
 *    UNIVERSAL MARITIME GRAPHICAL INTERFACE LIBRARY FOR NewIO
 * 
 *    ui_spec_widgets.c
 *
 *    Copyright (C) 2007  John Blitch & Jason Reynolds
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
 *    John Blitch
 *    E-Mail: johnb@newio.org
 *
 *    Jason Reynolds
 *    E-Mail: Jason@newio.org
 *    Blog:   http://www.promethean-tech.com/
 *    AIM:    UbiquitousEther
 *
 *    Dub it off your man, don't spend that ten bucks
 *    I did it for the advance, the back end sucks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui_spec.h"

UI_Window *ui_spec_newWindowNamed(char *name, UI_EventFn handler,
				  int flags, char *title)
{
	struct ui_window *wid;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_window));
	if (!wid)
		return NULL;
	wid = ui_spec_init(NULL, wid, WID_WINDOW, name, handler, flags);
	if (!wid)
		return NULL;

	wid->text = json_object_new_string(title);
	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	json_object_object_add(obj, "text", wid->text);
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}

UI_Box *ui_spec_newBoxNamed(void *parent, char *name, int hori, int flags)
{
	struct ui_box *wid = NULL;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_button));
	if (!wid)
		return NULL;
	if (hori)
		wid =
		    ui_spec_init(parent, wid, WID_BOXHORI, name, NULL,
				 flags);
	else
		wid =
		    ui_spec_init(parent, wid, WID_BOXVERT, name, NULL,
				 flags);
	if (!wid)
		return NULL;

	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}

UI_Fixed *ui_spec_newFixedNamed(void *parent, char *name, int flags)
{
	struct ui_fixed *wid = NULL;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_fixed));
	if (!wid)
		return NULL;
	wid = ui_spec_init(parent, wid, WID_FIXED, name, NULL, flags);
	if (!wid)
		return NULL;

	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}

UI_Button *ui_spec_newButtonNamed(void *parent, char *name,
				  UI_EventFn handler, int flags,
				  char *title)
{
	struct ui_button *wid;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_button));
	if (!wid)
		return NULL;
	wid = ui_spec_init(parent, wid, WID_BUTTON, name, handler, flags);
	if (!wid)
		return NULL;

	wid->text = json_object_new_string(title);
	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	json_object_object_add(obj, "text", wid->text);
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}

UI_Label *ui_spec_newLabelNamed(void *parent, char *name, int flags,
				char *text)
{
	struct ui_label *wid;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_label));
	if (!wid)
		return NULL;
	wid = ui_spec_init(parent, wid, WID_LABEL, name, NULL, flags);
	if (!wid)
		return NULL;

	wid->text = json_object_new_string(text);
	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	json_object_object_add(obj, "text", wid->text);
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}

UI_Checkbox *ui_spec_newCheckboxNamed(void *parent, char *name,
				      UI_EventFn handler, int flags,
				      char *title, int state)
{
	struct ui_checkbox *wid;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_checkbox));
	if (!wid)
		return NULL;
	wid =
	    ui_spec_init(parent, wid, WID_CHECKBOX, name, handler, flags);
	if (!wid)
		return NULL;

	wid->text = json_object_new_string(title);
	wid->state = state ? 1 : 0;
	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	json_object_object_add(obj, "text", wid->text);
	json_object_object_add(obj, "state",
			       json_object_new_boolean(wid->state));
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}

UI_Textbox *ui_spec_newTextboxNamed(void *parent, char *name,
				    UI_EventFn handler, int flags,
				    char *title, char *text)
{
	struct ui_textbox *wid;
	struct json_object *obj;

	wid = malloc(sizeof(struct ui_textbox));
	if (!wid)
		return NULL;
	wid = ui_spec_init(parent, wid, WID_TEXTBOX, name, handler, flags);
	if (!wid)
		return NULL;

	if (title)
		wid->title = json_object_new_string(title);
	if (text)
		wid->text = json_object_new_string(text);
	UISPEC(wid)->flags = flags;
	UISPEC(wid)->changeType = changeType_ADD;
	obj = UISPEC(wid)->changes = json_object_new_object();

	json_object_object_add(obj, "kind",
			       json_object_new_int(UISPEC(wid)->kind));
	json_object_object_add(obj, "name",
			       json_object_new_string(UISPEC(wid)->name));
	if (title)
		json_object_object_add(obj, "title", wid->title);
	if (text)
		json_object_object_add(obj, "text", wid->text);
	json_object_object_add(obj, "flags",
			       json_object_new_int(UISPEC(wid)->flags));

	return wid;
}
