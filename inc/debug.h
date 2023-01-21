#ifndef DEBUG_INCLUDE_H
#define DEBUG_INCLUDE_H

#include <genesis.h>
#include "KDebug.h"

#define DEBUG_LOGGER                   1

#define xstr(a) str(a)
#define str(a) #a

#define NUMARGS(...)  (sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)
#define SUM(...)  sum(NUMARGS(__VA_ARGS__), ##__VA_ARGS__)

#if DEBUG_LOGGER == 1
    #define LOGU(text, val) KLog_U1(text, val)
    #define LOGU2(text1, val1, text2, val2) KLog_U2(text, val, text2, val2)
    #define LOGS(text, val) KLog_S1(text, val)
    #define LOGS2(text1, val1, text2, val2) KLog_S2(text, val, text2, val2)
    #define LOGf(text, val) KLog_f1(text, val)
    #define LOGf2(text1, val1, text2, val2) KLog_f2(text, val, text2, val2)
    #define LOGF(text, val) KLog_F1(text, val)
    #define LOGF2(text1, val1, text2, val2) KLog_F2(text, val, text2, val2)

#else
    #define LOGU(X)
    #define LOGU2(X)
    #define LOGS(X)
    #define LOGS2(X)
    #define LOGf(X)
    #define LOGf2(X)
    #define LOGF(X)
    #define LOGF2(X)
#endif



#if DEBUG_LOGGER == 1
    #define LOGX(_1, _2) _Generic((_2),                     \
                                  int: KLog_U1,             \
                                  u8: KLog_U1,              \
                                  u16: KLog_U1,             \
                                  u32: KLog_U1,             \
                                  s8: KLog_S1,              \
                                  s16: KLog_S1,             \
                                  s32: KLog_S1)(_1, _2)     \


    #define _MYFUNC_SEL(_1, _2, _3, ...) _3
    #define LOG(...) _MYFUNC_SEL(__VA_ARGS__, LOGX, KLog)(__VA_ARGS__)
#else
    #define LOGX(_1, _2)
    #define LOG(...)
#endif

extern void debug_stop();


#endif
