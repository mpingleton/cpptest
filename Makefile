.PHONY: uninstall install clean test build

CFLAGS = -Wall
CPPFLAGS = -Wall -std=c++23

build: libraries/libctest.a libraries/libcpptest.a

clean:
	rm -rf libraries
	rm -rf source/ccore/*.o
	rm -rf source/cppcore/*.o
	$(MAKE) -C tests clean

install: libraries/libctest.a libraries/libcpptest.a init
	cp include/cpptest.h /usr/local/include
	cp include/cpptest.hpp /usr/local/include
	cp libraries/libctest.a /usr/local/lib
	cp libraries/libcpptest.a /usr/local/lib

uninstall:
	rm -f /usr/local/include/cpptest.h
	rm -f /usr/local/include/cpptest.hpp
	rm -f /usr/local/lib/libctest.a
	rm -f /usr/local/lib/libcpptest.a

test: libraries/libctest.a libraries/libcpptest.a
	$(MAKE) -C tests test

CCORE = source/ccore/expectation_result.o source/ccore/scenario.o source/ccore/expectation.o source/ccore/section.o source/ccore/runner.o source/ccore/progress.o

libraries/libctest.a: $(CCORE) init
	ar rc libraries/libctest.a $(CCORE)

source/ccore/expectation_result.o: source/ccore/expectation_result.c
	clang source/ccore/expectation_result.c -c $(CFLAGS) -o source/ccore/expectation_result.o

source/ccore/scenario.o: source/ccore/scenario.c
	clang source/ccore/scenario.c -c $(CFLAGS) -o source/ccore/scenario.o

source/ccore/expectation.o: source/ccore/expectation.c
	clang source/ccore/expectation.c -c $(CFLAGS) -o source/ccore/expectation.o

source/ccore/section.o: source/ccore/section.c
	clang source/ccore/section.c -c $(CFLAGS) -o source/ccore/section.o

source/ccore/runner.o: source/ccore/runner.c
	clang source/ccore/runner.c -c $(CFLAGS) -o source/ccore/runner.o

source/ccore/progress.o: source/ccore/progress.c
	clang source/ccore/progress.c -c $(CFLAGS) -o source/ccore/progress.o

CPPCORE = source/cppcore/expectation_result.o source/cppcore/scenario.o source/cppcore/expectation.o source/cppcore/section.o source/cppcore/runner.o source/cppcore/progress.o

libraries/libcpptest.a: $(CPPCORE) init
	ar rc libraries/libcpptest.a $(CPPCORE)

source/cppcore/expectation_result.o: source/cppcore/expectation_result.cpp
	clang++ source/cppcore/expectation_result.cpp -c $(CPPFLAGS) -o source/cppcore/expectation_result.o

source/cppcore/scenario.o: source/cppcore/scenario.cpp
	clang++ source/cppcore/scenario.cpp -c $(CPPFLAGS) -o source/cppcore/scenario.o

source/cppcore/expectation.o: source/cppcore/expectation.cpp
	clang++ source/cppcore/expectation.cpp -c $(CPPFLAGS) -o source/cppcore/expectation.o

source/cppcore/section.o: source/cppcore/section.cpp
	clang++ source/cppcore/section.cpp -c $(CPPFLAGS) -o source/cppcore/section.o

source/cppcore/runner.o: source/cppcore/runner.cpp
	clang++ source/cppcore/runner.cpp -c $(CPPFLAGS) -o source/cppcore/runner.o

source/cppcore/progress.o: source/cppcore/progress.cpp
	clang++ source/cppcore/progress.cpp -c $(CPPFLAGS) -o source/cppcore/progress.o

init:
	mkdir -p libraries
