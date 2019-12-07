#include "stats.h"

static int bytesToKb = 1024;
static char buf[256];

/* Statistics of memory allocation:
 *
 * free_count: total amount of freed memory
 * alloc_count: total amount of allocated memory
 * stats_mem_head: sums of allocated memory per each
 * 		   memory allocation method: malloc, calloc, realloc,
 * 		   size of last allocated memory, etc... per pointer
 * stats_mem_overhead: total amount of allocated memory for storing memory 
 * 		       allocation statistics: sizeof(free_count) + 
 * 		       sizeof(alloc_count) + self (sizeof(stats_mem_overhead)) + 
 * 		       ntimes * sizeof(stat_mem_alloc)
 */
static unsigned long long free_count = 0;
static unsigned long long alloc_count  = 0;
static struct stat_mem_alloc *stats_mem_head;
static unsigned long long stats_mem_overhead = sizeof(unsigned long long)*3;


/* Statistics of file operations:
 *
 * fd_open: total time open() was called on file descriptor
 * fd_close: total time close() was called on file descriptor
 * stats_fd_head: total amount of operations open(), close(),
 * 		  read() and write() per file descriptor.
 * stats_fd_overhead: total amount of allocated memory for
 * 		      file descriptor statistics: sizeof(fd_open) + 
 * 		      sizeof(fd_close) + self (sizeof(stats_fd_overhead)) + 
 * 		      ntimes * sizeof(stats_fd_head)
 */
static unsigned long long fd_open = 0;
static unsigned long long fd_close = 0;
static struct stat_fd *stats_fd_head;
static unsigned long long stats_fd_overhead = sizeof(unsigned long long)*3;

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
		stats_mem_overhead += sizeof(struct stat_mem_alloc);
	}
	struct stat_mem_alloc *mem = __malloc(sizeof(struct stat_mem_alloc));
	mem->next = stats_mem_head;
	stats_mem_head = mem;
	stats_mem_overhead += sizeof(struct stat_mem_alloc);
}

void __append_fd(){
	if (!stats_fd_head){
		stats_fd_head = __malloc(sizeof(struct stat_fd));
		stats_fd_head->next = NULL;
		stats_fd_head->open = 0;
		stats_fd_head->read = 0;
		stats_fd_head->write = 0;
		stats_fd_head->close = 0;
		stats_fd_overhead += sizeof(struct stat_fd);
	}
	struct stat_fd *new_fd = __malloc(sizeof(struct stat_fd));
	new_fd->next = stats_fd_head;
	new_fd->open = 0;
	new_fd->read = 0;
	new_fd->write = 0;
	new_fd->close = 0;
	stats_fd_head = new_fd;
	stats_fd_overhead += sizeof(struct stat_fd);
}

/* 
 * Log pointers that are not freed 
 */
void __log_alloc(){
        struct stat_mem_alloc *cur = stats_mem_head;
	sprintf(buf, "Total allocated memory: %lld bytes (~%lldKB)\nTotal freed memory: %lld bytes (~%lldKB)\nTotal overhead: %lld bytes (~%lldKB)\n\nAllocated memory info per pointer:\n\n", alloc_count, alloc_count/bytesToKb, free_count, free_count/bytesToKb, stats_mem_overhead, stats_mem_overhead/bytesToKb);
	log_stats(buf);
	sprintf(buf, "| ptr:%10s | malloc (bytes):%5s | calloc (nmemb x bytes):%20s | realloc (bytes):%4s | last size (bytes):%2s | total free (bytes):%1s |\n", "", "", "", "", "", "");
	log_stats(buf);
        while(cur != NULL){
                if ((cur->malloc_size + (cur->calloc_size * cur->calloc_nmemb) + cur->realloc_size) != cur->free_size){
			sprintf(buf, "| %p | %20ld | %20ld x %20ld | %20ld | %20ld | %20ld |\n",
					cur->ptr, cur->malloc_size, cur->calloc_size, cur->calloc_nmemb, cur->realloc_size, cur->last_size, cur->free_size);
			log_stats(buf);
		}
                cur = cur->next;
        }
	sprintf(buf, "\n\n");
	log_stats(buf);
}

/* 
 * Log file descriptors that are not closed 
 */
void __log_fd(){
	struct stat_fd *cur = stats_fd_head;
	sprintf(buf, "Total open(): %lld times\nTotal close(): %lld times\nTotal overhead: %lld bytes (~%lldKB)\n\nFile operations info per file descriptor:\n\n",
			fd_open, fd_close, stats_fd_overhead, stats_fd_overhead/bytesToKb);
	log_stats(buf);
	sprintf(buf, "| file descriptor #: %2s| open (times):%7s | read (bytes):%7s | write (bytes):%6s | close (times):%6s |\n", "", "", "", "", "");
	log_stats(buf);
	while(cur != NULL){
		if(cur->open != cur->close){
			sprintf(buf, "| %20d | %20ld | %20lld | %20lld | %20ld |\n", cur->fd, cur->open, cur->read, cur->write, cur->close);
			log_stats(buf);
		}
		cur = cur->next;
	}
	sprintf(buf, "\n\n");
	log_stats(buf);
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
	stats_mem_head->last_size = size*nmemb;
	alloc_count += size*nmemb;
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
	__log_alloc();
}

void stats_open(int fd){
	if(fd < 0)
		return;
	struct stat_fd *fd_stat = __find_fd(fd);
	if (fd_stat){
		fd_stat->open += 1;
	} else {
		__append_fd();
		stats_fd_head->fd = fd;
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
	if(fd_open != fd_close)
		__log_fd();
}
