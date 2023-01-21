#include <genesis.h>
#include "KDebug.h"
#include "debug.h"

void Log_(char *t1)  {
    KLog(t1);
}

void Log_U1_(char *t1, u32 v1)  {
    KLog_U1(t1, v1);
}

void Log_U2_(char *t1, u32 v1, char *t2, u32 v2)    {
    KLog_U2(t1, v1, t2, v2);
}

void Log_S1_(char *t1, s32 v1)  {
    KLog_S1(t1, v1);
}

void Log_S2_(char *t1, s32 v1, char *t2, s32 v2)    {
    KLog_S2(t1, v1, t2, v2);
}

void Log_f1_(char *t1, fix16 v1)  {
    KLog_f1(t1, v1);
}

void Log_f2_(char *t1, fix16 v1, char *t2, fix16 v2)    {
    KLog_f2(t1, v1, t2, v2);
}

void Log_F1_(char *t1, fix32 v1)  {
    KLog_F1(t1, v1);
}

void Log_F2_(char *t1, fix32 v1, char *t2, fix32 v2)    {
    KLog_F2(t1, v1, t2, v2);
}

void debug_stop()
{
	KDebug_Halt();
}


