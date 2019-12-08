#ifndef OPS_LOGGER
#define OPS_LOGGER

#include <string.h>
#include <stdio.h>

#include "opslib.h"

#define LOGS_DIR "logs"
#define STATS_FILE "stats_log.log"
#define ERROR_FILE "errors.log"
#define LOG_FILE "syscalls.log"
#define FILE_PRIV 0667

void log_stats(const char *msg);
void log_error(const char *msg);
void log_msg(const char *msg);

#endif
