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

int main(int argc, char** argv)
{
	if (!cppTestExpectationResult())
	{
		cout << "Test Section Failed: Expectation Result" << endl;
		return -1;
	}

	if (!cppTestScenario())
	{
		cout << "Test Section Failed: Scenario" << endl;
		return -2;
	}

	if (!cppTestSection())
	{
		cout << "Test Section Failed: Section" << endl;
		return -3;
	}

	cout << "All tests passed." << endl;
	return 0;
}