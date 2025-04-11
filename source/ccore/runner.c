//-----------------------------------------------------------------------------
// CPPTEST
//
// ccore/runner.c
//
// Functions which test runners.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"

#include <stdlib.h>
#include <string.h>

void initTests(struct CTestRunner* pRunner, int numberSections)
{
	if (numberSections > 0)
	{
		pRunner->numberSections = numberSections;
		pRunner->pSection = (struct CTestSection*)malloc(sizeof(struct CTestSection) * numberSections);
		memset(pRunner->pSection, 0, sizeof(struct CTestSection) * numberSections);
	}
	else
	{
		pRunner->numberSections = 0;
		pRunner->pSection = 0;
	}
}

void freeTests(struct CTestRunner* pRunner)
{
	if (pRunner->pSection)
	{
		for (int i = 0; i < pRunner->numberSections; i++)
			freeSection(&pRunner->pSection[i]);

		free(pRunner->pSection);
	}

	memset(pRunner, 0, sizeof(struct CTestRunner));
}

void runTests(struct CTestRunner* pRunner, char show)
{
	for (int i = 0; i < pRunner->numberSections; i++)
		runSection(&pRunner->pSection[i], show);
}

char didTestsPass(struct CTestRunner* pRunner)
{
	int numberPass = 0, numberFail = 0;
	for (int i = 0; i < pRunner->numberSections; i++)
	{
		if (didSectionPass(&pRunner->pSection[i]))
			numberPass++;
		else
			numberFail++;
	}

	if (numberPass > 0 && numberFail == 0)
		return EXPECTATION_PASS;

	return EXPECTATION_FAIL;
}

void printTests(struct CTestRunner* pRunner, char show)
{
	if (show == SHOW_NOTHING) return;
	for (int i = 0; i < pRunner->numberSections; i++)
		printSection(&pRunner->pSection[i], show);
}
