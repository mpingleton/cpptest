binary/tests: source/main.cpp
	clang++ source/main.cpp -o binary/tests

init:
	mkdir binary
	mkdir objects

clean:
	rm -rf binary/*
	rm -rf objects/*
