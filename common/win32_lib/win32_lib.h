#ifdef WIN32

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 255
#endif

#ifdef __MINGW32__
/* 2026: MinGW-w64 has these, with its own prototypes. */
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#define random		rand
#define poll		WSAPoll
#else
#define mkstemp		_mktemp
#define snprintf	_snprintf
#define strcasecmp	stricmp
#define random		rand
#define vsnprintf	_vsnprintf
#endif

#define S_IWUSR 0
#define S_IRUSR 0

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

#ifndef __MINGW32__
//int gettimeofday(struct timeval *time_Info, struct timezone *timezone_Info);
int gettimeofday (struct timeval *tv, void* tz);
void usleep(unsigned int useconds);
#endif
void bzero(char *to, int count);
int init_winsock(void);

#endif
