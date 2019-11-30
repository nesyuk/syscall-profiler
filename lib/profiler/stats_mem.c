#include "stats_mem.h"

bool find(struct stat_mem_alloc *head, void *ptr, struct stat_mem_alloc *found){
	return false;
}

void append(struct stat_mem_alloc *head, struct stat_mem_alloc *new_amem){}

void set_malloc(struct stat_mem_alloc *amem, void *ptr, size_t size){}

void set_calloc(struct stat_mem_alloc *amem, void *ptr, size_t size, size_t nmem){}

void set_realloc(struct stat_mem_alloc *amem, void *ptr, size_t size){}

void set_free(struct stat_mem_alloc *amem){}
