#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    long result = syscall(__NR_nanosleep, req, rem);

    if (result < 0) {
        errno = -result;
        return -1;
    }

    return 0;
}

unsigned int sleep(unsigned int seconds)
{
    struct timespec request_time;
    request_time.tv_sec = seconds;
    request_time.tv_nsec = 0;

    struct timespec reminder_time;
    reminder_time.tv_sec = 0;
    reminder_time.tv_nsec = 0;

    int result = nanosleep(&request_time, &reminder_time);

    if (result != 0) {
        return reminder_time.tv_sec;
    }

    return 0;
}
