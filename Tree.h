#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*Debug modes*/
#define LOG1(fmt, ...){                                  \
    if (debug_mode >= DBG_ERROR)                         \
    {                                                    \
        fprintf(stderr,"INFO:"fmt"\n", ##__VA_ARGS__);   \
    }                                                    \
                                                         \
}

#define LOG2(fmt, ...){                                  \
    if (debug_mode >= DBG_WARN)                          \
    {                                                    \
        fprintf(stderr,"INFO:" fmt "\n", ##__VA_ARGS__); \
    }                                                    \
    \
}

#define LOG3(fmt, ...){                                  \
        if (debug_mode >= DBG_INFO)                      \
        {                                                \
        fprintf(stderr,"INFO:" fmt "\n", ##__VA_ARGS__); \
    }                                                    \
                                                         \
}

/*Variarity of dbg modes*/
enum Debug_Modes
{
    DBG_OFF   = 0,
    DBG_ERROR = 1,
    DBG_WARN  = 2,
    DBG_INFO  = 3,
};