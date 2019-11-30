#ifndef STATS_OP_PROFILER
#define STATS_OP_PROFILER

#include <stdbool.h>

#include "opslib.h"
#include "stats_mem.h"

void stats_add_malloc(void *ptr, size_t size);
void stats_add_calloc(void *ptr, size_t nmemb, size_t size);
void stats_add_realloc(void *prev, void *cur, size_t size);
void stats_free(void *ptr);

#endif
