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

binary/ccore.a: objects/ccore/expectation_result.o
	ar rc binary/ccore.a objects/ccore/expectation_result.o

objects/ccore/expectation_result.o: source/ccore/expectation_result.c
	clang source/ccore/expectation_result.c -c -Wall -o objects/ccore/expectation_result.o

binary/cppcore.a: objects/cppcore/expectation_result.o
	ar rc binary/cppcore.a objects/cppcore/expectation_result.o

objects/cppcore/expectation_result.o: source/cppcore/expectation_result.cpp
	clang++ source/cppcore/expectation_result.cpp -c -Wall -o objects/cppcore/expectation_result.o

binary/ctests.a: objects/ctests/expectation_result.o
	ar rc binary/ctests.a objects/ctests/expectation_result.o

objects/ctests/expectation_result.o: source/tests/expectation_result.c
	clang source/tests/expectation_result.c -c -Wall -o objects/ctests/expectation_result.o

binary/cpptests.a: objects/cpptests/expectation_result.o
	ar rc binary/cpptests.a objects/cpptests/expectation_result.o

objects/cpptests/expectation_result.o: source/tests/expectation_result.cpp
	clang++ source/tests/expectation_result.cpp -c -Wall -o objects/cpptests/expectation_result.o