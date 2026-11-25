#ifdef WIN32

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 255
#endif

#define mkstemp		_mktemp
#define snprintf	_snprintf
#define strcasecmp	stricmp
#define random		rand
#define vsnprintf	_vsnprintf

#define S_IWUSR 0
#define S_IRUSR 0

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

//int gettimeofday(struct timeval *time_Info, struct timezone *timezone_Info);
int gettimeofday (struct timeval *tv, void* tz);
void usleep(unsigned int useconds);
void bzero(char *to, int count);
int init_winsock(void);

#endif
