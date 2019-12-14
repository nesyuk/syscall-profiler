#ifndef STATS_OP_PROFILER
#define STATS_OP_PROFILER

#include <stdbool.h>

#include "opslib.h"
#include "logger.h"
#include "opsconfig.h"

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

struct stat_fd {
        int fd;
        size_t open;
        unsigned long long read;
        unsigned long long write;
	size_t close;
	struct stat_fd *next;
};

void stats_malloc(void *ptr, size_t size);
void stats_calloc(void *ptr, size_t nmemb, size_t size);
void stats_realloc(void *prev, void *cur, size_t size);
void stats_free(void *ptr);
void stats_open(int fd);
void stats_read(int fd, size_t size);
void stats_write(int fd, size_t size);
void stats_close(int fd);

#endif
