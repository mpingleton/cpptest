//-----------------------------------------------------------------------------
// CPPTEST
//
// main.cpp
//
// Entry point for performing basic tests on the C++ framework.
//
// Created	: 31 March 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../include/cpptest.hpp"
#include "../include/tests.hpp"

#include <iostream>

using namespace std;

void printSep()
{
	for (int i = 0; i < 80; i++) cout << "#";
	cout << endl;
}

int main(int argc, char** argv)
{
	cout << "1. Expectation Results: ";
	printSep();
	if (!cppTestExpectationResult())
	{
		cout << "Test Section Failed: Expectation Result" << endl;
		return -1;
	}

	cout << "2. Scenarios: ";
	printSep();
	if (!cppTestScenario())
	{
		cout << "Test Section Failed: Scenario" << endl;
		return -2;
	}

	cout << "3. Sections: ";
	printSep();
	if (!cppTestSection())
	{
		cout << "Test Section Failed: Section" << endl;
		return -3;
	}

	printSep();
	printSep();
	cout << "All tests passed." << endl;
	return 0;
}