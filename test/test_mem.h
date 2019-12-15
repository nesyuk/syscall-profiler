#ifndef TEST_OPPROFILER_MEM
#define TEST_OPPROFILER_MEM

#define MIN_ALLOC_NMEM (size_t)1
#define MAX_ALLOC_NMEM (size_t)100
#define ALLOC_NMEM_SIZE (size_t)2
#define MIN_ALLOC_SIZE (size_t)1
#define MAX_REALLOC_SIZE (size_t)300

#include <stdbool.h>
#include <stdio.h>

#include "test_util.h"

bool test_malloc(void **, unsigned int *);
bool test_calloc(void **, unsigned int *);
bool test_realloc(void **, unsigned int *);
bool test_free(void **, unsigned int *);

void cleanup_mem(void **, unsigned int *);

#endif
