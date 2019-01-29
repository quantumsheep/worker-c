#include <pthread.h>

typedef struct timer_t Timer;
struct timer_t
{
    int time;
};

int
go_sleep(Timer timer)
{
    sleep(timer.time);
}

int
main(void)
{
    void
}