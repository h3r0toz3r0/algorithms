# Algorithms

## Overview

The algorithms repository provides a collection of essential algorithm implementations, including sorting, searching, and more, organized for easy integration and use in various projects.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Requirements](#requirements)
  - [Setup](#setup)
  - [Operator Guide](#operator-guide)
  - [Testing](#testing)
- [Known Issues/Bugs](#known-issuesbugs)
- [Repository Structure](#repository-structure)

## Usage

### Requirements

- **Hardware**: Any machine capable of running C.
- **Operating System**: Recommended Ubuntu 22.04.
- **Software**: 
  - `git` to clone the repo
  - Dependencies installed via `setup.sh`

### Setup

1. Install `git`:

   ```sh
   sudo apt install git
   ```
1. Clone the repository:

   ```sh
   git clone https://github.com/yourusername/data-structures.git
   cd data-structures/
   ```
1. Install necessary dependencies:

   ```sh
   ./setup.sh
   ```

### Operator Guide

To compile the C files and generate the object files, use:

```sh
make all
```

To remove the generated object files and clean up the build directory, use:

```sh
make clean
```

To use the algorithms, write a program that links against the generated object files and utilizes the internal functions.

### Testing

Each algorithm includes tests located in the tests/ directory. The tests cover edge cases, performance benchmarks, and comparisons with built-in library functions.

To compile the tests, use:

```sh
make test
```

To remove the generated object files and clean up the build directory, use:

```sh
make clean
```

The testing suite supports various command-line arguments:

```sh
./bin/test_main help
./bin/test_main list
./bin/test_main <specific suite name>
```

- `help`: Displays a usage guide.
- `list`: Lists all available test suite names.
- `<specific suite name>`: Runs a specific test suite.

The Makefile includes additional commands:

```sh
make format
make valgrind
```

- `format`: Formats all C source and header files using clang-format-15 to match Barr C standards.
- `valgrind`: Runs all tests with Valgrind to check for memory leaks.

## Known Issues/Bugs

No known issues.

## Repository Structure

```
algorithms/
│
├── src/
│   ├── sorting/
│   │   ├── bubble_sort.c
│   │   ├── merge_sort.c
│   │   └── quick_sort.c
│   ├── searching/
│   │   ├── binary_search.c
│   │   ├── dfs.c
│   │   └── bfs.c
│   ├── dynamic_programming/
│   │   ├── fibonacci.c
│   │   ├── knapsack.c
│   │   └── lcs.c
│   ├── graphs/
│   │   ├── dijkstra.c
│   │   ├── kruskal.c
│   │   └── prim.c
│   ├── strings/
│   │   ├── kmp.c
│   │   ├── rabin_karp.c
│   │   └── trie.c
│
├── include/
│   ├── sorting/
│   │   ├── bubble_sort.h
│   │   ├── merge_sort.h
│   │   └── quick_sort.h
│   ├── searching/
│   │   ├── binary_search.h
│   │   ├── dfs.h
│   │   └── bfs.h
│   ├── dynamic_programming/
│   │   ├── fibonacci.h
│   │   ├── knapsack.h
│   │   └── lcs.h
│   ├── graphs/
│   │   ├── dijkstra.h
│   │   ├── kruskal.h
│   │   └── prim.h
│   ├── strings/
│   │   ├── kmp.h
│   │   ├── rabin_karp.h
│   │   └── trie.h
|
├── tests/
│
└── README.md
```
