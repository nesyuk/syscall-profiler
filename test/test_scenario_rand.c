#include "test_scenario_rand.h"

static bool (*test_mem_ops[5])(void**, unsigned int*) = {test_malloc, test_free, test_calloc, test_realloc, test_free};
static bool (*test_fd_ops[4])(int *, size_t*) = {test_open, test_read, test_write, test_close};

void test_rand(int num_of_syscalls){
	
	int *opened_files_list;
	size_t opened_files_count = 0;

	opened_files_list = (int *) alloca(num_of_syscalls*sizeof(int));

	void **allocated_memory_list;
	unsigned int allocated_memory_count = 0;

	allocated_memory_list = alloca(num_of_syscalls*sizeof(void*));

	for (int i = 0; i < num_of_syscalls; i++){
		printf("[%d] ", i);
		bool op_allowed = 0;
		while(!op_allowed){
			int random_op_idx = rand() % OPS_SIZE;
			if (random_op_idx < 5){
				op_allowed = (*test_mem_ops[random_op_idx])(allocated_memory_list, &allocated_memory_count);
			} else {
				op_allowed = (*test_fd_ops[random_op_idx-5])(opened_files_list, &opened_files_count);
			}
		}
	}
	cleanup_fd(opened_files_list, &opened_files_count);
	cleanup_mem(allocated_memory_list, &allocated_memory_count);
}
