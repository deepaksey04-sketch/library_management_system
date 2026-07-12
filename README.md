# Library Management System in C

This is a console-based Library Management System with separate source files and a Makefile.

## Build

```sh
make
```

## Run

```sh
./lms
```

On Windows, run:

```sh
lms.exe
```

## Files

- `include/lms.h` - shared structures, constants, and function declarations
- `src/main.c` - program entry point
- `src/menu.c` - main menu
- `src/books.c` - book add, update, remove, search, and view functions
- `src/issues.c` - issue, return, fine calculation, and issued book listing
- `src/storage.c` - file loading and saving
- `src/utils.c` - input, search, and date helper functions
- `Makefile` - build instructions

The program creates `books.dat` and `issues.dat` when data is saved.
