#include "test_util.h"

void exit_with_error(const char *err_source) {
  perror(err_source);
  printf("%d", errno);
  exit(1);
}

size_t get_rand(size_t min, size_t max) {
  if (max <= min)
    return 0;
  return min + rand() % (max - min);
}

void print_headline_separator() {
  printf("==========================================\n");
}

void print_line_separator() { printf("------------------------\n"); }
