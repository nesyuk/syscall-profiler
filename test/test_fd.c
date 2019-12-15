#include "test_fd.h"

void __remove_test_file(size_t filenumber) {
  char filename[FILENAME_MAX_SIZE];
  get_testfilename(filename, filenumber);
  unlink(filename);
}

void cleanup_fd(int *opened_files_list, size_t *opened_files_count) {
  printf("Closing and removing test files...");

  while (*opened_files_count > 0) {
    close(opened_files_list[--*(opened_files_count)]);
    __remove_test_file(*opened_files_count);
  }
  printf("\n");
}

bool test_open(int *opened_files_list, size_t *opened_files_count) {
  printf("Test open\n");

  // TODO: add check for exceeded files, log error
  char filename[FILENAME_MAX_SIZE];
  get_testfilename(filename, *opened_files_count);

  int fd = open(filename, O_RDWR | O_CREAT, FILE_PERM);
  printf("Created file: %s with fd: %d\n", filename, fd);
  opened_files_list[*opened_files_count] = fd;
  (*opened_files_count)++;
  print_line_separator();
  return 1;
}

bool test_read(int *opened_files_list, size_t *opened_files_count) {
  if (*opened_files_count == 0)
    return 0;
  printf("Test read\n");

  size_t const buf_size = get_rand(MIN_BUF_SIZE, MAX_BUF_SIZE);
  char buf[buf_size];

  // set file cursor to position 0
  size_t idx = (*opened_files_count) - 1;
  lseek(opened_files_list[idx], 0, SEEK_SET);

  size_t bytes = read(opened_files_list[idx], buf, buf_size);
  printf("Read %ld bytes (buf size: %ld) from file with fd: %d\nbuf:%s\n",
         bytes, buf_size, opened_files_list[idx], buf);
  print_line_separator();
  return 1;
}

bool test_write(int *opened_files_list, size_t *opened_files_count) {
  if (*opened_files_count == 0)
    return 0;
  printf("Test write\n");

  size_t idx = (*opened_files_count) - 1;
  size_t const buf_size = get_rand(MIN_BUF_SIZE, MAX_BUF_SIZE);
  char buf[buf_size - 1];
  populate_buffer(buf, buf_size);
  size_t bytes = write(opened_files_list[idx], buf, buf_size);
  printf("Wrote %ld bytes to file with fd: %d\nbuf: %s\n", bytes,
         opened_files_list[idx], buf);
  print_line_separator();
  return 1;
}

bool test_close(int *opened_files_list, size_t *opened_files_count) {
  if (*opened_files_count == 0)
    return 0;

  size_t idx = (*opened_files_count) - 1;
  close(opened_files_list[idx]);
  printf("Test close file with fd %d\n", opened_files_list[idx]);
  opened_files_list[--(*opened_files_count)] = 0;
  __remove_test_file(*opened_files_count);
  print_line_separator();
  return 1;
}
