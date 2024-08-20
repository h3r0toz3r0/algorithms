# Algorithms

## Overview

This repository contains implementations of various algorithms in C, C++, and Python. Each algorithm is categorized by its type (e.g., sorting, searching, dynamic programming) and is implemented in all three languages to showcase different language features and best practices.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Requirements](#requirements)
  - [Setup](#setup)
  - [Operator Guide](#operator-guide)
    - [C Algorithms](#c-algorithms)
    - [C++ Algorithms](#c-algorithms)
    - [Python Algorithms](#python-algorithms)
  - [Testing](#testing)
    - [C Algorithm Tests](#c-algorithm-tests)
    - [C++ Algorithm Tests](#c-algorithm-tests)
    - [Python Algorithm Tests](#python-algorithm-tests)
- [Known Issues/Bugs](#known-issuesbugs)
- [Repository Structure](#repository-structure)

## Usage

### Requirements

- **Hardware**: Any machine capable of running a C, C++, and Python environment.
- **Operating System**: Recommended Ubuntu 22.04.
- **Software**: 
  - `git`: to clone the repo
  - all other dependencies will be installed with the `setup.sh`

### Setup

1. Install `git`:

   ```sh
   sudo apt install git
   ```
1. Clone the repository:

   ```sh
   git clone https://github.com/yourusername/algorithms.git
   cd algorithms
   ```
1. Install necessary dependencies:

   ```sh
   ./setup.sh
   ```

### Operator Guide

#### C Algorithms

To compile the C algorithms and generate the corresponding object files, use the following commands:

```sh
make all
```

or

```sh
make C
```

To remove the generated object files and clean up the build directory, use:

```sh
make clean
```

To interact with the algorithms, you will need to write a program that links against the generated object files and uses the internal functions.

---

#### C++ Algorithms

---

#### Python Algorithms

---

### Testing

Each algorithm has accompanying tests located in the tests/ directory. Test coverage includes edge cases, performance benchmarks, and comparisons against built-in library functions (where applicable).

#### C Algorithm Tests

To compile the C algorithm tests, use the following command:

```sh
make test
```

To remove the generated object files and clean up the build directory, use:

```sh
make clean
```

To run all tests, use:

```sh
make test execute
```
Alternatively, to run tests with `Valgrind` to check for memory leaks, use:

```sh
make test valgrind
```
The testing suite supports various command-line arguments. You can use these with either the `execute` or `valgrind` modes:

```sh
make test execute help
make test execute list
make test execute <specific suite name>

make test valgrind help
make test valgrind list
make test valgrind <specific suite name>
```

- `help`: Displays a usage guide.
- `list`: Lists all available test suite names.
- `<specific suite name>`: Runs a specific test suite.

#### C++ Algorithm Tests

---

#### Python Algorithm Tests

---

## Known Issues/Bugs

Some algorithms may not be optimized for large datasets in their naive implementations.
Platform-specific issues might arise due to differences in compilers or Python versions.

## Repository Structure

```
algorithms/
│
├── C/
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
│   └── data_structures/
│       ├── linked_list.c
│       ├── stack.c
│       ├── queue.c
│       ├── binary_tree.c
│       └── hash_table.c
│
├── C++/
│   ├── sorting/
│   │   ├── bubble_sort.cpp
│   │   ├── merge_sort.cpp
│   │   └── quick_sort.cpp
│   ├── searching/
│   │   ├── binary_search.cpp
│   │   ├── dfs.cpp
│   │   └── bfs.cpp
│   ├── dynamic_programming/
│   │   ├── fibonacci.cpp
│   │   ├── knapsack.cpp
│   │   └── lcs.cpp
│   ├── graphs/
│   │   ├── dijkstra.cpp
│   │   ├── kruskal.cpp
│   │   └── prim.cpp
│   ├── strings/
│   │   ├── kmp.cpp
│   │   ├── rabin_karp.cpp
│   │   └── trie.cpp
│   └── data_structures/
│       ├── linked_list.cpp
│       ├── stack.cpp
│       ├── queue.cpp
│       ├── binary_tree.cpp
│       └── hash_table.cpp
│
├── Python/
│   ├── sorting/
│   │   ├── bubble_sort.py
│   │   ├── merge_sort.py
│   │   └── quick_sort.py
│   ├── searching/
│   │   ├── binary_search.py
│   │   ├── dfs.py
│   │   └── bfs.py
│   ├── dynamic_programming/
│   │   ├── fibonacci.py
│   │   ├── knapsack.py
│   │   └── lcs.py
│   ├── graphs/
│   │   ├── dijkstra.py
│   │   ├── kruskal.py
│   │   └── prim.py
│   ├── strings/
│   │   ├── kmp.py
│   │   ├── rabin_karp.py
│   │   └── trie.py
│   └── data_structures/
│       ├── linked_list.py
│       ├── stack.py
│       ├── queue.py
│       ├── binary_tree.py
│       └── hash_table.py
│
├── tests/
│   ├── C/
│   ├── C++/
│   └── Python/
│
└── README.md
```
