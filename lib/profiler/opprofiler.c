#include "opprofiler.h"

void *malloc(size_t size){
	return __malloc(size);
}

void free(void *ptr){
	__free(ptr);
}

void *calloc(size_t nmemb, size_t size){
	return __calloc(nmemb, size);
}

void *realloc(void *ptr, size_t size){
	return __realloc(ptr, size);
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
