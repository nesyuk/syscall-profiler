#include "test_opprofiler.h"

static bool (*test_ops[OPS_SIZE])(void) = {test_malloc, test_open, test_calloc, test_realloc, test_free, test_read, test_write, test_close};

static void **allocated_memory_list;
static unsigned int allocated_memory_count = 0;

static int *opened_files_list;
static size_t opened_files_count = 0;

static void run_tests(int syscalls_num);
static void test_alloc();
static void test_fd();
static void test_rand(int num_of_syscalls);
static void cleanup(int num_of_syscalls);

int main(int argc, char **argv){

	if (argc > 1 && (!isdigit(*argv[1]) || atoi(argv[1]) < 0)){
		printf("Invalid first argument: %s. Must be a number >= 0.\n", argv[1]);
		return 0;
	}

	int const num_of_syscalls = (argc > 1) ? atoi(argv[1]) : -1;
	run_tests(num_of_syscalls);

	return 0;
}

static void run_tests(int syscalls_num){
	print_headline_separator();
        printf("Tests *alloc:\n");
        print_headline_separator();

	test_alloc();

	print_headline_separator();
        printf("Tests fd:\n");
        print_headline_separator();

	test_fd();

	srand(time(0));
        int const num_of_syscalls = (syscalls_num >= 0) ? syscalls_num : get_rand(MIN_NUM_SYSCALLS, MAX_NUM_SYSCALLS);

	print_headline_separator();
        printf("Tests random %d syscalls:\n", num_of_syscalls);
        print_headline_separator();

	test_rand(num_of_syscalls);
}

static void test_alloc(){
	allocated_memory_list = alloca(5*sizeof(void*));
	test_malloc();
	test_malloc();
	test_calloc();
	test_realloc();
	test_free();
	test_free();
	test_free();
	cleanup(5);
}

static void test_fd(){
	opened_files_list = (int *) alloca(3*sizeof(int));
	test_open();
	test_write();
	test_read();
	test_open();
	test_write();
	test_read();
	test_read();
	test_close();
	test_close();
	cleanup(3);
}

static void test_rand(int num_of_syscalls){

        allocated_memory_list = alloca(num_of_syscalls*sizeof(void*));
        opened_files_list = (int *) alloca(num_of_syscalls*sizeof(int));

	for (int i = 0; i < num_of_syscalls; i++){
		printf("[%d] ", i);
		bool op_allowed = 0;
		while(!op_allowed){
			int random_op_idx = rand() % OPS_SIZE;
			op_allowed = (*test_ops[random_op_idx])();
		}
	}
	cleanup(num_of_syscalls);
}

static void cleanup(int num_of_syscalls){
	printf("Freeing memory...\n");
	while(allocated_memory_count > 0){
		free(allocated_memory_list[--allocated_memory_count]);
	}
	printf("Closing and removing test files...\n");
	while(opened_files_count > 0){
		close(opened_files_list[--opened_files_count]);
		remove_test_file(opened_files_count);
	}
	printf("Done!\n");
}

static bool test_malloc(void){
	printf("Test malloc\n");

	size_t rand_size = get_rand(MIN_ALLOC_SIZE, MAX_ALLOC_NMEM*ALLOC_NMEM_SIZE);
	printf("Allocating %ld bytes\n", rand_size);

	void *ptr = malloc(rand_size);
	if (ptr == NULL)
		exit_with_error("malloc");
	allocated_memory_list[allocated_memory_count++] = ptr;
	print_line_separator();
	return 1;
}

static bool test_calloc(void){
	printf("Test calloc\n");

	size_t rand_nmem = get_rand(MIN_ALLOC_NMEM, MAX_ALLOC_NMEM);
	printf("Allocating %ld bytes\n", rand_nmem * ALLOC_NMEM_SIZE);

	void *ptr = calloc(rand_nmem, ALLOC_NMEM_SIZE);
	if (ptr == NULL)
		exit_with_error("calloc");
	allocated_memory_list[allocated_memory_count++] = ptr;
	print_line_separator();
	return 1;
}

static bool test_realloc(void){
	if (allocated_memory_count == 0)
		return 0;
	printf("Test realloc\n");

	size_t new_size = get_rand(MIN_ALLOC_SIZE, MAX_REALLOC_SIZE);
	printf("Reallocating %ld bytes\n", new_size);
	void *ptr = realloc(allocated_memory_list[allocated_memory_count-1], new_size);
	if (ptr == NULL)
		exit_with_error("realloc");
	allocated_memory_list[allocated_memory_count-1] = ptr;
	print_line_separator();
	return 1;
}

static bool test_free(void){
	if(allocated_memory_count == 0)
		return 0;
	printf("Test free\n");

	free(allocated_memory_list[allocated_memory_count-1]);
	allocated_memory_list[--allocated_memory_count] = 0;
	print_line_separator();
	return 1;
}

static bool test_open(void){
	printf("Test open\n");

	/*
	 * TODO: check max number of open files.
	 */
	
	char filename[FILENAME_MAX_SIZE];
	get_testfilename(filename, opened_files_count);

	int fd = open(filename, O_RDWR|O_CREAT, FILE_PERM);
	printf("Created file: %s with fd: %d\n", filename, fd);
	opened_files_list[opened_files_count++] = fd;
	print_line_separator();
	return 1;
}

static bool test_read(void){
	if (opened_files_count == 0)
		return 0;
	printf("Test read\n");

	size_t const buf_size = get_rand(MIN_BUF_SIZE, MAX_BUF_SIZE);
	char buf[buf_size];
	size_t bytes = read(opened_files_list[opened_files_count-1], buf, buf_size);
	printf("Read %ld bytes (buf size: %ld) from file with fd: %d\nbuf:%s\n", bytes, buf_size, opened_files_list[opened_files_count-1], buf);
	print_line_separator();
	return 1;
}

static bool test_write(void){
	if (opened_files_count == 0)
		return 0;
	printf("Test write\n");

	size_t const buf_size = get_rand(MIN_BUF_SIZE, MAX_BUF_SIZE);
	char buf[buf_size-1];
	populate_buffer(buf, buf_size);
	size_t bytes = write(opened_files_list[opened_files_count-1], buf, buf_size);
	printf("Wrote %ld bytes to file with fd: %d\nbuf: %s\n", bytes, opened_files_list[opened_files_count-1], buf);
	print_line_separator();
	return 1;
}

static bool test_close(void){
	if (opened_files_count == 0)
		return 0;
	close(opened_files_list[opened_files_count-1]);
	printf("Test close file with fd %d\n", opened_files_list[opened_files_count-1]);
	opened_files_list[--opened_files_count] = 0;
	remove_test_file(opened_files_count);
	print_line_separator();
	return 1;
}
