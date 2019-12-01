#ifndef STATS_OP_PROFILER
#define STATS_OP_PROFILER

#include <stdbool.h>

#include "opslib.h"

struct stat_mem_alloc {
        void *ptr;
	size_t malloc_size;
	size_t calloc_size;
        size_t calloc_nmemb;
	size_t realloc_size;
        void *realloc_ptr;
	size_t last_size;
	size_t free_size;
        struct stat_mem_alloc *next;
};

void stats_add_malloc(void *ptr, size_t size);
void stats_add_calloc(void *ptr, size_t nmemb, size_t size);
void stats_add_realloc(void *prev, void *cur, size_t size);
void stats_free(void *ptr);

#endif
