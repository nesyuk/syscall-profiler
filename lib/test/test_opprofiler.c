#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define TEST_FILENAME "testfile"
#define OPS_SIZE (size_t) 8

static void test_malloc(void);
static void test_calloc(void);
static void test_realloc(void);
static void test_free(void);
static void test_open(void);
static void test_read(void);
static void test_write(void);
static void test_close(void);

static void run(int);
static void cleanup();

static void (*test_ops[OPS_SIZE])(void) = {test_malloc, test_calloc, test_realloc, test_free, test_open, test_read, test_write, test_close};

int main(int argc, char **argv){

	if (argc > 1 && (!isdigit(*argv[1]) || atoi(argv[1]) < 0)){
		printf("Invalid first argument: %s. Must be a number >= 0.\n", argv[1]);
		return 0;
	}
	srand(time(0));
	int num_of_syscalls = (argc > 1) ? atoi(argv[1]) : rand() % 50;

	run(num_of_syscalls);
	cleanup();

	return 0;
}

static void run(int num_of_syscalls){

	printf("Running tests for %d number of syscalls:\n", num_of_syscalls);

	for (int i = 0; i < num_of_syscalls; i++){
		(*test_ops[i % OPS_SIZE])();
	}
}

static void cleanup(int num_of_syscalls){
	printf("Freeing memory... ");
	printf("Done!\n");
}

static void test_malloc(void){
	printf("Test malloc\n");
}

static void test_calloc(void){
	printf("Test calloc\n");
}

static void test_realloc(void){
	printf("Test realloc\n");
}

static void test_free(void){
	printf("Test free\n");
}

static void test_open(void){
	printf("Test open\n");
}

static void test_read(void){
	printf("Test read\n");
}

static void test_write(void){
	printf("Test write\n");
}

static void test_close(void){
	printf("Test close\n");
}
