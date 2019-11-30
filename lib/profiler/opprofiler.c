#include "opprofiler.h"

void *malloc(size_t size){
	void *ptr  = __malloc(size);
	stats_add_malloc(ptr, size);
	return ptr;
}

void free(void *ptr){
	stats_free(ptr);
	__free(ptr);
}

void *calloc(size_t nmemb, size_t size){
	void *ptr = __calloc(nmemb, size);
	stats_add_calloc(ptr, nmemb, size);
	return ptr;
}

void *realloc(void *ptr, size_t size){
	void *realloc_ptr =  __realloc(ptr, size);
	stats_add_realloc(ptr, realloc_ptr, size);
	return realloc_ptr;
}

int open(const char *pathname, int flags, ...){
	int mode = 0;
	if (__OPEN_NEEDS_MODE (flags)){
                va_list arg;
                va_start (arg, flags);
                mode = va_arg (arg, int);
                va_end (arg);
        }
	return __open(pathname, flags, mode);
}

int close(int fd){
	return __close(fd);
}

ssize_t read(int fd, void *buf, size_t count){
	return __read(fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count){
	return __write(fd, buf, count);
}
