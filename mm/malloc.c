// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <internal/io.h>
#include <stdlib.h>
#include <errno.h>

/**
 * This function uses mmap to allocate memory with the specified size and protection flags.
 * If successful, it adds the allocated memory to a memory list and returns the pointer to the memory.
 * If allocation fails, it sets errno to EINVAL and returns NULL.
*/
void *malloc(size_t size)
{
	void *mapped_memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (mapped_memory == MAP_FAILED) {
        errno = EINVAL;
        return NULL;
    }

    if (mem_list_add(mapped_memory, size) != 0) {
        munmap(mapped_memory, size);
        return NULL;
    }

    return mapped_memory;
}


/**
 * This function allocates the memory and also initializes every byte in the allocated memory to 0.
 * If allocation fails, it sets errno to ENOMEM and returns NULL.
 */
void *calloc(size_t nmemb, size_t size)
{
    void *mapped_memory = malloc(nmemb * size);
    if (mapped_memory == NULL) {
		errno = ENOMEM;
		return NULL;
	}

    while (nmemb > 0) {
		*(size_t*) mapped_memory = 0;
        mapped_memory++;
        nmemb--;
	}

    return mapped_memory;
}

/**
 * Deallocates the memory block pointed to by ptr.
 * This function also updates the memory list to remove the deallocated memory.
*/
void free(void *ptr)
{
    struct mem_list *item = mem_list_find(ptr);
	munmap(ptr, item->len);
    mem_list_del(item->start);
}

/**
 * Reallocates memory for a block of memory pointed to by ptr to the given size.
 * If successful, it copies the data from the old block to the new block and frees the old block.
 * If the reallocation fails, it sets errno to ENOMEM and returns NULL.
 */
void *realloc(void *ptr, size_t size)
{
	void *mapped_memory = malloc(size);

    if (mapped_memory == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	if (size < (size_t) ptr)
        memcpy(mapped_memory, ptr, size);
	else
		memcpy(mapped_memory, ptr, (size_t) ptr);

	free(ptr);

	return mapped_memory;
}

/**
 * This function is similar to realloc but takes two arguments for size and number of elements.
 * If successful, it copies the data from the old block to the new block and frees the old block.
 * If the reallocation fails, returns NULL.
 */
void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    void *mapped_memory = realloc(ptr, nmemb * size);

    if (mapped_memory == NULL) {
		return NULL;
	}

    return mapped_memory;
}
