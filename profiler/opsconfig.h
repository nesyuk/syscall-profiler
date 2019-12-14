#ifndef OPS_CONFIG
#define OPS_CONFIG

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILENAME_LEN (short) 256
#define LOGS_DIR "logs"
#define ERROR_FILE_POSTFIX "_errors"
#define LOG_FILE_POSTFIX ""
#define STATS_FILE_POSTFIX "_stats"
#define FILE_EXT ".log"
#define FILE_PRIV 0666
#define FILE_FLAGS O_RDWR|O_CREAT|O_APPEND

#define ENV_STATS_FILE "PROFILE_STATS_FILE"
#define ENV_LOG_FILE "PROFILE_LOG_FILE"
#define ENV_MEMORY_USAGE "PROFILE_MEMORY_USAGE"
#define ENV_FILE_USAGE "PROFILE_FILE_USAGE"
#define ENV_LOG_SYSCALL "PROFILE_LOG_SYSCALL"
#define ENV_OVERHEAD_CALC "PROFILE_OVERHEAD_CALC"

void set_error_filename(char*);
void set_log_filename(char*);
void set_stats_filename(char*);
bool log_memory_usage();
bool log_file_usage();
bool log_syscall();
bool log_overhead_calc();

#endif
