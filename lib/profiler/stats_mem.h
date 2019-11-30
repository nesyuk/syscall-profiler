#ifndef STATS_MEM_ALLOC_OP_PROFILER
#define STATS_MEM_ALLOC_OP_PROFILER

#include <sys/types.h>
#include <stdbool.h>

#define MALLOC_IDX 0
#define CALLOC_IDX 1
#define REALLOC_IDX 2
#define LAST_ALLOC_IDX 3
#define FREE_IDX 4

struct stat_mem_alloc {
        void *ptr;
        unsigned long long mem_size[5];
        size_t calloc_nmemb;
        struct stat_mem_alloc *next;
        struct stat_mem_alloc *realloc_ptr;
        unsigned long long *alloc_count; // total alloc for all ptrs
        unsigned long long *free_count; // total free for all ptrs
};

bool find(struct stat_mem_alloc *first, void *ptr, struct stat_mem_alloc *found);
void append(struct stat_mem_alloc *current, struct stat_mem_alloc *new_amem);
void set_malloc(struct stat_mem_alloc *amem, void *ptr, size_t size);
void set_calloc(struct stat_mem_alloc *amem, void *ptr, size_t size, size_t nmem);
void set_realloc(struct stat_mem_alloc *amem, void *ptr, size_t size);
void set_realloc_ptr(void *ptr);
void set_free(struct stat_mem_alloc *amem);

#endif
