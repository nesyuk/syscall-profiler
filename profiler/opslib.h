#ifndef OPS_LIB_PROFILER
#define OPS_LIB_PROFILER

#define _GNU_SOURCE
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>

void *__malloc(size_t size);
void __free(void *ptr);
void *__calloc(size_t nmemb, size_t size);
void *__realloc(void *ptr, size_t size);
int __open(const char *pathname, int flags, mode_t mode);
int __close(int fd);
ssize_t __read(int fd, void *buf, size_t count);
ssize_t __write(int fd, const void *buf, size_t count);

#endif
