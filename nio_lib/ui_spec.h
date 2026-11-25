/*	Public domain	*/

#include "nioui.h"
#include <sys/queue.h>

#ifndef _UI_SPEC_H
#define _UI_SPEC_H

/* UISPEC()
	use this on any of the complex types to access
	the primative ui_spec members:
	UISPEC(button)->name
*/
#define UISPEC(spec)	((struct ui_spec *)(spec))

/* UI_EventFn()
	callback when an event arrives for the widget.
	passed a JSON object with at least the following:
		int		UID
		string	path
		string	event name
*/
typedef void (*UI_EventFn) (struct json_object *);

enum ui_spec_changeType {
	changeType_NONE = 0,	// json object is empty
	changeType_ADD = 1,	// json object is a dictionary type for an add array
	changeType_MOD = 2,	// json object is a dictionary type for a mod array
	changeType_DEL = 3	// json object is a string type for a del array
};

TAILQ_HEAD(ui_spec_q, ui_spec);

/* UI_Spec
	The generic widget type, contained as the first member
	of all subclasses. Represents attributes common
	to all widgets, see UISPEC().
*/
typedef struct ui_spec {
	char name[UI_NAME_MAX + 1];	/* name unique among siblings */
	char *path;		/* path, including name */
	unsigned long UID;	/* unique ID */
	enum widget_kind kind;	/* see ui_lib.h */
	unsigned long flags;	/* flags */
	UI_EventFn handler;	/* event handler */
	void *parent;		/* object's container, NULL at root */

	int x, y;
	int w, h;

	struct ui_spec_q children;	/* child objects */
	 TAILQ_ENTRY(ui_spec) cobjs;	/* entry in child object queue */

	int changeType;
	struct json_object *changes;
} UI_Spec;

typedef struct ui_size {
	int x, y;
	int w, h;
} UI_Size;

/* Widget Lookup Functions */
void *ui_spec_findUID(unsigned long);
void *ui_spec_findPath(char *);

/* Widget init function*/
void *ui_spec_init(void *parent, void *wid, enum widget_kind kind,
		   char *name, UI_EventFn handler, int flags);

void ui_spec_setGeometry(void *widget, int x, int y, int w, int h);
void ui_spec_getGeometry(void *widget, UI_Size * geom);
void ui_spec_setHandler(void *wid, UI_EventFn handler);

/* Widget delete functions */
void ui_spec_destroy(void *);
#define ui_spec_destroyUID(uid) ui_spec_widget_destroyPtr(ui_spec_fndUID(uid))
#define ui_spec_destroyPath(ptr) ui_spec_widget_destroyPtr(ui_spec_findPath(path))

/* Synchronize the client terminal with any changes */
void ui_spec_flush(void *node);

void ui_spec_eventHandle(struct json_object *event);

/* Individual widget functions */
#include "ui_spec_widgets.h"

#endif				// _UI_SPEC_H
