# CPPTEST

Version: A.1

A simple automated testing framework for projects written in C and C++.

There are two separate implementations of this testing framework: one for C and the other for C++.  This allows tests to be implemented in an idiomatic manner for either language.

It will also serve as a prototype for the automated testing framework of Iridium programming language.

CPPTEST is released under the MIT license.

> [!WARNING]
> CPPTEST is still in Alpha-testing; please use with care.  To report issues, use the "Issues" tab on this repository or send a message to mnpingleton@gmail.com.

Documentation and code examples are available in the /docs directory.

## Dependencies

| Dependency | Purpose |
| --- | --- |
| clang | Compiler |
| make | Automated build system |

## Getting Started

### 1. Clone this repository

```shell
$ git clone git@github.com:mpingleton/cpptest.git
```

### 2. Compile

```shell
$ make
```

### 3. Run the self-test

```shell
$ make test
```

### 4. Install

> [!IMPORTANT]
> Root privileges are necessary for installation.

```shell
# make install
```

### OR

```shell
$ sudo make install
```

### 5. Link to your project

In a C project, use the -lctest flag in your compiler:

```make
$ clang yourtestcode.c -lctest -o yourtestbinary
```

For C++, use the -lcpptest flag:

```make
$ clang++ yourtestcode.cpp -lcpptest -o yourtestbinary
```

## Contributions

This project is currently not accepting contributions.
