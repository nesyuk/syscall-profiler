#include "opslogger.h"

static bool has_log_events = false;
static char buf[1024];
static char args[640];

const int file_flags_size = 21;
static int file_flags[] = {O_APPEND, O_ASYNC, O_CLOEXEC, O_CREAT, __O_TMPFILE, __O_DIRECT, O_DIRECTORY, O_DSYNC,
        O_EXCL, __O_LARGEFILE, __O_NOATIME, O_NOCTTY, O_NOFOLLOW, O_NONBLOCK, __O_PATH, O_SYNC, O_TRUNC,
        O_RDWR, O_RDONLY, O_WRONLY, O_EXCL};

static char *file_flags_names[] = {"O_APPEND", "O_ASYNC", "O_CLOEXEC", "O_CREAT", "O_TMPFILE", "O_DIRECT", "O_DIRECTORY", "O_DSYNC",
        "O_EXCL", "O_LARGEFILE", "O_NOATIME", "O_NOCTTY", "O_NOFOLLOW", "O_NONBLOCK", "O_PATH", "O_SYNC", "O_TRUNC",
        "O_RDWR", "O_RDONLY", "O_WRONLY", "O_EXCL"};
/*
 * Log syscall event
 */
void __log_syscall(const char *syscall, const char *args){
        if (!has_log_events){
                // print header
                sprintf(buf, "timestamp (nanosec):%6s syscall:%7s args:%5s\n\n", "", "", "");
                has_log_events = true;
                log_msg(buf);
        }
        int max_space = 15;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long long timestamp_ms = (tv.tv_sec) * SEC_TO_NANOSEC + (tv.tv_usec);
        sprintf(buf, "%lld%10s %s%*s %s%*s\n", timestamp_ms,  "",
                        syscall,(int) (max_space - strlen(syscall)), "",
                        args, (int) (max_space - strlen(args)), "");
        log_msg(buf);
}

void log_malloc(size_t size){
	sprintf(args, "size: %ld", size);
	__log_syscall("malloc", args);
}

void log_calloc(size_t nmemb, size_t size){
	sprintf(args, "nmemb: %ld, size: %ld", nmemb, size);
	__log_syscall("calloc", args);
}

void log_realloc(void *ptr, size_t size){
	sprintf(args, "ptr: %p, size: %ld", ptr, size);
	__log_syscall("realloc", args);
}

void log_free(void *ptr){
	sprintf(args, "ptr: %p", ptr);
	__log_syscall("free", args);
}

void log_open(const char *pathname, int flags, mode_t mode){
	char flag_args[512] = "";

	for(int i = 0; i < file_flags_size; i++){
		if(flags & file_flags[i])
			sprintf(flag_args + strlen(flag_args), "%s ", file_flags_names[i]);
	}

	sprintf(args, "pathname: %s, flags: %s(%d), mode: %d", pathname, flag_args, flags, mode);
	__log_syscall("open", args);
}

void log_close(int fd){
	sprintf(args, "fd: %d", fd);
	__log_syscall("close", args);
}

void log_read(int fd, void *buf, size_t count){
	sprintf(args, "fd: %d, buf: %p, count: %ld", fd, buf, count);
	__log_syscall("read", args);
}

void log_write(int fd, const void *buf, size_t count){
	sprintf(args, "fd: %d, buf: %p, count: %ld", fd, buf, count);
	__log_syscall("write", args);
}
