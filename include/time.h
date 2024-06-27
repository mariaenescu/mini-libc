#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif
/**
 * To find out what exactly is the timespec C structure:
 * https://man7.org/linux/man-pages/man3/timespec.3type.html
*/
typedef long time_t;
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

int nanosleep(const struct timespec *req, struct timespec *rem);
unsigned int sleep(unsigned int seconds);

#ifdef __cplusplus
}
#endif

#endif
