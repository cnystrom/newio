/******************************************************************************
 *    UNIVERSAL MARITIME GRAPHICAL INTERFACE LIBRARY FOR NewIO
 * 
 *    ui_spec.c
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
#include "nio_ui_lib.h"

static unsigned long UID = 0;	// XXX after 4.29billion this will overflow
struct ui_spec_q spec_root = TAILQ_HEAD_INITIALIZER(spec_root);	// root widget

void handlerfn(struct json_object *event)
{
	printf("Event Received\n%s\n", json_object_to_json_string(event));
	void *wid1;
	wid1 = ui_spec_newWindow(NULL, 0, "HAH");
	ui_spec_newButton(wid1, NULL, 0x0, "HEHE");
	ui_spec_flush(NULL);
}

static const char LONGBLAH[] =
    "<vedge> maybe just add a WindowScaleMinimum() function\n"
    "<vedge> which would just issue a WidgetSizeRequest() on the window followed by WindowSetGeometry()\n"
    "<phip> that would be a good solution\n"
    "<phip> A compromise on doing things the user doesn't expect is still needed though\n"
    "<vedge> you could try this:\n"
    "<vedge> AG_SizeReq req;\n"
    "<vedge> AG_WidgetSizeReq(win, &req);\n"
    "<vedge> AG_WindowSetGeometry(win, -1, -1, req.w, req.h);\n"
    "<vedge> AG_WindowUpdate(win);\n"
    "<vedge> i'm not sure the update is needed\n"
    "<vedge> yes, it is if widgets are being removed, to redraw background.\n"
    "<vedge> note that size requests do not return the minimum, it returns the \n"
    "<vedge> note that size requests do not return the minimum, it returns the \"best\" size\n"
    "<phip> I might put some logic around it in hopes of not jarring the user, but for now that fixes the weird window sizes\n"
    "<vedge> i'm not sure what is best to do by default for the minimum window sizes. there is no minimum (widgets just hide themselves if they are resized too small), but users might not expect that in many cases.\n"
    "<vedge> so right now, the \"best\" size is used as minimum unless changed explicitely\n"
    "<phip> i'll certainly suggest if I think of a better way, but I don't see one now\n"
    "<phip> having a loadable interface specification would allow for easy explicit sizings and positions like in AG_Fixed\n"
    "<phip> but that still wouldn't help me and my need to accommodate arbitrary additions and removals to visible windows\n"
    "<phip> I'll probably resize to the greater of current width or height and the suggested \"best\", so it never shrinks on the user\n"
    "<vedge-shop> but did the WidgetSizeReq() trick work?\n"
    "<phip> yeah yeah, sorry, yeah it worked\n"
    "<phip> he's gone!\n"
    "<phip> The dev.csoft.org svn server seems to be acting up\n"
    "<phip> svn: PROPFIND of '/agar/trunk': 405 Method Not Allowed (http://dev.csoft.org)\n"
    "<vedge> hmm\n"
    "<vedge> strange. the FPU on one of my machines appear to be screwed up. i've never seen anything like it.\n"
    "<vedge> any floating-point operation results in an illegal instruction trap.\n"
    "<phip> that's very strange\n"
    "<vedge_> dev.csoft.org should be working now\n" "<phip> it do, it do";

void pooptest(void)
{
	void *wid1, *wid2, *wid3, *wid4;

	wid1 =
	    ui_spec_newWindowNamed("suppwin", NULL, 0x0, "First Window!");

	ui_spec_flush(NULL);

	wid2 =
	    ui_spec_newWindowNamed("nestwin", NULL, 0x0, "CAMU SAYS DIE!");
	wid3 = ui_spec_newBoxHori(wid2, 0x0);
	ui_spec_newButton(wid3, handlerfn, 0x0, "Nasty as nose hair!");
	ui_spec_newButton(wid3, handlerfn, 0x0, "Fancy!");
	wid3 = ui_spec_newFixed(wid2, UI_FIXED_BOX);
	ui_spec_setGeometry(wid3, -1, -1, 300, 100);
	wid4 = ui_spec_newLabel(wid3, 0, "HEY GUYS I AM REALLY THINKING OF KILLING MYSEFL");	//*/
	ui_spec_setGeometry(wid4, 1, 1, -1, -1);
	wid4 = ui_spec_newCheckbox(wid3, handlerfn, 0, "Democrat", 0);
	ui_spec_setGeometry(wid4, 50, 18, -1, -1);
	//wid4 = ui_spec_newCheckbox(wid3, handlerfn, 0, "Asshat", 1);
	//ui_spec_setGeometry(wid4, 75, 199, -1, -1);
	//ui_spec_newTextbox(wid2, handlerfn, UI_TEXTBOX_MULTILINE|UI_EXPAND, NULL, LONGBLAH);

	ui_spec_newButton(wid1, handlerfn, 0x0, "HAHA");
	ui_spec_newButton(wid1, handlerfn, 0x0, "AHAH");

	/*
	   win2 = ui_spec_newWindow("nestwin2", NULL, 0x0, "Hello World!");
	   ui_spec_newButton(win2, "nestbut3", handlerfn, 0x0, "DICKS!");
	   ui_spec_newButton(win2, "nestbut4", handlerfn, 0x0, "VAGOOS!");// */

	ui_spec_flush(NULL);

	//ui_spec_destroy(win2);
	//ui_spec_flush(win2);
}


