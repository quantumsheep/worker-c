#ifndef _ASYNC_H
#define _ASYNC_H 1

#ifdef _WIN32
#include <windows.h>

typedef HANDLE ThreadId;
#else
#include <pthread.h>

typedef pthread_t ThreadId;
#endif

typedef unsigned long ThreadErr;

extern ThreadId
async(void *f, void *args, ThreadErr *err);

extern ThreadErr
await(ThreadId thread);

extern ThreadErr
astop(ThreadId thread);

#endif
