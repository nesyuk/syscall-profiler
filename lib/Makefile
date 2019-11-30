SHELL = /bin/sh

CC := gcc
CFLAGS := -c -fPIC -Wall
LDFLAGS := -shared -fPIC -ldl -Wl,-soname,
LIB_DIR := profiler
TARGET_DIR := lib
TARGET_LIB_SONAME := libopprofiler.so.1
TARGET_LIB := $(TARGET_LIB_SONAME).0.1
TEST_DIR := test

.PHONY: all

all:	lib

lib:	clean pre_install install
	$(CC) $(TARGET_DIR)/*.o $(LDFLAGS)$(TARGET_LIB_SONAME) -o $(TARGET_DIR)/$(TARGET_LIB)

pre_install:
	mkdir -p $(TARGET_DIR)

install:	$(LIB_DIR)/opslib.c $(LIB_DIR)/opslib.h $(LIB_DIR)/opprofiler.c $(LIB_DIR)/opprofiler.h
	$(CC) $(CFLAGS) $(LIB_DIR)/opslib.c -o $(TARGET_DIR)/opslib.o
	$(CC) $(CFLAGS) $(LIB_DIR)/opprofiler.c -o $(TARGET_DIR)/opprofiler.o

.PHONY: test
test:	test_install test_run test_clean

test_install:
	$(CC) $(TEST_DIR)/test_opprofiler.c -o $(TEST_DIR)/testopprofiler

test_run:
	-LD_PRELOAD=$(TARGET_DIR)/$(TARGET_LIB) ./$(TEST_DIR)/testopprofiler

test_clean:
	-rm $(TEST_DIR)/testopprofiler

.PHONY: clean
clean:
	-rm -rf $(TARGET_DIR) 2>/dev/null