static void *findUID(struct ui_spec_q *node, unsigned long UID)
{
	struct ui_spec *t, *t2;

	TAILQ_FOREACH(t, node, cobjs) {
		if (t->UID == UID)
			return t;
		else {
			t2 = findUID(&t->children, UID);
			if (t2)
				return t2;
		}
	}
	return NULL;
}

void *ui_spec_findUID(unsigned long UID)
{
	return findUID(&spec_root, UID);
}

static void *findPath(struct ui_spec_q *node, char *path)
{
	struct ui_spec *chld;
	char node_name[UI_NAME_MAX + 1];
	char *s;

	if (!path || !node)
		return NULL;
	//printf("findPath(%s)", path);
	strlcpy(node_name, &path[1], sizeof(node_name));
	if ((s = strchr(node_name, '/')) != NULL) {
		*s = '\0';
	}
	//printf("%s\n", node_name);
	TAILQ_FOREACH(chld, node, cobjs) {
		//printf("\t%s - ", chld->name);
		if (strcmp(chld->name, node_name) != 0) {
			//printf("cont\n");
			continue;
		}
		if (s && !TAILQ_EMPTY(&chld->children)) {
			//printf("down %p\n", s);
			*s = '/';
			return findPath(&chld->children, s);
		}
		//printf("ret\n");
		return (chld);
	}
	return NULL;
}

void *ui_spec_findPath(char *path)
{
#if 0
	void *p;
	p = findPath(&spec_root, path);
	if (p)
		printf("ui_spec_findPath(%s) FOUND\n", path);
	else
		printf("ui_spec_findPath(%s) NOT FOUND\n", path);
	return p;
#else
	return findPath(&spec_root, path);
#endif
}

