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

binary/ccore.a: objects/ccore/expectation_result.o objects/ccore/scenario.o objects/ccore/expectation.o
	ar rc binary/ccore.a objects/ccore/expectation_result.o objects/ccore/scenario.o objects/ccore/expectation.o

objects/ccore/expectation_result.o: source/ccore/expectation_result.c
	clang source/ccore/expectation_result.c -c -Wall -o objects/ccore/expectation_result.o

objects/ccore/scenario.o: source/ccore/scenario.c
	clang source/ccore/scenario.c -c -Wall -o objects/ccore/scenario.o

objects/ccore/expectation.o: source/ccore/expectation.c
	clang source/ccore/expectation.c -c -Wall -o objects/ccore/expectation.o

binary/cppcore.a: objects/cppcore/expectation_result.o objects/cppcore/scenario.o objects/cppcore/expectation.o
	ar rc binary/cppcore.a objects/cppcore/expectation_result.o objects/cppcore/scenario.o objects/cppcore/expectation.o

objects/cppcore/expectation_result.o: source/cppcore/expectation_result.cpp
	clang++ source/cppcore/expectation_result.cpp -c -Wall -o objects/cppcore/expectation_result.o

objects/cppcore/scenario.o: source/cppcore/scenario.cpp
	clang++ source/cppcore/scenario.cpp -c -Wall -o objects/cppcore/scenario.o

objects/cppcore/expectation.o: source/cppcore/expectation.cpp
	clang++ source/cppcore/expectation.cpp -c -Wall -o objects/cppcore/expectation.o

binary/ctests.a: objects/ctests/expectation_result.o objects/ctests/scenario.o
	ar rc binary/ctests.a objects/ctests/expectation_result.o objects/ctests/scenario.o

objects/ctests/expectation_result.o: source/tests/expectation_result.c
	clang source/tests/expectation_result.c -c -Wall -o objects/ctests/expectation_result.o

objects/ctests/scenario.o: source/tests/scenario.c
	clang source/tests/scenario.c -c -Wall -o objects/ctests/scenario.o

binary/cpptests.a: objects/cpptests/expectation_result.o objects/cpptests/scenario.o
	ar rc binary/cpptests.a objects/cpptests/expectation_result.o objects/cpptests/scenario.o

objects/cpptests/expectation_result.o: source/tests/expectation_result.cpp
	clang++ source/tests/expectation_result.cpp -c -Wall -o objects/cpptests/expectation_result.o

objects/cpptests/scenario.o: source/tests/scenario.cpp
	clang++ source/tests/scenario.cpp -c -Wall -o objects/cpptests/scenario.o
