#ifndef SYSCALL_OPS_LOGGER
#define SYSCALL_OPS_LOGGER

#include <stdbool.h>
#include <sys/time.h>

#include "logger.h"

#define SEC_TO_NANOSEC 1000000LL

void log_malloc(size_t size);
void log_calloc(size_t nmemb, size_t size);
void log_realloc(void *ptr, size_t size);
void log_free(void *ptr);
void log_open(const char *pathname, int flags, mode_t mode);
void log_close(int fd);
void log_read(int fd, void *buf, size_t count);
void log_write(int fd, const void *buf, size_t count);

#endif
