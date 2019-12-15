#include "opslib.h"

void *__malloc(size_t size) {
  return ((__malloc_func)dlsym(RTLD_NEXT, "malloc"))(size);
}

void __free(void *ptr) { ((__free_func)dlsym(RTLD_NEXT, "free"))(ptr); }

void *__calloc(size_t nmemb, size_t size) {
  return ((__calloc_func)dlsym(RTLD_NEXT, "calloc"))(nmemb, size);
}

void *__realloc(void *ptr, size_t size) {
  return ((__realloc_func)dlsym(RTLD_NEXT, "realloc"))(ptr, size);
}

int __open(const char *pathname, int flags, mode_t mode) {
  return ((__open_func)dlsym(RTLD_NEXT, "open"))(pathname, flags, mode);
}

int __close(int fd) { return ((__close_func)dlsym(RTLD_NEXT, "close"))(fd); }
ssize_t __read(int fd, void *buf, size_t count) {
  return ((__read_func)dlsym(RTLD_NEXT, "read"))(fd, buf, count);
}

ssize_t __write(int fd, const void *buf, size_t count) {
  return ((__write_func)dlsym(RTLD_NEXT, "write"))(fd, buf, count);
}
