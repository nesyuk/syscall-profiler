#ifndef OPS_CONFIG
#define OPS_CONFIG

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define LOGS_DIR "logs"
#define ERROR_FILE "errors.log"
#define FILE_PRIV 0666
#define FILE_FLAGS O_RDWR|O_CREAT|O_APPEND

char * get_error_filename();
char * get_log_filename();
char * get_stats_filename();
bool log_memory_usage();
bool log_file_usage();
bool log_syscall();
bool log_overhead_calc();

#endif
