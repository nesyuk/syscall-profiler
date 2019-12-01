#include "stats.h"

static unsigned long long free_count = 0;
static unsigned long long alloc_count  = 0;
static struct stat_mem_alloc *stats_mem_head;

struct stat_mem_alloc* find_mem(void *ptr){
	struct stat_mem_alloc *cur = stats_mem_head;
	while(cur != NULL){
		if (cur->ptr == ptr)
			return cur;
		cur = cur->next;
	}
        return false;
}

void append_mem(){
	if (!stats_mem_head){
		stats_mem_head = __malloc(sizeof(struct stat_mem_alloc));
		stats_mem_head->next = NULL;
	}
	struct stat_mem_alloc *mem = __malloc(sizeof(struct stat_mem_alloc));
	mem->next = stats_mem_head;
	stats_mem_head = mem;
}

void stats_add_malloc(void *ptr, size_t size){
	if (!ptr)
		return;
	append_mem();
	stats_mem_head->ptr = ptr;
	stats_mem_head->malloc_size = size;
	stats_mem_head->last_size = size;
	alloc_count += size;
}

void stats_add_calloc(void *ptr, size_t nmemb, size_t size){
	if (!ptr)
		return;
	append_mem();
	stats_mem_head->ptr = ptr;
	stats_mem_head->calloc_size = size;
	stats_mem_head->calloc_nmemb = nmemb;
	stats_mem_head->last_size = size;
	alloc_count += size;
}

void stats_add_realloc(void *prev, void *cur, size_t size){
	if(!prev || !cur)
		return;
	struct stat_mem_alloc *prev_mem = find_mem(prev);
	if(prev_mem){
		prev_mem->free_size += prev_mem->last_size;
		free_count += prev_mem->last_size;
		alloc_count += size;
		// update ptr
		if (prev == cur){
			prev_mem->realloc_size += size;
			prev_mem->last_size = size;
		}
		else
			prev_mem->realloc_ptr = cur;
	}
	if (prev != cur){
		// add new ptr
		append_mem();
		stats_mem_head->realloc_size += size;
		stats_mem_head->last_size = size;
		stats_mem_head->ptr = cur;
	}
}

void stats_free(void *ptr){
	if (!ptr)
		return;
	struct stat_mem_alloc *mem = find_mem(ptr);
	if(mem){
		free_count += mem->last_size;
		mem->free_size += mem->last_size;
	}
}
