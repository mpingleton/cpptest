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

int main(int argc, char** argv)
{
	if (!cTestExpectationResult())
	{
		printf("Test Section Failed: Expectation Result\n");
		return -1;
	}

	if (!cTestScenario())
	{
		printf("Test Section Failed: Scenario\n");
		return -2;
	}

	printf("All tests passed.\n");
	return 0;
}