#include "logger.h"

static char path[126];

void __log(const char *path, const char *msg){
	int fd = __open(path, O_RDWR|O_CREAT|O_APPEND, FILE_PRIV);
	__write(fd, msg, strlen(msg) + 1);
	__close(fd);
}

void log_stats(const char *msg){
        sprintf(path, "./%s/%s", LOGS_DIR, STATS_FILE);
        __log(path, msg);
}

void log_error(const char *msg){
        sprintf(path, "./%s/%s", LOGS_DIR, ERROR_FILE);
        __log(path, msg);
}

void log_msg(const char *msg){
	sprintf(path, "./%s/%s", LOGS_DIR, LOG_FILE);
        __log(path, msg);
}
