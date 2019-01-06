# Async library
Multithreading can be very complicated in C, POSIX and Windows multithreading functions are not the same for instance.
This library was made in order to palliate this issue and facilitate the use of asynchronous instructions in C.


# How to install
Just drop `async.h` and `async.c` in your project and include `async.h` using a relative path.

Sometimes you will need to add `-pthread` in gcc options (only if not on Windows).

# Usage
## async()
```c
ThreadId
async(void *f, void *args, ThreadErr *err);
```
This function is used to start any functions asynchronously. 

### Parameters
**f**: the function that will be run asynchronously.  
**args**: arguments to be passed to the given function.  
**err**: the error code number, literally an `unsigned long`. It can be `NULL` but if not, see [`pthread_create` POSIX information page](http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_create.html) for Linux or OSX and [`GetLastError()` documentation](https://msdn.microsoft.com/fr-fr/d852e148-985c-416f-a5a7-27b6914b45d4) for Windows.

### Return value
It returns a `ThreadId` which is a `pthread_t` (`pthread.h`) on POSIX operating systems and a `HANDLE` (`windows.h`) on Windows.
The returned value can be `NULL` if their is an error.


## await()
```c
ThreadErr
await(ThreadId thread);
```
This function is used to wait for a thread to end before continuing the program.

### Parameters
**thread**: a `ThreadId`, returned by the [`async()`](#async) function.

### Return value
It's the error code number, literally an `unsigned long`. It can be `NULL` but if not, see [`pthread_create` POSIX information page](http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_create.html) for Linux or OSX and [`GetLastError()` documentation](https://msdn.microsoft.com/fr-fr/d852e148-985c-416f-a5a7-27b6914b45d4) for Windows.


## astop()
```c
ThreadErr
astop(ThreadId thread);
```
Terminate a thread. Considered as an unsafe instruction.

### Parameters
**thread**: a `ThreadId`, returned by the [`async()`](#async) function.

### Return value
It's the error code number, literally an `unsigned long`. It can be `NULL` but if not, see [`pthread_create` POSIX information page](http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_create.html) for Linux or OSX and [`GetLastError()` documentation](https://msdn.microsoft.com/fr-fr/d852e148-985c-416f-a5a7-27b6914b45d4) for Windows.


## Example
```c
#include "async/async.h"

#include <unistd.h>
#include <stdio.h>

void
timeout(int time)
{
    sleep(time);
    printf("Wake up\n");
}

void
handleError(ThreadErr err)
{
    if (err)
    {
        printf("Error code: %ld\n", err);
        _exit(0);
    }
}

int
main(int argc, char** argv)
{
    ThreadErr err;

    void* args = { 2 };
    ThreadId thread = async(timeout, args, &err);
    handleError(err);

    printf("The thread has started!\n");

    err = await(thread);
    handleError(err);

    printf("Timeout finished.\n");
}
```

This example will print the following:
```
The thread has started!
Wake up!
Timeout finished
```
« `Wake up!` » printed 2 seconds after « `The thread has started!` » like wanted with the `sleep(2)`. And « `Timeout finished.` » directly printed after the thread's end.
