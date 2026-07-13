.PHONY: init clean test build

CFLAGS = -Wall
CPPFLAGS = -Wall -std=c++23

TEST_SUBJECT_C = ../libraries/libctest.a
TEST_SUBJECT_CPP = ../libraries/libcpptest.a

build: binary/ctests binary/cpptests

test: binary/ctests binary/cpptests
	binary/ctests
	binary/cpptests

clean:
	rm -f ctests/*.o
	rm -f cpptests/*.o
	rm -rf binary

CTESTS = ctests/scenario.o ctests/section.o ctests/expectation_result.o ctests/runner.o

binary/ctests: init main.c $(CTESTS) $(TEST_SUBJECT_C)
	clang main.c $(CTESTS) $(TEST_SUBJECT_C) -o binary/ctests

ctests/scenario.o: ctests/scenario.c
	clang ctests/scenario.c -c $(CFLAGS) -o ctests/scenario.o

ctests/section.o: ctests/section.c
	clang ctests/section.c -c $(CFLAGS) -o ctests/section.o

ctests/expectation_result.o: ctests/expectation_result.c
	clang ctests/expectation_result.c -c $(CFLAGS) -o ctests/expectation_result.o

ctests/runner.o: ctests/runner.c
	clang ctests/runner.c -c $(CFLAGS) -o ctests/runner.o

CPPTESTS = cpptests/scenario.o cpptests/section.o cpptests/expectation_result.o cpptests/runner.o

binary/cpptests: init main.cpp $(CPPTESTS) $(TEST_SUBJECT_CPP)
	clang++ main.cpp $(CPPTESTS) $(TEST_SUBJECT_CPP) -o binary/cpptests

cpptests/scenario.o: cpptests/scenario.cpp
	clang++ cpptests/scenario.cpp -c $(CPPFLAGS) -o cpptests/scenario.o

cpptests/section.o: cpptests/section.cpp
	clang++ cpptests/section.cpp -c $(CPPFLAGS) -o cpptests/section.o

cpptests/expectation_result.o: cpptests/expectation_result.cpp
	clang++ cpptests/expectation_result.cpp -c $(CPPFLAGS) -o cpptests/expectation_result.o

cpptests/runner.o: cpptests/runner.cpp
	clang++ cpptests/runner.cpp -c $(CPPFLAGS) -o cpptests/runner.o

init: $(TEST_SUBJECT_C) $(TEST_SUBJECT_CPP)
	mkdir -p binary
