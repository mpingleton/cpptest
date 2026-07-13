.PHONY: uninstall install clean test build

CFLAGS = -Wall
CPPFLAGS = -Wall -std=c++23

build: binary/ccore.a binary/cppcore.a

init:
	mkdir -p binary
	mkdir -p objects
	mkdir -p objects/ccore
	mkdir -p objects/ctests
	mkdir -p objects/cppcore
	mkdir -p objects/cpptests

clean:
	rm -rf binary/*
	rm -rf objects/ccore/*
	rm -rf objects/ctests/*
	rm -rf objects/cppcore/*
	rm -rf objects/cpptests/*
	$(MAKE) -C tests clean

install: binary/ccore.a binary/cppcore.a test
	cp include/cpptest.h /usr/local/include
	cp include/cpptest.hpp /usr/local/include
	cp binary/ccore.a /usr/local/lib/libctest.a
	cp binary/cppcore.a /usr/local/lib/libcpptest.a

uninstall:
	rm /usr/local/include/cpptest.h
	rm /usr/local/include/cpptest.hpp
	rm /usr/local/lib/libctest.a
	rm /usr/local/lib/libcpptest.a


test: binary/ccore.a binary/cppcore.a
	$(MAKE) -C tests test

CCORE = objects/ccore/expectation_result.o objects/ccore/scenario.o objects/ccore/expectation.o objects/ccore/section.o objects/ccore/runner.o objects/ccore/progress.o

binary/ccore.a: $(CCORE)
	ar rc binary/ccore.a $(CCORE)

objects/ccore/expectation_result.o: source/ccore/expectation_result.c
	clang source/ccore/expectation_result.c -c $(CFLAGS) -o objects/ccore/expectation_result.o

objects/ccore/scenario.o: source/ccore/scenario.c
	clang source/ccore/scenario.c -c $(CFLAGS) -o objects/ccore/scenario.o

objects/ccore/expectation.o: source/ccore/expectation.c
	clang source/ccore/expectation.c -c $(CFLAGS) -o objects/ccore/expectation.o

objects/ccore/section.o: source/ccore/section.c
	clang source/ccore/section.c -c $(CFLAGS) -o objects/ccore/section.o

objects/ccore/runner.o: source/ccore/runner.c
	clang source/ccore/runner.c -c $(CFLAGS) -o objects/ccore/runner.o

objects/ccore/progress.o: source/ccore/progress.c
	clang source/ccore/progress.c -c $(CFLAGS) -o objects/ccore/progress.o

CPPCORE = objects/cppcore/expectation_result.o objects/cppcore/scenario.o objects/cppcore/expectation.o objects/cppcore/section.o objects/cppcore/runner.o objects/cppcore/progress.o

binary/cppcore.a: $(CPPCORE)
	ar rc binary/cppcore.a $(CPPCORE)

objects/cppcore/expectation_result.o: source/cppcore/expectation_result.cpp
	clang++ source/cppcore/expectation_result.cpp -c $(CPPFLAGS) -o objects/cppcore/expectation_result.o

objects/cppcore/scenario.o: source/cppcore/scenario.cpp
	clang++ source/cppcore/scenario.cpp -c $(CPPFLAGS) -o objects/cppcore/scenario.o

objects/cppcore/expectation.o: source/cppcore/expectation.cpp
	clang++ source/cppcore/expectation.cpp -c $(CPPFLAGS) -o objects/cppcore/expectation.o

objects/cppcore/section.o: source/cppcore/section.cpp
	clang++ source/cppcore/section.cpp -c $(CPPFLAGS) -o objects/cppcore/section.o

objects/cppcore/runner.o: source/cppcore/runner.cpp
	clang++ source/cppcore/runner.cpp -c $(CPPFLAGS) -o objects/cppcore/runner.o

objects/cppcore/progress.o: source/cppcore/progress.cpp
	clang++ source/cppcore/progress.cpp -c $(CPPFLAGS) -o objects/cppcore/progress.o
