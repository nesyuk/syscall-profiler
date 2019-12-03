#include "logger.h"

void log_stats(const char *msg){
	char path[126];
        sprintf(path, "./%s/%s", LOGS_DIR, STATS_FILE);
        int fd = __open(path, O_RDWR|O_CREAT|O_APPEND, FILE_PRIV);
        __write(fd, msg, strlen(msg) + 1);
        __close(fd);
}

void log_error(const char *msg){
	char path[126];
        sprintf(path, "./%s/%s", LOGS_DIR, ERROR_FILE);
        int fd = __open(path, O_RDWR|O_CREAT|O_APPEND, FILE_PRIV);
        __write(fd, msg, strlen(msg) + 1);
        __close(fd);
}
