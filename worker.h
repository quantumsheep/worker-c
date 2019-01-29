#ifndef _WORKER_H
#define _WORKER_H

#ifdef _WIN32
#include <windows.h>

typedef HANDLE WorkerId;
#else
#include <pthread.h>

typedef pthread_t WorkerId;
#endif

typedef unsigned long WorkerErr;

extern WorkerId
worker(void *f, void *args, WorkerErr *err);

extern WorkerErr
worker_wait(WorkerId thread);

extern WorkerErr
worker_stop(WorkerId thread);

#endif
