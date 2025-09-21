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

void initTests(struct CTestRunner* pRunner)
{
	pRunner->numberSections = 0;
	pRunner->pSection = 0;
}

void addSectionToTest(struct CTestRunner* pRunner, struct CTestSection* pSection)
{
	int i = pRunner->numberSections;
	pRunner->numberSections++;

	if (i == 0)
		pRunner->pSection = (struct CTestSection**)malloc(sizeof(struct CTestSection*));
	else
		pRunner->pSection = (struct CTestSection**)realloc(pRunner->pSection, sizeof(struct CTestSection*) * pRunner->numberSections);

	pRunner->pSection[i] = pSection;
}

void freeTests(struct CTestRunner* pRunner)
{
	if (pRunner->pSection)
	{
		for (int i = 0; i < pRunner->numberSections; i++)
		{
			freeSection(pRunner->pSection[i]);
			free(pRunner->pSection[i]);
		}

		memset(pRunner->pSection, 0, sizeof(struct CTestSection*) * pRunner->numberSections);
		free(pRunner->pSection);
	}

	memset(pRunner, 0, sizeof(struct CTestRunner));
}

void runTests(struct CTestRunner* pRunner, char show)
{
	if (pRunner->numberSections == 0) return;

	for (int i = 0; i < pRunner->numberSections; i++)
	{
		struct CTestSection* pS = pRunner->pSection[i];

		if (show > SHOW_NOTHING)
		{
			printf("\x1b[2K");

			char pc[101] = {};
			if (pS->pDesc)
				snprintf(pc, 100, "Running \"%s\"", pS->pDesc);
			else
				snprintf(pc, 100, "Running Section");
				
			printProgress(pc, i, pRunner->numberSections);
			printf("\n");
		}

		runSection(pS, show);

		if (show > SHOW_NOTHING) printf("\x1b[1F");
	}

	if (show > SHOW_NOTHING)
	{
		printf("\x1b[2K");

		int i = pRunner->numberSections;
		printProgress("All Sections Finished", i, i);
		
		printf("\n");
	}
}

char didTestsPass(struct CTestRunner* pRunner)
{
	int numberPass = 0, numberFail = 0;
	for (int i = 0; i < pRunner->numberSections; i++)
	{
		if (didSectionPass(pRunner->pSection[i]))
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
		printSection(pRunner->pSection[i], show);
}
