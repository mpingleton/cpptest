//-----------------------------------------------------------------------------
// CPPTEST
//
// main.c
//
// Entry point for performing basic tests on the C framework.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../include/cpptest.h"
#include "../include/tests.h"

#include <stdio.h>

void printSep()
{
	for (int i = 0; i < 80; i++) printf("#");
	printf("\n");
}

int main(int argc, char** argv)
{
	printf("1. Expectation Results: ");
	printSep();
	if (!cTestExpectationResult())
	{
		printf("Test Section Failed: Expectation Result\n");
		return -1;
	}

	printf("2. Scenarios: ");
	printSep();
	if (!cTestScenario())
	{
		printf("Test Section Failed: Scenario\n");
		return -2;
	}

	printf("3. Sections: ");
	printSep();
	if (!cTestSection())
	{
		printf("Test Section Failed: Section\n");
		return -3;
	}

	printf("4. Runners: ");
	printSep();
	if (!cTestRunner())
	{
		printf("Test Section Failed: Runner\n");
		return -4;
	}

	printSep();
	printSep();
	printf("All tests passed.\n");
	return 0;
}
