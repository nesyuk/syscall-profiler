#include "stats.h"

static struct stat_mem_alloc *head;

void init_stats_mem(struct stat_mem_alloc *mem){
	mem = (struct stat_mem_alloc *) __malloc(sizeof(struct stat_mem_alloc *));
}

void stats_add_malloc(void *ptr, size_t size){
	if (!ptr)
		return;
	struct stat_mem_alloc *mem = 0;
	init_stats_mem(mem);
	set_malloc(mem, ptr, size);
	append(head, mem);
}

void stats_add_calloc(void *ptr, size_t nmemb, size_t size){
	if (!ptr)
		return;
	struct stat_mem_alloc *mem = 0;
        init_stats_mem(mem);
	set_calloc(mem, ptr, nmemb, size);
        append(head, mem);
}

void stats_add_realloc(void *prev, void *cur, size_t size){
	if(!prev || !cur)
		return;
	struct stat_mem_alloc *prev_mem = 0;
	if(find(head, prev, prev_mem)){
		set_free(prev_mem);
		// update ptr
		if (prev == cur)
			set_realloc(prev_mem, prev, size);
		else
			set_realloc_ptr(cur);
	}
	if (prev != cur){
		// add new ptr
		struct stat_mem_alloc *realloc_mem = 0;
		init_stats_mem(realloc_mem);
		set_realloc(realloc_mem, cur, size);
		append(head, realloc_mem);
	}
}

void stats_free(void *ptr){
	if (!ptr)
		return;
	struct stat_mem_alloc *mem = 0;
	if(find(head, ptr, mem)){
		set_free(mem);
	}
}
