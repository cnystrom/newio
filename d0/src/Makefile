
TARGETS =	$(TARGET1)

#==============================================================================

FILENAME1 =	d0
TARGET1 =	$(FILENAME1)

HEADERS1 = 	\
		done.h \
		file_xfr.h \
		install_dir.h \
		rand.h \
		rpc.h \
		text_box.h \
		url.h \
		$(NULL)

CCFILES1 =	\
		call_http.c \
		call_nio.c \
		check_home.c \
		do_data_in.c \
		done.c \
		file_xfr.c \
		get_login.c \
		get_url.c \
		install_dir.c \
		play_intro.c \
		print_func.c \
		rand.c \
		rpc.c \
		text_box.c \
		url.c \
		get_userpass.c \
		rw_ssh.c \
		main.c \
		$(NULL)

OBJS1 =		${CCFILES1:.c=.o}

#		-lssh2\
#

LIBS1 = 	\
		-lSDL_ttf \
		-lSDL_image \
		-lSDL_mixer \
		-lcrypto \
		-lssh2 \
		$(NIO_LOG_LIB_BIN) \
		$(STR_LIB_BIN) \
		$(FILE_IO_LIB_BIN) \
		$(SOCK_LIB_BIN) \
		$(AUDIO_LIB_BIN) \
		$(COLOR_LIB_BIN) \
		$(EVENT_LIB_BIN) \
		$(FONT_LIB_BIN) \
		$(IMAGE_LIB_BIN) \
		$(MSG_LIB_BIN) \
		$(SSH2_LIB_BIN) \
		$(LIBSSH2_LIB_BIN) \
		$(SCREEN_LIB_BIN) \
		$(SDL_LIB_BIN) \
		$(TERM_LIB_BIN) \
		$(MOVIE_LIB_BIN) \
		$(STR_LIB_BIN) \
		$(NULL)

#==============================================================================

NIO_LOG_LIB =		nio_log
NIO_LOG_LIB_PATH =	../../common/$(NIO_LOG_LIB)
NIO_LOG_LIB_BIN =	$(NIO_LOG_LIB_PATH)/nio_log.a

AUDIO_LIB =		audio_lib
AUDIO_LIB_PATH =	$(AUDIO_LIB)
AUDIO_LIB_BIN =		$(AUDIO_LIB_PATH)/audio_lib.a

COLOR_LIB =		color_lib
COLOR_LIB_PATH =	$(COLOR_LIB)
COLOR_LIB_BIN =		$(COLOR_LIB_PATH)/color_lib.a

EVENT_LIB =		event_lib
EVENT_LIB_PATH =	$(EVENT_LIB)
EVENT_LIB_BIN =		$(EVENT_LIB_PATH)/event_lib.a

FILE_IO_LIB =		file_io_lib
FILE_IO_LIB_PATH =	../../common/$(FILE_IO_LIB)
FILE_IO_LIB_BIN =	$(FILE_IO_LIB_PATH)/file_io_lib.a

FONT_LIB =		font_lib
FONT_LIB_PATH =		$(FONT_LIB)
FONT_LIB_BIN =		$(FONT_LIB_PATH)/font_lib.a

IMAGE_LIB =		image_lib
IMAGE_LIB_PATH =	$(IMAGE_LIB)
IMAGE_LIB_BIN =		$(IMAGE_LIB_PATH)/image_lib.a

MSG_LIB =		msg_lib
MSG_LIB_PATH =		../../common/$(MSG_LIB)
MSG_LIB_BIN =		$(MSG_LIB_PATH)/msg_lib.a

SSH2_LIB =		ssh2_lib
SSH2_LIB_PATH =		../../common/$(SSH2_LIB)
SSH2_LIB_BIN =		$(SSH2_LIB_PATH)/ssh2_lib.a

#LIBSSH2_LIB =		libssh2_lib
#LIBSSH2_LIB_PATH =	$(LIBSSH2_LIB)
#LIBSSH2_LIB_BIN =	$(LIBSSH2_LIB_PATH)/libssh2.a

SCREEN_LIB =		screen_lib
SCREEN_LIB_PATH =	$(SCREEN_LIB)
SCREEN_LIB_BIN =	$(SCREEN_LIB_PATH)/screen_lib.a

