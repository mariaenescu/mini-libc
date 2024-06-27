Enescu Maria 321CA
# Mini-libc

## Objectives

- Learn about the structure and functionalities provided by the standard C library
- Accommodate with the syscall interface in Linux
- Gain a better understanding of strings and memory management functions
- Learn how the standard C library provides support for low-level input/output operations

## Statement

Build a **minimalistic** [**standard C library**](https://en.wikipedia.org/wiki/C_standard_library) implementation for Linux systems (named **mini-libc**), that can be used as a replacement for the **system libc** ([glibc](https://www.gnu.org/software/libc/) in Linux).
The goal is to have a minimally functional libc with features such as string management, basic memory support and POSIX file I/O.

The implementation of mini-libc will be **freestanding**, i.e. it will not use any outside library calls.
It will be implemented on top of the system call interface provided by Linux on an `x86_64` architecture.
Any function you require, that is typically part of libc, you will have to implement.
You can reuse functions that you implement in other parts of the mini-libc.

In case you are using a macOS device with ARM64 / Aarch64, you will have to install an `x86_64` virtual machine.

## Support Code

The support code consists of three directories:

- `libc/` is the skeleton mini-libc implementation.
  You will have to implement missing parts marked as `TODO` items.

- `samples/` stores use cases and tests of mini-libc.

- `tests/` are states used to validate (and grade) the assignment.

System call invocation is done via the `syscall()` function defined in `libc/syscall.c`.
That itself makes a call to the architecture-specific call in `libc/internal/arch/x86_64/syscall_arch.h`;
hence the dependency on the `x86_64` architecture.

### API and Implementation Tasks

The application programming interface (API) of the C standard library is declared in a number of header files.
Each header file contains one or more function declarations, data type definitions and macros.
For your minimal implementation, the following header files are of interest:

- `<string.h>`: defines string-handling functions

  For this assignment, you will have to implement the following functions: `strcpy()`, `strcat()`, `strlen()`, `strncpy()`, `strncat()`, `strcmp()`, `strncmp()`, `strstr()`, `strrstr()`, `memcpy()`, `memset()`, `memmove()`, `memcmp()`.

- `<stdio.h>`: defines printing and I/O functions

  For this assignment, you will have to implement `puts()`.

- `<unistd.h>`, `<sys/fcntl.h>` and `<sys/stat.h>`: define I/O primitives

  For this assignment, you will have to implement the following functions: `open()`, `close()`, `lseek()`, `stat()`, `fstat()`, `truncate()`, `ftruncate()`.

  You will also have to implement the `nanosleep()` and `sleep()` functions.

- `<stdlib.h`> and `<sys/mman.h>` define memory allocation functions

  For this assignment, you will have to implement the following functions: `malloc()`, `free()`, `calloc()`, `realloc()`, `realloc_array()`, `mmap()`, `mremap()`, `munmap()`.

  For managing memory areas, a basic list structure is provided in `include/internal/mm/mem_list.h` and `mm/mem_list.c`.

- `<errno.h>` and `errno.c`: declare and define the integer variable `errno`, which is set by system calls and some library functions in the event of an error to indicate what went wrong.

Some tests do not build.
This is intentional.
You will have to add the missing features to make those tests compile, that is

- the `time.h` header
- the declaration and the implementation of `puts()`
- the declaration and the implementation of `nanosleep()` and `sleep()`
- the update of the libc `Makefile` to build the source code files implementing `puts()`, `nanosleep()` and `sleep()`

  :exclamation::exclamation: **Pay attention** to which functions have to modify the `errno` variable.

### Building mini-libc

To build mini-libc, run `make` in the `libc/` directory:

```console
student@so:~/.../content/assignments/mini-libc$ cd libc/

student@so:~/.../assignments/mini-libc/libc$ make
```

To build samples, enter the `samples` directory and run `make`:

```console
student@so:~/.../content/assignments/mini-libc$ cd samples/

student@so:~/.../assignments/mini-libc/samples$ make
```
