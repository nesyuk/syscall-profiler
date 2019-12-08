SHELL = /bin/sh

CC := gcc
CFLAGS := -c -fPIC -Wall
LDFLAGS := -shared -fPIC -ldl -Wl,-soname,
LIB_DIR := profiler
TARGET_DIR := lib
TARGET_LIB_SONAME := libopprofiler.so.1
TARGET_LIB := $(TARGET_LIB_SONAME).0.1
TEST_DIR := test
LOGS_DIR := logs

.PHONY: all

all:	lib

lib:	clean pre_install install
	$(CC) $(TARGET_DIR)/*.o $(LDFLAGS)$(TARGET_LIB_SONAME) -o $(TARGET_DIR)/$(TARGET_LIB)

pre_install:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(LOGS_DIR)

install:	install_stats opsconfig.o opslib.o opprofiler.o opslogger.o logger.o

install_stats:	$(LIB_DIR)/stats.c $(LIB_DIR)/stats.h
	$(CC) $(CFLAGS) $(LIB_DIR)/stats.c -o $(TARGET_DIR)/stats.o

opprofiler.o:	$(LIB_DIR)/opprofiler.c $(LIB_DIR)/opprofiler.h
	$(CC) $(CFLAGS) $(LIB_DIR)/opprofiler.c -o $(TARGET_DIR)/opprofiler.o

opslib.o:	$(LIB_DIR)/opslib.c $(LIB_DIR)/opslib.h
	$(CC) $(CFLAGS) $(LIB_DIR)/opslib.c -o $(TARGET_DIR)/opslib.o

logger.o:	$(LIB_DIR)/logger.c $(LIB_DIR)/logger.h
	$(CC) $(CFLAGS) $(LIB_DIR)/logger.c -o $(TARGET_DIR)/logger.o

opslogger.o:	$(LIB_DIR)/opslogger.c $(LIB_DIR)/opslogger.h
	$(CC) $(CFLAGS) $(LIB_DIR)/opslogger.c -o $(TARGET_DIR)/opslogger.o

opsconfig.o:	$(LIB_DIR)/opsconfig.c $(LIB_DIR)/opsconfig.h
	$(CC) $(CFLAGS) $(LIB_DIR)/opsconfig.c -o $(TARGET_DIR)/opsconfig.o

.PHONY: test
test:	test_prepare test_install test_run test_clean

test_prepare:
	-echo "" > $(LOGS_DIR)/errors.log

test_install:
	$(CC) $(TEST_DIR)/test_opprofiler.c -o $(TEST_DIR)/testopprofiler

test_run:
	-LD_PRELOAD=$(TARGET_DIR)/$(TARGET_LIB) ./$(TEST_DIR)/testopprofiler

test_clean:
	-rm $(TEST_DIR)/testopprofiler

.PHONY: clean
clean:
	-rm -rf $(TARGET_DIR) 2>/dev/null
