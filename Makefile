SHELL = /bin/sh

export CC := gcc
export CFLAGS := -c -fPIC -Wall
LDFLAGS := -shared -fPIC -ldl -Wl,-soname,
LIB_DIR := profiler
TARGET_DIR := lib
TARGET_LIB_SONAME := libopprofiler.so.1
TARGET_LIB := $(TARGET_LIB_SONAME).0.1
TEST_DIR := test
export TEST_OBJ := testopprofiler.o
LOGS_DIR := logs

.PHONY: all
all:	clean pre_install
	cd $(LIB_DIR) && $(MAKE) install
	$(CC) $(LIB_DIR)/*.o $(LDFLAGS)$(TARGET_LIB_SONAME) -o $(TARGET_DIR)/$(TARGET_LIB)

pre_install:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(LOGS_DIR)

.PHONY: test
test:	
	cd $(TEST_DIR) && $(MAKE) test_install
	LD_PRELOAD=$(TARGET_DIR)/$(TARGET_LIB) ./$(TEST_DIR)/$(TEST_OBJ)

.PHONY: clean
clean:
	-rm -rf $(TARGET_DIR) 2>/dev/null
	-rm -rf $(LOGS_DIR) 2>/dev/null
