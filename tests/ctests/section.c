//-----------------------------------------------------------------------------
// CPPTEST
//
// section.c
//
// Tests for sections.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../tests.h"

#include <stdlib.h>
#include <string.h>

void scenario1(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualFloat(pScenario, "2", 3.14f, 3.14f);
}

void scenario2(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualFloat(pScenario, "2", 3.14f, 3.0f);
}

void scenario3(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, "1", 10, 12);
	expectToEqualFloat(pScenario, "1", 3.14f, 3.14f);
}

void scenario4(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualFloat(pScenario, "1", 3.14f, 3.14f);
}

struct CTestSection* initSection1()
{
	struct CTestSection* pSection = initSection("Section One");
	addScenarioToSection(pSection, "Test 1", &scenario1);
	addScenarioToSection(pSection, "Test 2", &scenario2);

	return pSection;
}

struct CTestSection* initSection2()
{
	struct CTestSection* pSection = initSection("Section Two");
	addScenarioToSection(pSection, "Test 3", &scenario3);

	return pSection;
}

struct CTestSection* initSection3()
{
	struct CTestSection* pSection = initSection("Section Three");
	addScenarioToSection(pSection, "Test 4", &scenario4);

	return pSection;
}

int cTestSection()
{
	struct CTestSection* pSections[3];
	pSections[0] = initSection1();
	pSections[1] = initSection2();
	pSections[2] = initSection3();

	printSection(pSections[0], SHOW_EVERYTHING, 0);
	printSection(pSections[1], SHOW_EVERYTHING, 0);
	printSection(pSections[2], SHOW_EVERYTHING, 0);

	runSection(pSections[0], SHOW_EVERYTHING);
	runSection(pSections[1], SHOW_EVERYTHING);
	runSection(pSections[2], SHOW_EVERYTHING);

	printSection(pSections[0], SHOW_EVERYTHING, 0);
	printSection(pSections[1], SHOW_EVERYTHING, 0);
	printSection(pSections[2], SHOW_EVERYTHING, 0);

	if (didSectionPass(pSections[0]))
	{
		printf("Section one should not have passed\n");
		return 0;
	}
	else if (didSectionPass(pSections[1]))
	{
		printf("Section two should not have passed\n");
		return 0;
	}
	else if (!didSectionPass(pSections[2]))
	{
		printf("Section three should have passed\n");
		return 0;
	}

	freeSection(pSections[0]);
	freeSection(pSections[1]);
	freeSection(pSections[2]);
	free(pSections[0]);
	free(pSections[1]);
	free(pSections[2]);

	return 1;
}