SDL_LIB =		sdl_lib
SDL_LIB_PATH =		$(SDL_LIB)
SDL_LIB_BIN =		$(SDL_LIB_PATH)/sdl_lib.a

MOVIE_LIB =		movie_lib
MOVIE_LIB_PATH =	$(MOVIE_LIB)
MOVIE_LIB_BIN =		$(MOVIE_LIB_PATH)/movie_lib.a

SOCK_LIB =		sock_lib
SOCK_LIB_PATH =		../../common/$(SOCK_LIB)
SOCK_LIB_BIN =		$(SOCK_LIB_PATH)/sock_lib.a

STR_LIB =		str_lib
STR_LIB_PATH =		../../common/$(STR_LIB)
STR_LIB_BIN =		$(STR_LIB_PATH)/str_lib.a

#TERM_LIB =		term_lib
#TERM_LIB_PATH =		$(TERM_LIB)
#TERM_LIB_BIN =		$(TERM_LIB_PATH)/term_lib.a

#==============================================================================

TARGET_OS = 	UNIX

CC =		gcc

COPTS =		-O3 -g -Wall $(shell sdl-config --cflags)

INCLUDES = 	\
		-I../../common/ \
		-I../../common/nio_log \
		-I../../common/str_lib \
		-I../../common/file_io_lib \
		-I../../common/sock_lib \
		-I../../common/ssh2_lib \
		$(NULL)

LIBDIRS = 	\
		$(NULL)
 
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
		$(CC) $(LFLAGS) $(OBJS1) $(LIBS2) $(LIBS1) -o $@ -lavformat -lavcodec -lavutil -lswscale
		cp $(TARGET1) ..

$(NIO_LOG_LIB_BIN):
		cd $(NIO_LOG_LIB_PATH); make TARGET_OS=$(TARGET_OS)

$(AUDIO_LIB_BIN):
		cd $(AUDIO_LIB_PATH); make TARGET_OS=$(TARGET_OS)

$(COLOR_LIB_BIN):
		cd $(COLOR_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(EVENT_LIB_BIN):
		cd $(EVENT_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(FILE_IO_LIB_BIN):
		cd $(FILE_IO_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(FONT_LIB_BIN):
		cd $(FONT_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(IMAGE_LIB_BIN):
		cd $(IMAGE_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(MSG_LIB_BIN):
		cd $(MSG_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(SCP_LIB_BIN):
		cd $(SCP_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(SSH2_LIB_BIN):
		cd $(SSH2_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
#$(LIBSSH2_LIB_BIN):
#		cd $(LIBSSH2_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(SCREEN_LIB_BIN):
		cd $(SCREEN_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(SDL_LIB_BIN):
		cd $(SDL_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(MOVIE_LIB_BIN):
		cd $(MOVIE_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(SOCK_LIB_BIN):
		cd $(SOCK_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
$(STR_LIB_BIN):
		cd $(STR_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
#$(TERM_LIB_BIN):
#		cd $(TERM_LIB_PATH); make TARGET_OS=$(TARGET_OS) 
						                            
indent:
		cd $(NIO_LOG_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(AUDIO_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(COLOR_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(EVENT_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(FILE_IO_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(FONT_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(IMAGE_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(MSG_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(SSH2_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
#		cd $(LIBSSH2_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(SCREEN_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(SDL_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(MOVIE_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(SOCK_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(STR_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
#		cd $(TERM_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		cd $(SOCK_LIB_PATH); make TARGET_OS=$(TARGET_OS) indent
		dos2unix *.h *.c
		indent -kr -i4 *.h *.c 

clean:
		cd $(NIO_LOG_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(AUDIO_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(COLOR_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(EVENT_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(FILE_IO_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(FONT_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(IMAGE_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(MSG_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
#		cd $(LIBSSH2_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(SSH2_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(SCREEN_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(SDL_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(MOVIE_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(SOCK_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		cd $(STR_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
#		cd $(TERM_LIB_PATH); make TARGET_OS=$(TARGET_OS) clean
		rm -f $(TARGETS) *.o *.a core a.exe *~ .*.swp
 

