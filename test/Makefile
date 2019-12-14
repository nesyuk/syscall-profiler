.PHONY: test_install
test_install: test_clean test.o
	$(CC) *.o -o $(TEST_OBJ)

test.o:	test.c test.h test_util.o test_scenario_rand.o test_scenario_mem.o test_scenario_mem.o
	$(CC) $(CFLAGS) test.c -o $@

test_scenario_rand.o:	test_scenario_rand.c test_scenario_rand.h test_scenario_fd.o test_scenario_mem.o test_util.o
	$(CC) $(CFLAGS) test_scenario_rand.c -o $@

test_scenario_fd.o:	test_scenario_fd.c test_scenario_fd.h test_fd.o test_util.o
	$(CC) $(CFLAGS) test_scenario_fd.c -o $@

test_scenario_mem.o:	test_scenario_mem.c test_scenario_mem.h test_mem.o test_util.o
	$(CC) $(CFLAGS) test_scenario_mem.c -o $@

test_fd.o:	test_fd.c test_fd.h test_util.o
	$(CC) $(CFLAGS) test_fd.c -o $@

test_mem.o:	test_mem.c test_mem.h test_util.o
	$(CC) $(CFLAGS) test_mem.c -o $@

test_util.o:	test_util.c test_util.h
	$(CC) $(CFLAGS) test_util.c -o $@

test_clean:
	-rm *.o
