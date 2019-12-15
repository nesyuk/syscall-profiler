#include "test_mem.h"

void cleanup_mem(void **allocated_memory_list,
                 unsigned int *allocated_memory_count) {
  printf("Freeing memory...");

  while (*allocated_memory_count > 0) {
    free(allocated_memory_list[--(*allocated_memory_count)]);
  }
  printf("\n");
}

bool test_malloc(void **allocated_memory_list,
                 unsigned int *allocated_memory_count) {
  printf("Test malloc\n");

  size_t rand_size = get_rand(MIN_ALLOC_SIZE, MAX_ALLOC_NMEM * ALLOC_NMEM_SIZE);
  printf("Allocating %ld bytes\n", rand_size);

  void *ptr = malloc(rand_size);
  if (ptr == NULL)
    exit_with_error("malloc");
  allocated_memory_list[(*allocated_memory_count)++] = ptr;
  print_line_separator();
  return 1;
}

bool test_calloc(void **allocated_memory_list,
                 unsigned int *allocated_memory_count) {
  printf("Test calloc\n");

  size_t rand_nmem = get_rand(MIN_ALLOC_NMEM, MAX_ALLOC_NMEM);
  printf("Allocating %ld bytes\n", rand_nmem * ALLOC_NMEM_SIZE);

  void *ptr = calloc(rand_nmem, ALLOC_NMEM_SIZE);
  if (ptr == NULL)
    exit_with_error("calloc");
  allocated_memory_list[(*allocated_memory_count)++] = ptr;
  print_line_separator();
  return 1;
}

bool test_realloc(void **allocated_memory_list,
                  unsigned int *allocated_memory_count) {
  if (*allocated_memory_count == 0)
    return 0;
  printf("Test realloc\n");

  size_t new_size = get_rand(MIN_ALLOC_SIZE, MAX_REALLOC_SIZE);
  printf("Reallocating %ld bytes\n", new_size);
  unsigned int idx = *allocated_memory_count - 1;
  void *ptr = realloc(allocated_memory_list[idx], new_size);
  if (ptr == NULL)
    exit_with_error("realloc");
  allocated_memory_list[idx] = ptr;
  print_line_separator();
  return 1;
}

bool test_free(void **allocated_memory_list,
               unsigned int *allocated_memory_count) {
  if (*allocated_memory_count == 0)
    return 0;
  printf("Test free\n");
  free(allocated_memory_list[*allocated_memory_count - 1]);
  allocated_memory_list[--(*allocated_memory_count)] = 0;
  print_line_separator();
  return 1;
}
