#ifndef OPS_LIB_PROFILER
#define OPS_LIB_PROFILER

#define _GNU_SOURCE
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>

typedef void *(*__malloc_func)(size_t size);
typedef void (*__free_func)(void *ptr);
typedef void *(*__calloc_func)(size_t nmemb, size_t size);
typedef void *(*__realloc_func)(void *ptr, size_t size);
typedef int (*__open_func)(const char *pathname, int flags, mode_t mode);
typedef int (*__close_func)(int fd);
typedef ssize_t (*__read_func)(int fd, void *buf, size_t count);
typedef ssize_t (*__write_func)(int fd, const void *buf, size_t count);

void *__malloc(size_t size);
void __free(void *ptr);
void *__calloc(size_t nmemb, size_t size);
void *__realloc(void *ptr, size_t size);
int __open(const char *pathname, int flags, mode_t mode);
int __close(int fd);
ssize_t __read(int fd, void *buf, size_t count);
ssize_t __write(int fd, const void *buf, size_t count);

#endif
