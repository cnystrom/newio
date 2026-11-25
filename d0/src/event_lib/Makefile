
TARGETS =	$(TARGET1)

#==============================================================================

FILENAME1 =	event_lib
TARGET1 =	$(FILENAME1).a

HEADERS1 = 	\
		$(FILENAME1).h \
		user_event.h \
		$(NULL)

CCFILES1 =	\
		handler.c \
		keyboard.c \
		mouse.c \
		user_event.c \
		$(NULL)

OBJS1 =		${CCFILES1:.c=.o}

LIBS1 = 	\
		$(NULL)

#==============================================================================

CC =		gcc

COPTS =		-O3 -g -Wall  $(shell sdl-config --cflags)

INCLUDES = 	\
		-I../../../common \
		-I../../../common/msg_lib \
		-I../../../common/win32_lib \
		-I../screen_lib \
		-I../movie_lib \
		$(NULL)

LIBDIRS = 	\
		$(NULL)

#ifndef TARGET_OS
TARGET_OS = unix
#endif
 
CFLAGS =	$(COPTS) $(INCLUDES) -DDEBUG -D$(TARGET_OS)
#CFLAGS =	$(COPTS) $(INCLUDES)

LFLAGS =	$(LIBDIRS)

#default compilation rules
%.o:		%.c
		$(CC) -c $< $(CFLAGS) -o $@

all: 		$(TARGETS)

default:	$(TARGETS)

new:		clean default

#==============================================================================

$(TARGET1):	$(OBJS1) $(HEADERS1) $(LIBS1)
		ar rcs $(TARGET1) $(LIBS1) $(OBJS1)
		ranlib $(TARGET1)

indent:
		dos2unix *.h *.c
		indent -kr -i4 *.h *.c 

clean:
		rm -f $(TARGETS) *.o *.a core a.out *~
 
