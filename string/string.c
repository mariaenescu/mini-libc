// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

/**
 * For all the functions I used the Linux Manual pages in order to understand
 * exactly what some functions do and retun in different situations
 * https://man7.org/linux/man-pages/index.html
*/
char *strcpy(char *destination, const char *source)
{
    char *cpy_dst = destination;
    while (*source != '\0')
    {
        *cpy_dst = *source;
        cpy_dst++;
        source++;
    }

    *cpy_dst = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
    char *cpy_dst = destination;
    while (*source != '\0' && len > 0) {
        *cpy_dst = *source;
        cpy_dst++;
        source++;
		len--;
    }

    while (len > 0) {
        *cpy_dst = '\0';
        cpy_dst++;
        len--;
    }

    return destination;
}

char *strcat(char *destination, const char *source)
{
    char *cpy_dst = destination;
    while (*cpy_dst != '\0') {
        cpy_dst++;
    }

    while (*source != '\0') {
        *cpy_dst = *source;
        cpy_dst++;
        source++;
    }
    *cpy_dst = '\0';

    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
    char *cpy_dst = destination;
    while (*cpy_dst != '\0') {
        cpy_dst++;
    }

    while (*source != '\0' && len > 0) {
        *cpy_dst = *source;
        cpy_dst++;
        source++;
		len--;
    }

    *cpy_dst = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    int cmp_status = 0;

    if (*str1 != *str2) {
        cmp_status = (*str1 > *str2) ? 1 : -1;
    }

    return cmp_status;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	while (*str1 != '\0' && *str1 == *str2 && len > 0) {
        str1++;
        str2++;
		len--;
    }

    int cmp_status = 0;
    if (len != 0 && *str1 != *str2) {
        cmp_status = (*str1 > *str2) ? 1 : -1;
    }

    return cmp_status;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
    while (*str != '\0' && *str != (char)c) {
        str++;
    }

    if (*str == (char)c) {
        return (char*)str;
    }

    return NULL;
}

char *strrchr(const char *str, int c)
{
    const char *last = NULL;

    while (*str) {
        if (*str == (char)c) {
            last = str;
        }
        str++;
    }

    return (char*)last;
}

char *strstr(const char *haystack, const char *needle)
{
	 while (*haystack) {
        const char *str_h = haystack;
        const char *str_n = needle;

        while (*str_h && *str_n && (*str_h == *str_n)) {
            str_h++;
            str_n++;
        }

        if (*str_n == '\0') {
            return (char*)haystack;
        }

        haystack++;
    }

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
    for (int i = strlen(haystack) - strlen(needle); i >= 0; i--) {
        if (strncmp(haystack + i, needle, strlen(needle)) == 0) {
            return (char *)(haystack + i);
        }
    }

    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
    void *cpy_dst = destination;
    while (num > 0) {
            *(char *)cpy_dst = *(const char *)source;
            cpy_dst++;
            source++;
            num--;
    }

    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
    void *cpy_dst = destination;
    if ((char *)cpy_dst < (const char *)source) {
        while (num > 0) {
            *(char *)cpy_dst = *(const char *)source;
            cpy_dst++;
            source++;
            num--;
        }
    } else if ((char *)cpy_dst > (const char *)source) {
        size_t n = num;
        while (num > 0) {
            *((char *)cpy_dst + n - 1)  = *((const char *)source + n - 1);
            cpy_dst--;
            source--;
            num--;
        }
    }

    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    int cmp_status = 0;
    while (num > 0) {
        if (*(const char *)ptr1 != *(const char *)ptr2) {
            cmp_status = (*(const char *)ptr1 > *(const char *)ptr2) ? 1 : -1;
            break;
        }
        ptr1++;
        ptr2++;
        num--;
    }

    return cmp_status;
}

void *memset(void *source, int value, size_t num)
{
    void *cpy_src = source;
    while (num > 0) {
        *(char *)cpy_src = (char)value;
        cpy_src++;
        num--;
    }

    return source;
}
