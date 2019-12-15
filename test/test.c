#include "test.h"

void run_tests(int);

int main(int argc, char **argv) {

  if (argc > 1 && (!isdigit(*argv[1]) || atoi(argv[1]) < 0)) {
    printf("Invalid first argument: %s. Must be a number >= 0.\n", argv[1]);
    return 0;
  }

  int const num_of_syscalls = (argc > 1) ? atoi(argv[1]) : -1;
  run_tests(num_of_syscalls);

  return 0;
}

void run_tests(int syscalls_num) {
  print_headline_separator();
  printf("Tests *alloc:\n");
  print_headline_separator();

  test_alloc();

  print_headline_separator();
  printf("Tests fd:\n");
  print_headline_separator();

  test_fd();

  srand(time(0));
  int const num_of_syscalls =
      (syscalls_num >= 0) ? syscalls_num
                          : get_rand(MIN_NUM_SYSCALLS, MAX_NUM_SYSCALLS);

  print_headline_separator();
  printf("Tests random %d syscalls:\n", num_of_syscalls);
  print_headline_separator();

  test_rand(num_of_syscalls);
}
