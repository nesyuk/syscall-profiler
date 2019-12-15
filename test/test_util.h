#ifndef TEST_OPPROFILER_UTIL
#define TEST_OPPROFILER_UTIL

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void exit_with_error(const char *);
size_t get_rand(size_t, size_t);
void print_headline_separator();
void print_line_separator();

#endif