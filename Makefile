all: binary/ctests binary/cpptests binary/ccore.a binary/cppcore.a

test: binary/ctests binary/cpptests
	binary/ctests
	binary/cpptests

binary/ctests: source/main.c binary/ctests.a binary/ccore.a
	clang source/main.c binary/ctests.a binary/ccore.a -o binary/ctests

binary/cpptests: source/main.cpp binary/cpptests.a binary/cppcore.a
	clang++ source/main.cpp binary/cpptests.a binary/cppcore.a -o binary/cpptests

init:
	mkdir binary
	mkdir objects
	mkdir objects/ccore
	mkdir objects/ctests
	mkdir objects/cppcore
	mkdir objects/cpptests

clean:
	rm -rf binary/*
	rm -rf objects/ccore/*
	rm -rf objects/ctests/*
	rm -rf objects/cppcore/*
	rm -rf objects/cpptests/*

install: binary/ccore.a binary/cppcore.a
	cp include/cpptest.h /usr/local/include
	cp include/cpptest.hpp /usr/local/include
	cp binary/ccore.a /usr/local/lib/libctest.a
	cp binary/cppcore.a /usr/local/lib/libcpptest.a

uninstall:
	rm /usr/local/include/cpptest.h
	rm /usr/local/include/cpptest.hpp
	rm /usr/local/lib/libctest.a
	rm /usr/local/lib/libcpptest.a

binary/ccore.a: objects/ccore/expectation_result.o objects/ccore/scenario.o objects/ccore/expectation.o objects/ccore/section.o objects/ccore/runner.o
	ar rc binary/ccore.a objects/ccore/expectation_result.o objects/ccore/scenario.o objects/ccore/expectation.o objects/ccore/section.o objects/ccore/runner.o

objects/ccore/expectation_result.o: source/ccore/expectation_result.c
	clang source/ccore/expectation_result.c -c -Wall -o objects/ccore/expectation_result.o

objects/ccore/scenario.o: source/ccore/scenario.c
	clang source/ccore/scenario.c -c -Wall -o objects/ccore/scenario.o

objects/ccore/expectation.o: source/ccore/expectation.c
	clang source/ccore/expectation.c -c -Wall -o objects/ccore/expectation.o

objects/ccore/section.o: source/ccore/section.c
	clang source/ccore/section.c -c -Wall -o objects/ccore/section.o

objects/ccore/runner.o: source/ccore/runner.c
	clang source/ccore/runner.c -c -Wall -o objects/ccore/runner.o

binary/cppcore.a: objects/cppcore/expectation_result.o objects/cppcore/scenario.o objects/cppcore/expectation.o objects/cppcore/section.o objects/cppcore/runner.o
	ar rc binary/cppcore.a objects/cppcore/expectation_result.o objects/cppcore/scenario.o objects/cppcore/expectation.o objects/cppcore/section.o objects/cppcore/runner.o

objects/cppcore/expectation_result.o: source/cppcore/expectation_result.cpp
	clang++ source/cppcore/expectation_result.cpp -c -Wall -o objects/cppcore/expectation_result.o

objects/cppcore/scenario.o: source/cppcore/scenario.cpp
	clang++ source/cppcore/scenario.cpp -c -Wall -o objects/cppcore/scenario.o

objects/cppcore/expectation.o: source/cppcore/expectation.cpp
	clang++ source/cppcore/expectation.cpp -c -Wall -o objects/cppcore/expectation.o

objects/cppcore/section.o: source/cppcore/section.cpp
	clang++ source/cppcore/section.cpp -c -Wall -o objects/cppcore/section.o

objects/cppcore/runner.o: source/cppcore/runner.cpp
	clang++ source/cppcore/runner.cpp -c -Wall -o objects/cppcore/runner.o

binary/ctests.a: objects/ctests/expectation_result.o objects/ctests/scenario.o objects/ctests/section.o objects/ctests/runner.o
	ar rc binary/ctests.a objects/ctests/expectation_result.o objects/ctests/scenario.o objects/ctests/section.o objects/ctests/runner.o

objects/ctests/expectation_result.o: source/tests/expectation_result.c
	clang source/tests/expectation_result.c -c -Wall -o objects/ctests/expectation_result.o

objects/ctests/scenario.o: source/tests/scenario.c
	clang source/tests/scenario.c -c -Wall -o objects/ctests/scenario.o

objects/ctests/section.o: source/tests/section.c
	clang source/tests/section.c -c -Wall -o objects/ctests/section.o

objects/ctests/runner.o: source/tests/runner.c
	clang source/tests/runner.c -c -Wall -o objects/ctests/runner.o

binary/cpptests.a: objects/cpptests/expectation_result.o objects/cpptests/scenario.o objects/cpptests/section.o objects/cpptests/runner.o
	ar rc binary/cpptests.a objects/cpptests/expectation_result.o objects/cpptests/scenario.o objects/cpptests/section.o objects/cpptests/runner.o

objects/cpptests/expectation_result.o: source/tests/expectation_result.cpp
	clang++ source/tests/expectation_result.cpp -c -Wall -o objects/cpptests/expectation_result.o

objects/cpptests/scenario.o: source/tests/scenario.cpp
	clang++ source/tests/scenario.cpp -c -Wall -o objects/cpptests/scenario.o

objects/cpptests/section.o: source/tests/section.cpp
	clang++ source/tests/section.cpp -c -Wall -o objects/cpptests/section.o

objects/cpptests/runner.o: source/tests/runner.cpp
	clang++ source/tests/runner.cpp -c -Wall -o objects/cpptests/runner.o
