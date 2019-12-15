Syscall profiler
=================

Syscall profiler is a shared library that collects the statistics of the syscalls of a specified program/process and saves them to logiles.
Supported syscalls:

	memory allocation: malloc, calloc, realloc, free
	file operations: open, read, write, close

## Building

Run `make` in the project's directory (after cloning the repository). This will create two subfolders:

	lib/
	logs/
the lib/ folder will contain the .so library file which you can use to profile the syscalls of a certain program

the logs/ folder will contain the profiled syscalls for each program (shown by the process id)

## Installing

After building you have the .so library file in the /lib folder. To profile the syscalls of your program, set the environment variable during runtime/execution:

	LD_PRELOAD=<profiler_dir>/lib/libopprofiler.so.1.0.1 ./<your_prog_name>

## Testing

To see syscall profiler in action after building the library file, you can run:

	make test
This will run 3 tests:

	1) Tests for memory allocation
	2) Tests for file operations
	3) Random tests for all supported syscalls. (Default number of performed syscalls is 50.)
You can find the log files after running the tests in the logs/ folder

## Statistic logs

Can be found in the /logs folder in following filename format: `<pid>_stats.log`.

These logfiles contain information in following format:
For memory allocation syscalls:

	Total allocated memory: 0 bytes (~0KB)
	Total freed memory: 0 bytes (~0KB)
	Total overhead: 0 bytes (~0KB)
	Allocated memory info per pointer:
	| ptr | malloc (bytes) | calloc (nmemb x bytes) | realloc (bytes) | last allocated memory size (bytes) | total free size (bytes)
This data is logged on each free() syscall.

For file operation syscalls:

	Total open(): 0 times
	Total close(): 0 times
	Total overhead: 0 bytes (~0KB)
	File operations info per file descriptor:
	| file descriptor #: | open (times): | read (bytes): | write (bytes): | close (times): |
This data is logged on each close() syscall.

## Syscall logs

Can be found in the /logs folder in following filename format: `<pid>.log`.

These logs files contain information in the following format:

	timestamp (nanosec):       syscall:        args:
and are logged on each syscall.

## Customizing

To disable specific logging info, you can set following environment variables:

	PROFILE_MEMORY_USAGE=0 (to disable statistics for memory allocation, default = enabled)
	PROFILE_FILE_USAGE=0 (to disable statistics for file operations, default = enabled)
	PROFILE_LOG_SYSCALL=0 (to disable logging of called syscalls, default = enabled)
	PROFILE_OVERHEAD_CALC=0 (to disable showing statistics of overhead, default = enabled)

To change log file names:

	PROFILE_LOG_FILE=<name> (default = "<pid>.log")
	PROFILE_STATS_FILE=<name> (default = "<pid>_stats.log")
