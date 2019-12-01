#include "stats.h"

static unsigned long long free_count = 0;
static unsigned long long alloc_count  = 0;
static struct stat_mem_alloc *stats_mem_head;
static unsigned long long fd_open = 0;
static unsigned long long fd_close = 0;
static struct stat_fd *stats_fd_head;

struct stat_mem_alloc* __find_mem(void *ptr){
	struct stat_mem_alloc *cur = stats_mem_head;
	while(cur != NULL){
		if (cur->ptr == ptr)
			return cur;
		cur = cur->next;
	}
        return false;
}

struct stat_fd* __find_fd(int fd){
        struct stat_fd *cur = stats_fd_head;
        while(cur != NULL){
                if (cur->fd == fd)
                        return cur;
                cur = cur->next;
        }
        return false;
}

void __append_mem(){
	if (!stats_mem_head){
		stats_mem_head = __malloc(sizeof(struct stat_mem_alloc));
		stats_mem_head->next = NULL;
	}
	struct stat_mem_alloc *mem = __malloc(sizeof(struct stat_mem_alloc));
	mem->next = stats_mem_head;
	stats_mem_head = mem;
}

void __append_fd(){
	if (!stats_fd_head){
		stats_fd_head = __malloc(sizeof(struct stat_fd));
		stats_fd_head->next = NULL;
		stats_fd_head->open = 0;
		stats_fd_head->read = 0;
		stats_fd_head->write = 0;
		stats_fd_head->close = 0;
	}
	struct stat_fd *new_fd = __malloc(sizeof(struct stat_fd));
	new_fd->next = stats_fd_head;
	new_fd->open = 0;
	new_fd->read = 0;
	new_fd->write = 0;
	new_fd->close = 0;
	stats_fd_head = new_fd;
}

void stats_malloc(void *ptr, size_t size){
	if (!ptr)
		return;
	__append_mem();
	stats_mem_head->ptr = ptr;
	stats_mem_head->malloc_size = size;
	stats_mem_head->last_size = size;
	alloc_count += size;
}

void stats_calloc(void *ptr, size_t nmemb, size_t size){
	if (!ptr)
		return;
	__append_mem();
	stats_mem_head->ptr = ptr;
	stats_mem_head->calloc_size = size;
	stats_mem_head->calloc_nmemb = nmemb;
	stats_mem_head->last_size = size;
	alloc_count += size;
}

void stats_realloc(void *prev, void *cur, size_t size){
	if(!prev || !cur)
		return;
	struct stat_mem_alloc *prev_mem = __find_mem(prev);
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
		__append_mem();
		stats_mem_head->realloc_size += size;
		stats_mem_head->last_size = size;
		stats_mem_head->ptr = cur;
	}
}

void stats_free(void *ptr){
	if (!ptr)
		return;
	struct stat_mem_alloc *mem = __find_mem(ptr);
	if(mem){
		free_count += mem->last_size;
		mem->free_size += mem->last_size;
	}
}

void stats_open(int fd){
	if(fd < 0)
		return;
	struct stat_fd *fd_stat = __find_fd(fd);
	if (fd_stat){
		fd_stat->open += 1;
	} else {
		__append_fd();
		stats_fd_head->open += 1;
	}
	fd_open += 1;
}

void stats_read(int fd, size_t size){
	if(fd < 0)
		return;
	struct stat_fd *fd_stat = __find_fd(fd);
	if(fd_stat){
		fd_stat->read += size;
	}
}

void stats_write(int fd, size_t size){
	if(fd < 0)
		return;
	struct stat_fd *fd_stat = __find_fd(fd);
	if(fd_stat){
		fd_stat->write += size;
	}
}

void stats_close(int fd){
	if(fd < 0)
		return;
	struct stat_fd *fd_stat = __find_fd(fd);
	if(fd_stat){
		fd_stat->close += 1;
		fd_close += 1;
	}
}