void *ui_spec_init(void *pwid, void *wid, enum widget_kind kind,
		   char *name, UI_EventFn handler, int flags)
{
	struct ui_spec *w = UISPEC(wid);
	struct ui_spec *p = UISPEC(pwid);
	char *c;

	if (wid == NULL)
		goto fail;
	if (pwid == NULL && (kind != WID_WINDOW && kind != WID_MENU))
		goto fail;
	if (pwid != NULL && kind == WID_WINDOW)
		goto fail;

	w->x = w->y = w->w = w->h = -1;
	w->kind = kind;
	w->handler = handler;
	w->parent = pwid;
	w->UID = ++UID;
	w->flags = flags;
	TAILQ_INIT(&w->children);
	w->changes = NULL;
	w->changeType = changeType_NONE;

	if (name)
		strlcpy(w->name, name, sizeof(w->name));
	else
		snprintf(w->name, sizeof(w->name), "wid_%lu", w->UID);

	/* Prevent ambiguous characters in the name. */
	for (c = w->name; *c != '\0'; c++) {
		if (*c == '/' || *c == '.' || *c == ':' || *c == ',')
			*c = '_';
	}

	if (pwid)
		TAILQ_INSERT_TAIL(&p->children, w, cobjs);
	else
		TAILQ_INSERT_TAIL(&spec_root, w, cobjs);

	{
		c = w->path =
		    malloc((p ? strlen(p->path) : 0) + 1 +
			   strlen(w->name) + 1);
		if (p) {
			strcpy(w->path, p->path);
			c += strlen(w->path);
		}
		*c = '/';
		c++;
		strcpy(c, w->name);
	}

	//printf("ui_spec_init %p %s %i\n", w, w->name, w->kind);
	//printf("ui_spec_init %p {\n\tname : %s\n\tkind : %i\n\thandler : %p\n\tparent : %p\n\tUID : %lu\n\tpath : %s\n}\n",
	//      w, w->name, w->kind, w->handler, w->parent, w->UID, w->path);

	return w;
      fail:
	printf("ui_spec_init(%p, %p, %i, %p) failure\n", pwid, wid, kind,
	       handler);
	free(w);		// XXX init probably should not free?
	return NULL;
}

static void spec_free(void *wid)
{
	struct ui_spec *w = wid;

	while (!TAILQ_EMPTY(&w->children)) {
		struct ui_spec *c = TAILQ_FIRST(&w->children);
		TAILQ_REMOVE(&w->children, c, cobjs);
		spec_free(c);
		if (c->path)
			free(c->path);
		free(c);
		//printf("free %p %p\n", c->path, c);
	}
	/*TAILQ_REMOVE(w->parent?(&UISPEC(w->parent)->children):&spec_root, n, cobjs);
	   if (w->path) free(w->path);
	   free(w);
	   printf("finalfree %p %p\n", w->path, w); */
}

void ui_spec_destroy(void *wid)
{
	struct ui_spec *w = wid;
	if (wid == NULL)
		return;

	/* XXX Temporary flush every time */
	w->changes = json_object_new_string(w->path);
	w->changeType = changeType_DEL;
	//ui_spec_flush(w);
	spec_free(w);		// free all children
}

/* OK HERE GOES --
	walk the tree and check the changeType value.
	
	add - attach json_type_object items to this array,
		some of which may contain add objects of their own
	mod - attach json_type_object items to this array, flat
	del - attach json_type_string paths to this array
 */
static void spec_flush(struct ui_spec_q *nodeq,
		       struct json_object *addNested,
		       struct json_object *add,
		       struct json_object *mod, struct json_object *del)
{
	struct ui_spec *chld;

	//printf("flush in, addN=%s\n", addNested?"yes":"no");
	TAILQ_FOREACH(chld, nodeq, cobjs) {
		struct json_object *addNestedChld = NULL;

		/* if wid is a container, check for its children's add arrays */
		if (!TAILQ_EMPTY(&chld->children)
		    && UI_KIND_CONTAINER(chld->kind)) {
			if (addNested
			    && chld->changeType == changeType_ADD)
				addNestedChld = json_object_new_array();
			spec_flush(&chld->children, addNestedChld, add,
				   mod, del);
		}

		switch (chld->changeType) {
		case changeType_ADD:
			if (addNested) {
				if (addNestedChld)
					json_object_object_add(chld->
							       changes,
							       "add",
							       addNestedChld);
				json_object_array_add(addNested,
						      chld->changes);
			} else {
				json_object_object_add(chld->changes,
						       "path",
						       json_object_new_string
						       (UISPEC
							(chld->parent)->
							path));
				json_object_array_add(add, chld->changes);
			}
			break;
		case changeType_MOD:
			json_object_array_add(mod, chld->changes);
			break;
		case changeType_DEL:
			json_object_array_add(del,
					      json_object_new_string(chld->
								     path));
			break;
		}

		chld->changes = NULL;	/* JSON handles freeing it. I think. */
		chld->changeType = changeType_NONE;
	}
}

