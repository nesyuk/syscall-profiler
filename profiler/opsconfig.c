#include "opsconfig.h"

static bool __is_set(const char *name){
        char *val = getenv(name);
        int i;
        if (val == NULL || sscanf(val, "%i", &i) != 1 || i == 1)
                return true;

        return false;
}

void __set_filename_from_env(char *file, const char *default_postfix, const char *env_var){
	sprintf(file, "./%s/%d%s%s", LOGS_DIR, getpid(), default_postfix, FILE_EXT);
	if(!env_var)
		return;
	char *custom_filename = getenv(env_var);
	if (custom_filename != NULL && custom_filename[0] != '\0')
        sprintf(file, "%s", custom_filename);
}

void set_error_filename(char *file){
	__set_filename_from_env(file, ERROR_FILE_POSTFIX, 0);
}

void set_log_filename(char *file){
	__set_filename_from_env(file, LOG_FILE_POSTFIX, ENV_LOG_FILE);
}

void set_stats_filename(char *file){
	__set_filename_from_env(file, STATS_FILE_POSTFIX, ENV_STATS_FILE);
}

bool log_memory_usage(){
	return __is_set(ENV_MEMORY_USAGE);
}

bool log_file_usage(){
        return __is_set(ENV_FILE_USAGE);
}

bool log_syscall(){
        return __is_set(ENV_LOG_SYSCALL);
}

bool log_overhead_calc(){
        return __is_set(ENV_OVERHEAD_CALC);
}
