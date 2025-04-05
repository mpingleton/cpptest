//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/section.c
//
// Tests for sections.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../../include/tests.h"

#include <stdlib.h>
#include <string.h>

void scenario1(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, 1, 10, 10);
	expectToEqualFloat(pScenario, 2, 3.14f, 3.14f);
}

void scenario2(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, 1, 10, 10);
	expectToEqualFloat(pScenario, 2, 3.14f, 3.0f);
}

void scenario3(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, 1, 10, 12);
	expectToEqualFloat(pScenario, 1, 3.14f, 3.14f);
}

void scenario4(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, 1, 10, 10);
	expectToEqualFloat(pScenario, 1, 3.14f, 3.14f);
}

void initSection1(struct CTestSection* pSection)
{
	initSection(pSection, "Section One", 2);
	initScenario(&pSection->pScenarios[0], "Test 1", &scenario1);
	initScenario(&pSection->pScenarios[1], "Test 2", &scenario2);
}

void initSection2(struct CTestSection* pSection)
{
	initSection(pSection, "Section Two", 1);
	initScenario(&pSection->pScenarios[0], "Test 3", &scenario3);
}

void initSection3(struct CTestSection* pSection)
{
	initSection(pSection, "Section Three", 1);
	initScenario(&pSection->pScenarios[0], "Test 4", &scenario4);
}

int cTestSection()
{
	struct CTestSection* pSections = (struct CTestSection*)malloc(sizeof(struct CTestSection) * 3);
	memset(pSections, 0, sizeof(struct CTestSection) * 3);

	initSection1(&pSections[0]);
	initSection2(&pSections[1]);
	initSection3(&pSections[2]);

	printSection(&pSections[0]);
	printSection(&pSections[1]);
	printSection(&pSections[2]);

	runSection(&pSections[0], 1);
	runSection(&pSections[1], 1);
	runSection(&pSections[2], 1);

	printSection(&pSections[0]);
	printSection(&pSections[1]);
	printSection(&pSections[2]);

	if (didSectionPass(&pSections[0]))
	{
		printf("Section one should not have passed\n");
		return 0;
	}
	else if (didSectionPass(&pSections[1]))
	{
		printf("Section two should not have passed\n");
		return 0;
	}
	else if (!didSectionPass(&pSections[2]))
	{
		printf("Section three should have passed\n");
		return 0;
	}

	freeSection(&pSections[0]);
	freeSection(&pSections[1]);
	freeSection(&pSections[2]);

	memset(pSections, 0, sizeof(struct CTestSection) * 3);
	free(pSections);
	return 1;
}
