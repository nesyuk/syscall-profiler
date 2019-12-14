#include "test_scenario_mem.h"

void test_alloc(){
	void **allocated_memory_list;
	unsigned int count = 0;
	int syscalls_count = 5;

	allocated_memory_list = alloca(syscalls_count*sizeof(void*));

	test_malloc(allocated_memory_list, &count);
	test_malloc(allocated_memory_list, &count);
	test_calloc(allocated_memory_list, &count);
	test_realloc(allocated_memory_list, &count);
	test_free(allocated_memory_list, &count);
	test_free(allocated_memory_list, &count);
	test_free(allocated_memory_list, &count);

	cleanup_mem(allocated_memory_list, &count);
}
