#include "logger.h"

void __log(const char *path, const char *msg){
	int fd = __open(path, FILE_FLAGS, FILE_PRIV);
	__write(fd, msg, strlen(msg) + 1);
	__close(fd);
}

bool __is_valid_filename(const char *filename, const char *msg, const char *filetype){
	if (filename == NULL || filename[0] == '\0'){
		char error_buf[256];
                sprintf(error_buf, "Failed to write a message: %s. Reason: empty %s file name\n", filetype, msg);
                log_error(error_buf);
		return false;
	}
	return true;
}

void log_stats(const char *msg){
	char *filename = get_stats_filename();
	if(__is_valid_filename(filename, msg, "stats"))
		__log(filename, msg);
}

void log_error(const char *msg){
        __log(get_error_filename(), msg);
}

void log_msg(const char *msg){
	char *filename = get_log_filename();
	if(__is_valid_filename(filename, msg, "log"))
		__log(get_log_filename(), msg);
}
