#include "async.h"

#ifdef _WIN32
ThreadId
async(void *f, void *args, ThreadErr *err)
{
    ThreadId thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f, args, 0, NULL);

    if (thread == NULL)
    {
        *err = (ThreadErr)GetLastError();
    }
    else
    {
        *err = 0;
    }

    return thread;
}

ThreadErr
await(ThreadId thread)
{
    return (ThreadErr)WaitForSingleObject(thread, INFINITE);
}

#else
ThreadId
async(void *f, void *args, ThreadErr *err)
{
    ThreadId thread;
    *err = (ThreadErr)pthread_create(&thread, NULL, f, args);

    return thread;
}

ThreadErr
await(ThreadId thread)
{
    return (ThreadErr)pthread_join(thread, NULL);
}
#endif