void ui_spec_flush(void *node)
{
	struct ui_spec_q *q = node ? &UISPEC(node)->children : &spec_root;
	struct json_object *root, *root2;
	struct json_object *addNested, *add, *mod, *del;
	char *jsonstr;
	int len, i;

	addNested = json_object_new_array();
	add = json_object_new_array();
	mod = json_object_new_array();
	del = json_object_new_array();

	if (q == &spec_root)
		spec_flush(q, addNested, add, mod, del);
	else if (UISPEC(node)->changeType == changeType_DEL) {
		struct ui_spec *n = node;
		json_object_array_add(del, n->changes);
		TAILQ_REMOVE(n->
			     parent ? (&UISPEC(n->parent)->
				       children) : &spec_root, n, cobjs);
		if (n->path)
			free(n->path);
		free(n);
	}

	root = json_object_new_object();
	root2 = json_object_new_object();

	if ((len = json_object_array_length(addNested))) {
		for (i = 0; i < len; i++)
			json_object_array_add(add,
					      json_object_array_get_idx
					      (addNested, i));
	} else
		json_object_put(addNested);
	if (json_object_array_length(add))
		json_object_object_add(root2, "add", add);
	else
		json_object_put(add);
	if (json_object_array_length(mod))
		json_object_object_add(root2, "mod", mod);
	else
		json_object_put(mod);
	if (json_object_array_length(del))
		json_object_object_add(root2, "rem", del);
	else
		json_object_put(del);

	// we're ready to go ~
	//jsonstr = json_object_to_json_string(root2);
	//printf("\nfinal-%s\n\n", jsonstr);
	//ui_do_str(jsonstr);

	json_object_object_add(root, "niogui", root2);
	jsonstr = json_object_to_json_string(root);
	nio_client_script(jsonstr);
	json_object_put(root2);
}

void ui_spec_setGeometry(void *widget, int x, int y, int w, int h)
{
	struct ui_spec *wid = UISPEC(widget);

	if (!wid)
		return;

	/* for new widgets not yet flushed, we can just append the keys */
	if (wid->changeType == changeType_ADD) {
		if (x != -1) {
			wid->x = x;
			json_object_object_add(wid->changes, "x",
					       json_object_new_int(x));
		}
		if (y != -1) {
			wid->y = y;
			json_object_object_add(wid->changes, "y",
					       json_object_new_int(y));
		}
		if (w != -1) {
			wid->w = w;
			json_object_object_add(wid->changes, "w",
					       json_object_new_int(w));
		}
		if (h != -1) {
			wid->h = h;
			json_object_object_add(wid->changes, "h",
					       json_object_new_int(h));
		}
	}
	/* otherwise we have to [figure out what lol] */
	else {

	}
}

void ui_spec_getGeometry(void *widget, UI_Size * geom)
{

}

void ui_spec_setHandler(void *wid, UI_EventFn handler)
{
	if (!wid)
		return;
	UISPEC(wid)->handler = handler;
}

void ui_spec_eventHandle(struct json_object *event)
{
	void *wid;
	struct json_object *val;

	//if (val = json_object_object_get(event, "UID"))
	//      wid = ui_spec_findUID(json_object_get_int(val));
	//else 
	if ((val = json_object_object_get(event, "path")))
		wid = ui_spec_findPath(json_object_get_string(val));
	else {
		printf("ui_spec_eventHandle failure to find widget\n");
		return;
	}

	if (UISPEC(wid)->handler)
		UISPEC(wid)->handler(event);
}

#define PRINT_TABS(depth) do {int i; for(i=0; i<depth; i++) printf("\t");} while(0)
static void print_node(struct ui_spec_q *node, int depth)
{
	struct ui_spec *t;

	TAILQ_FOREACH(t, node, cobjs) {
		PRINT_TABS(depth);
		printf("node %s\n", t->name);
		print_node(&t->children, depth + 1);
	}
}

void ui_print_tree(void)
{
	print_node(&spec_root, 0);
}
