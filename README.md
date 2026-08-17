# Linux LD_PRELOAD Runtime Profiler

A small Linux runtime-instrumentation experiment written in C.

The project uses `LD_PRELOAD` to interpose selected libc functions and
collect statistics about memory allocation and file I/O performed by a
target process.

It was originally written in 2019 while studying Linux systems
programming and dynamic linking.

> **Note:** This is an educational project rather than a production
> profiler. It instruments selected libc functions, not Linux system
> calls directly.

## What It Does

The profiler is implemented as a shared library that can be injected
into a target process using `LD_PRELOAD`.

It currently interposes the following libc functions:

### Memory

- `malloc`
- `calloc`
- `realloc`
- `free`

### File I/O

- `open`
- `close`
- `read`
- `write`

The wrapper functions collect statistics while forwarding the calls to
the original libc implementations.

No changes to the target application's source code are required.

## How It Works

The project uses **dynamic symbol interposition**.

When the profiler library is loaded with `LD_PRELOAD`, calls to selected
libc functions are redirected to wrapper functions provided by the
profiler.

The wrappers resolve the original functions using:

```c
dlsym(RTLD_NEXT, ...)
````

A typical call therefore follows this path:

```text
Target application
       |
       v
   malloc()
       |
       v
LD_PRELOAD profiler
       |
       +---- collect statistics
       |
       v
Original libc malloc()
```

The same approach is used for the instrumented file-I/O functions.

## Project Structure

```text
.
├── lib/
│   ├── profiler/
│   │   ├── opprofiler.c
│   │   ├── opslib.c
│   │   ├── stats.c
│   │   └── logger.c
│   ├── test/
│   │   └── testopprofiler.c
│   └── Makefile
├── logs/
└── README.md
```

## Building

Build the shared library from the `lib` directory:

```bash
cd lib
make
```

This produces:

```text
libopprofiler.so.1.0.1
```

To clean the build:

```bash
make clean
```

## Running

The profiler can be loaded into a program using `LD_PRELOAD`.

For example:

```bash
LD_PRELOAD=./lib/libopprofiler.so.1.0.1 ./lib/test/testopprofiler
```

The profiler collects statistics while the test program is running and
writes the results to log files.

The project also provides a test target:

```bash
cd lib
make test
```

## Example

The profiler can also be used with another dynamically linked program:

```bash
LD_PRELOAD=/path/to/libopprofiler.so.1.0.1 ./my_program
```

The target program continues to use the normal libc implementations,
while the profiler observes the selected operations.

## Concepts Explored

This project was primarily an experiment in understanding:

* Linux shared libraries
* `LD_PRELOAD`
* Dynamic symbol resolution
* `dlsym`
* `RTLD_NEXT`
* Symbol interposition
* Runtime instrumentation
* C function pointers
* Memory allocation
* File descriptors
* File I/O
* Position-independent code (`-fPIC`)
* Building shared libraries with GCC

## Limitations

This project is intentionally small and educational.

It is **not** intended to be a general-purpose or production-ready
profiler.

Some limitations include:

* It instruments selected libc functions rather than kernel syscalls
  directly.
* It does not provide comprehensive coverage of process activity.
* The implementation has limited error handling.
* Thread-safety and re-entrancy have not been fully addressed.
* It has not been tested or designed for production workloads.
* Performance overhead has not been systematically measured.

## Background

I wrote this project in 2019 while studying Linux systems programming.

The main goal was to understand how a running application can be
instrumented externally using a dynamically loaded shared library,
without modifying the application's source code.

The project also provided hands-on experience with dynamic linking,
symbol resolution, and the boundary between an application and the
libraries it uses.
