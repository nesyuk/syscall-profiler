#include "test_scenario_fd.h"

void test_fd(){
	int *opened_files_list;
	size_t count = 0;
	int syscalls_count = 3;

	opened_files_list = (int *) alloca(syscalls_count*sizeof(int));

	test_open(opened_files_list, &count);
	test_write(opened_files_list, &count);
	test_read(opened_files_list, &count);
	test_open(opened_files_list, &count);
	test_write(opened_files_list, &count);
	test_read(opened_files_list, &count);
	test_read(opened_files_list, &count);
	test_close(opened_files_list, &count);
	test_close(opened_files_list, &count);
	
	cleanup_fd(opened_files_list, &count);
}

