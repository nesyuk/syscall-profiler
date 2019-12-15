#ifndef TEST_OPPROFILER_FD
#define TEST_OPPROFILER_FD

#define TEST_FILENAME "testfile"
#define MIN_BUF_SIZE (size_t)1
#define MAX_BUF_SIZE (size_t)100
#define MAX_CHAR 127

#define FILE_PERM 0644
#define FILENAME_MAX_SIZE 20

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "test_util.h"

static inline void populate_buffer(char *buf, size_t size) {
  for (size_t i = 0; i < size; i++) {
    buf[i] = get_rand('0', MAX_CHAR);
  }
}

static inline void get_testfilename(char *filename, size_t filenumber) {
  sprintf(filename, "%s_%ld", TEST_FILENAME, filenumber);
}

bool test_open(int *, size_t *);
bool test_read(int *, size_t *);
bool test_write(int *, size_t *);
bool test_close(int *, size_t *);

void cleanup_fd(int *, size_t *);

#endif
