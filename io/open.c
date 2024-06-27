// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
    va_list arg;
    va_start(arg, flags);
    int result = syscall(__NR_open, filename, flags, va_arg(arg, int));
    va_end(arg);

    if (result < 0) {
        errno = -result;
        result = -1;
    }

    return result;
}
