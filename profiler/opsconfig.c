#include "opsconfig.h"

char log_filename[256] = "";
char stats_filename[256] = "";
char error_filename[256] = "";

static bool __is_set(const char *name){
        char *val = getenv(name);
        int i;
        if (val == NULL || sscanf(val, "%i", &i) != 1 || i == 1)
                return true;

        return false;
}

char * get_error_filename(){
        sprintf(error_filename, "./%s/%s", LOGS_DIR, ERROR_FILE);
        return error_filename;
}

char * get_log_filename(){
	sprintf(log_filename, "./%s/%d.log", LOGS_DIR, getpid());
	char *custom_log_name = getenv("PROFILE_LOG_FILE");
	if (custom_log_name != NULL && custom_log_name[0] != '\0')
		sprintf(log_filename, "%s", custom_log_name);
        return log_filename;
}

char * get_stats_filename(){
	sprintf(stats_filename, "./%s/stats_%d.log", LOGS_DIR, getpid());
	char *custom_stats_name = getenv("PROFILE_STATS_FILE");
	if (custom_stats_name != NULL && custom_stats_name[0] != '\0')
		sprintf(stats_filename, "%s", custom_stats_name);
        return stats_filename;
}

bool log_memory_usage(){
	return __is_set("PROFILE_MEMORY_USAGE");
}

bool log_file_usage(){
        return __is_set("PROFILE_FILE_USAGE");
}

bool log_syscall(){
        return __is_set("PROFILE_LOG_SYSCALL");
}

bool log_overhead_calc(){
        return __is_set("PROFILE_OVERHEAD_CALC");
}
