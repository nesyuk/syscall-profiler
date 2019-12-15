#include "logger.h"

void __log(const char *path, const char *msg) {
  int fd = __open(path, FILE_FLAGS, FILE_PRIV);
  __write(fd, msg, strlen(msg) + 1);
  __close(fd);
}

bool __is_valid_filename(const char *filename, const char *filetype) {
  if (filename == NULL || filename[0] == '\0') {
    char error_buf[256];
    sprintf(
        error_buf,
        "Failed to write a message. Reason: empty filename for filetype: %s\n",
        filetype);
    log_error(error_buf);
    return false;
  }
  return true;
}

void log_stats(const char *msg) {
  char filename[MAX_FILENAME_LEN] = "";
  set_stats_filename(filename);
  if (__is_valid_filename(filename, "stats"))
    __log(filename, msg);
}

void log_error(const char *msg) {
  char filename[MAX_FILENAME_LEN] = "";
  set_error_filename(filename);
  __log(filename, msg);
}

void log_msg(const char *msg) {
  char filename[MAX_FILENAME_LEN] = "";
  set_log_filename(filename);
  if (__is_valid_filename(filename, "log"))
    __log(filename, msg);
}
