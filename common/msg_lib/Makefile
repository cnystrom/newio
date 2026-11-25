
TARGETS =	$(MSG_LIB_BIN)

#==============================================================================

MSG_LIB_BIN =	msg_lib.a
MSG_LIB_PATH =	$(NULL)

MSG_LIB_H =     \
                buffer.h \
                queue.h \
                bitqueue.h \
                msg_lib.h \
                base64.h \
                $(NULL)

MSG_LIB_C =     \
                buffer.c \
		queue.c \
		bitqueue.c \
                msg_lib.c \
                base64.c \
                $(NULL)

MSG_LIB_OBJS =  \
                ${MSG_LIB_C:.c=.o} \
                $(NULL)

#==============================================================================

CC =		gcc

COPTS =		-O3 -g -Wall $(shell sdl-config --cflags)

INCLUDES = 	\
		-I.. \
		-I../nio_log \
		-I../str_lib \
		$(NULL)

LIBDIRS = 	\
		$(NULL)

ifndef $(TARGET_OS)
TARGET_OS =     UNIX
endif
 
CFLAGS =	$(COPTS) $(INCLUDES) -DDEBUG -D$(TARGET_OS)

LFLAGS =	$(LIBDIRS) $(shell sdl-config --libs) -lssh2

#default compilation rules
%.o:		%.c
		$(CC) -c $< $(CFLAGS) -o $@

all: 		$(TARGETS)

default:	$(TARGETS)

new:		clean default

#==============================================================================

$(MSG_LIB_BIN): $(MSG_LIB_OBJS) $(MSG_LIB_H) $(MSG_LIB_C)
		rm -f $(MSG_LIB_BIN)
		ar rcs $(MSG_LIB_BIN) $(MSG_LIB_OBJS)
		ranlib $(MSG_LIB_BIN)

indent:
		dos2unix *.h *.c
		indent -kr -i4 *.h *.c 

clean:
		rm -f $(TARGETS) *.o *.a core a.out *~ .*.swp
 
