
TARGETS =	$(TARGET1)

#==============================================================================

FILENAME1 =	file_io_lib
TARGET1 =	$(FILENAME1).a

HEADERS1 = 	\
		$(FILENAME1).h \
		$(NULL)

CCFILES1 =	\
		misc_io.c \
		path.c \
		$(NULL)

OBJS1 =		${CCFILES1:.c=.o}

LIBS1 = 	\
		$(NULL)

#STR_LIB_PATH =	../str_lib
#STR_LIB_BIN =	$(STR_LIB_PATH)/str_lib.a

#==============================================================================

CC =		gcc

COPTS =		-O3 -g -Wall 

INCLUDES = 	\
		-I/Library/Frameworks/SDL.framework/Headers \
		-I.. \
		-I../str_lib \
		$(NULL)

LIBDIRS = 	\
		$(NULL)

ifndef $(TARGET_OS)
TARGET_OS =	UNIX
endif
 
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
		rm -f ${TARGET1}
		ar rcs $(TARGET1) $(LIBS1) $(OBJS1)
		ranlib $(TARGET1)

$(STR_LIB_BIN):
		cd $(STR_LIB_PATH); make

indent:
		dos2unix *.h *.c
		indent -kr -i4 *.h *.c 

clean:
		rm -f $(TARGETS) *.o *.a core a.out *~
 
