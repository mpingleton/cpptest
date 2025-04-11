//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/runner.c
//
// Tests for runners.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../../include/tests.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void someScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualInt(pScenario, "1", 3, 2);
	expectToEqualFloat(pScenario, "2", 3.14f, 3.14f);

	if (isScenarioCanceled(pScenario)) return;

	expectToEqualDouble(pScenario, "3", 1.2, 1.2);
}

void anotherScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualInt(pScenario, "1", 2, 2);
	expectToEqualFloat(pScenario, "2", 3.14f, 3.14f);

	if (isScenarioCanceled(pScenario)) return;

	expectToEqualDouble(pScenario, "3", 1.2, 1.2);

	int a = 0;
	int* b = 0;
	int* c = &a;
	expectPointerNull(pScenario, "4", b);
	expectPointerInitialized(pScenario, "5", c);
	expectToEqualPointer(pScenario, "6", c, &a);
}

void someotherScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualInt(pScenario, "1", 1, 1);
	expectToEqualInt(pScenario, "2", 2, 2);
}

void yetotherScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualFloat(pScenario, "1", 3.14f, 3.14f);
	expectToEqualDouble(pScenario, "2", 1.4, 1.4);
}

void initSectionOne(struct CTestSection* pSection)
{
	initSection(pSection, "Section One", 1);
	initScenario(&pSection->pScenarios[0], "Test 1", &someScenario1);
}

void initSectionTwo(struct CTestSection* pSection)
{
	initSection(pSection, "Section Two", 1);
	initScenario(&pSection->pScenarios[0], "Test 2", &anotherScenario1);
}

void initSectionThr(struct CTestSection* pSection)
{
	initSection(pSection, "Section Three", 2);
	initScenario(&pSection->pScenarios[0], "Test 3", &someotherScenario1);
	initScenario(&pSection->pScenarios[1], "Test 4", &yetotherScenario1);
}

int cTestRunner()
{
	struct CTestRunner runner1 = {};
	initTests(&runner1, 2);
	initSectionOne(&runner1.pSection[0]);
	initSectionTwo(&runner1.pSection[1]);

	runTests(&runner1, SHOW_EVERYTHING);
	if (didTestsPass(&runner1))
	{
		printf("Tests should not have passed\n");
		return 0;
	}

	struct CTestRunner runner2 = {};
	initTests(&runner2, 1);
	initSectionThr(&runner2.pSection[0]);

	runTests(&runner2, SHOW_EVERYTHING);
	if (!didTestsPass(&runner2))
	{
		printf("Tests should have passed\n");
		return 0;
	}

	printTests(&runner1, SHOW_EVERYTHING);
	printTests(&runner2, SHOW_EVERYTHING);

	freeTests(&runner1);
	freeTests(&runner2);
	return 1;
}
