#include "opprofiler.h"

void *malloc(size_t size){
	if (log_syscall())
		log_malloc(size);

	void *ptr  = __malloc(size);
	stats_malloc(ptr, size);
	return ptr;
}

void free(void *ptr){
	if(log_syscall())
		log_free(ptr);

	stats_free(ptr);
	__free(ptr);
}

void *calloc(size_t nmemb, size_t size){
	if(log_syscall())
		log_calloc(nmemb, size);

	void *ptr = __calloc(nmemb, size);
	stats_calloc(ptr, nmemb, size);
	return ptr;
}

void *realloc(void *ptr, size_t size){
	if(log_syscall())
		log_realloc(ptr, size);

	void *realloc_ptr =  __realloc(ptr, size);
	stats_realloc(ptr, realloc_ptr, size);
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
	if(log_syscall())
		log_open(pathname, flags, mode);

	int fd = __open(pathname, flags, mode);
	stats_open(fd);
	return fd;
}

int close(int fd){
	if(log_syscall())
		log_close(fd);

	int result =  __close(fd);
	//TODO: log error if result != 0
	stats_close(fd);
	return result;
}

ssize_t read(int fd, void *buf, size_t count){
	if(log_syscall())
		log_read(fd, buf, count);

	size_t bytes = __read(fd, buf, count);
	stats_read(fd, bytes);
	return bytes;
}

ssize_t write(int fd, const void *buf, size_t count){
	if(log_syscall())
		log_write(fd, buf, count);

	size_t bytes = __write(fd, buf, count);
	stats_write(fd, bytes);
	return bytes;
}
