#ifndef OP_PROFILER
#define OP_PROFILER

#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <unistd.h>

typedef void * (*__malloc_func)(size_t size);
typedef void (*__free_func)(void *ptr);
typedef void * (*__calloc_func)(size_t nmemb, size_t size);
typedef void * (*__realloc_func)(void *ptr, size_t size);
typedef int (*__open_func)(const char *pathname, int flags, mode_t mode);
typedef int (*__close_func)(int fd);
typedef ssize_t (*__read_func)(int fd, void *buf, size_t count);
typedef ssize_t (*__write_func)(int fd, const void *buf, size_t count);

#endif
