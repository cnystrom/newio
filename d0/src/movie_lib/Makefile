
TARGETS =	$(LIB1)

#==============================================================================

LIB1_PATH = .
LIB1 =		movie_lib.a

LIB1_H =     \
		movie_lib.h \
		$(NULL)

LIB1_C =     \
		movie_lib.c \
		$(NULL)

LIB1_OBJS =  \
		${LIB1_C:.c=.o} \
		$(NULL)

#==============================================================================

CC =		gcc

COPTS =         -O3 -g -Wall  $(shell sdl-config --cflags)

INCLUDES = 	\
		-I../../../common \
		-I../../../common/file_io_lib \
		-I../screen_lib \
		-I../audio_lib \
		-I/usr/include/ffmpeg \
		$(NULL)

LIBDIRS = 	\
		$(NULL)

#ifndef TARGET_OS
TARGET_OS = unix
#endif
 
CFLAGS =	$(COPTS) $(INCLUDES) -DDEBUG -D$(TARGET_OS)

LFLAGS =	$(LIBDIRS)

#default compilation rules
%.o:		%.c
		$(CC) -c $< $(CFLAGS) -o $@

all: 		$(TARGETS)

default:	$(TARGETS)

new:		clean default

#==============================================================================

$(TARGET1):	$(OBJS1) $(HEADERS1) $(LIBS1)
		$(CC) $(LFLAGS) $(OBJS1) $(LIBS1) -o $@

$(LIB1):	$(LIB1_OBJS) $(LIB1_H) $(LIB1_C)
		ar rcs $(LIB1) $(LIB1_OBJS)
		ranlib $(LIB1)

indent:
		dos2unix *.h *.c
		indent -kr -i4 *.h *.c 

clean:
		rm -f $(TARGETS) *.o *.a core a.out *~
 
