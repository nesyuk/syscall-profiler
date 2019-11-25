SHELL = /bin/sh

CC := gcc
LDFLAGS := -shared -fPIC -ldl -Wl,-soname,
LIB_DIR := profiler
TARGET_DIR := lib
TARGET_LIB_SONAME := libopprofiler.so.1
TARGET_LIB := $(TARGET_LIB_SONAME).0.1
TEST_DIR := test

.PHONY: all

all:	clean lib

lib:	$(LIB_DIR)/opprofiler.c $(LIB_DIR)/opprofiler.h
	mkdir -p $(TARGET_DIR)
	$(CC) $(LIB_DIR)/opprofiler.c $(LDFLAGS)$(TARGET_LIB_SONAME) -o $(TARGET_DIR)/$(TARGET_LIB)

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
