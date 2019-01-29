#include "worker.h"

#ifdef _WIN32
WorkerId
worker(void *f, void *args, WorkerErr *err)
{
    WorkerId thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f, args, 0, NULL);

    if (thread == NULL)
    {
        *err = (WorkerErr)GetLastError();
    }
    else
    {
        *err = 0;
    }

    return thread;
}

WorkerErr
worker_wait(WorkerId thread)
{
    return (WorkerErr)WaitForSingleObject(thread, INFINITE);
}

WorkerErr
worker_stop(WorkerId thread)
{
    return TerminateThread(thread, 0);
}

#else
WorkerId
worker(void *f, void *args, WorkerErr *err)
{
    WorkerId thread;
    *err = (WorkerErr)pthread_create(&thread, NULL, f, args);

    return thread;
}

WorkerErr
worker_wait(WorkerId thread)
{
    return (WorkerErr)pthread_join(thread, NULL);
}

WorkerErr
worker_stop(WorkerId thread)
{
    return pthread_cancel(thread);
}
#endif
