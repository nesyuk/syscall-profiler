#ifndef TEST_OPPROFILER_SCENARIO_RAND
#define TEST_OPPROFILER_SCENARIO_RAND

#define MIN_NUM_SYSCALLS 1
#define MAX_NUM_SYSCALLS 50
#define OPS_SIZE (size_t) 8

#include "test_util.h"
#include "test_fd.h"
#include "test_mem.h"

void test_rand(int num_of_syscalls);

#endif
