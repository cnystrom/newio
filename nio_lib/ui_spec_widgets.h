/*	Public domain	*/

#ifndef _UI_SPEC_WIDGETS_H
#define _UI_SPEC_WIDGETS_H

typedef struct ui_window {
	struct ui_spec spec;
	struct json_object *text;
} UI_Window;

UI_Window *ui_spec_newWindowNamed(char *name, UI_EventFn handler,
				  int flags, char *title);
#define ui_spec_newWindow(handler, flags, title) ui_spec_newWindowNamed(NULL, handler, flags, title)

typedef struct ui_box {
	struct ui_spec spec;
} UI_Box;

UI_Box *ui_spec_newBoxNamed(void *parent, char *name, int hori, int flags);
#define ui_spec_newBoxHoriNamed(a,b,c) ui_spec_newBoxNamed(a, b, 1, c)
#define ui_spec_newBoxVertNamed(a,b,c) ui_spec_newBoxNamed(a, b, 0, c)
#define ui_spec_newBoxVert(a, b) ui_spec_newBoxNamed(a, NULL, 1, b)
#define ui_spec_newBoxHori(a, b) ui_spec_newBoxNamed(a, NULL, 1, b)

typedef struct ui_fixed {
	struct ui_spec spec;
} UI_Fixed;

UI_Fixed *ui_spec_newFixedNamed(void *parent, char *name, int flags);
#define ui_spec_newFixed(parent, flags) \
	ui_spec_newFixedNamed(parent, NULL, flags)

typedef struct ui_label {
	struct ui_spec spec;
	struct json_object *text;
} UI_Label;

UI_Label *ui_spec_newLabelNamed(void *parent,
				char *name, int flags, char *text);
#define ui_spec_newLabel(parent, flags, text) \
	ui_spec_newLabelNamed(parent, NULL, flags, text)

typedef struct ui_button {
	struct ui_spec spec;
	struct json_object *text;
} UI_Button;

UI_Button *ui_spec_newButtonNamed(void *parent,
				  char *name,
				  UI_EventFn handler,
				  int flags, char *title);
#define ui_spec_newButton(parent, handler, flags, title) \
	ui_spec_newButtonNamed(parent, NULL, handler, flags, title)

typedef struct ui_checkbox {
	struct ui_spec spec;
	int state;
	struct json_object *text;
} UI_Checkbox;

UI_Checkbox *ui_spec_newCheckboxNamed(void *parent,
				      char *name,
				      UI_EventFn handler,
				      int flags, char *title, int state);
#define ui_spec_newCheckbox(parent, handler, flags, title, state) \
	ui_spec_newCheckboxNamed(parent, NULL, handler, flags, title, state)

typedef struct ui_radio {
	struct ui_spec spec;
	struct json_object *items;
} UI_Radio;

UI_Checkbox *ui_spec_newRadioArr(void *parent, char *name,
				 UI_EventFn handler, int flags,
				 char **items);
UI_Checkbox *ui_spec_newRadioVbl(void *parent, char *name,
				 UI_EventFn handler, int flags, ...);

typedef struct ui_textbox {
	struct ui_spec spec;
	struct json_object *title;
	struct json_object *text;
} UI_Textbox;

UI_Textbox *ui_spec_newTextboxNamed(void *parent, char *name,
				    UI_EventFn handler, int flags,
				    char *title, char *text);
#define ui_spec_newTextbox(parent, handler, flags, title, text) \
	ui_spec_newTextboxNamed(parent, NULL, handler, flags, title, text)

#endif				// _UI_SPEC_WIDGETS_H
