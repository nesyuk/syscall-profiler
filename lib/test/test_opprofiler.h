#ifndef TEST_OPPROFILER
#define TEST_OPPROFILER

#define MIN_NUM_SYSCALLS 1
#define MAX_NUM_SYSCALLS 300
#define OPS_SIZE (size_t) 8

#define MIN_ALLOC_NMEM (size_t) 1
#define MAX_ALLOC_NMEM (size_t) 100
#define ALLOC_NMEM_SIZE (size_t) 2
#define MIN_ALLOC_SIZE (size_t) 1
#define MAX_REALLOC_SIZE (size_t) 300

#define TEST_FILENAME "testfile"
#define MIN_BUF_SIZE (size_t) 1
#define MAX_BUF_SIZE (size_t) 100
#define MAX_CHAR 127

#define FILE_PERM 0644
#define FILENAME_MAX_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static bool test_malloc(void);
static bool test_calloc(void);
static bool test_realloc(void);
static bool test_free(void);
static bool test_open(void);
static bool test_read(void);
static bool test_write(void);
static bool test_close(void);

static void run(int);
static void cleanup();

static inline void exit_with_error(const char *err_source){
        perror(err_source);
        printf("%d", errno);
        exit(1);
}

static inline size_t get_rand(size_t min, size_t max){
        if (max <= min)
                return 0;
        return min + rand() % (max - min);
}

static inline void populate_buffer(char *buf, size_t size){
        for(size_t i = 0; i < size; i++){
                buf[i] = get_rand('0', MAX_CHAR);
        }
}

static inline void get_testfilename(char *filename, size_t filenumber){
	sprintf(filename, "%s_%ld", TEST_FILENAME, filenumber);
}

static inline void remove_test_file(size_t filenumber){
	char filename[FILENAME_MAX_SIZE];
	get_testfilename(filename, filenumber);
	unlink(filename);
}

static inline void print_headline_separator(){
        printf("=========================================\n");
}

static inline void print_line_separator(){
        printf("------------------------------\n");
}

#endif
