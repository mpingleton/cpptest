//-----------------------------------------------------------------------------
// CPPTEST
//
// ccore/section.c
//
// Functions for handling sections.
//
// Created	: 4 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"

#include <stdlib.h>
#include <string.h>

void initSection(struct CTestSection* pSection, const char* pDesc, int numberScenarios)
{
	size_t lenDesc = strlen(pDesc);
	if (lenDesc > 0)
	{
		pSection->pDesc = (char*)malloc(lenDesc);
		strcpy(pSection->pDesc, pDesc);
	}

	if (numberScenarios > 0)
	{
		pSection->numberScenarios = numberScenarios;
		pSection->pScenarios = (struct CTestScenario*)malloc(sizeof(struct CTestScenario) * numberScenarios);
		memset(pSection->pScenarios, 0, sizeof(struct CTestScenario) * numberScenarios);
	}
	else
	{
		pSection->numberScenarios = 0;
		pSection->pScenarios = 0;
	}
}

void freeSection(struct CTestSection* pSection)
{
	if (pSection->pDesc)
	{
		size_t lenDesc = strlen(pSection->pDesc);
		memset(pSection->pDesc, 0, lenDesc);
		free(pSection->pDesc);
	}

	if (pSection->pScenarios)
	{
		for (int i = 0; i < pSection->numberScenarios; i++)
			freeScenario(&pSection->pScenarios[i]);

		free(pSection->pScenarios);
	}

	memset(pSection, 0, sizeof(struct CTestSection));
}

void runSection(struct CTestSection* pSection, char show)
{
	if (show)
	{
		if (pSection->pDesc) printf("Section: %s\n", pSection->pDesc);
		else printf("Section: \n");
	}

	for (int i = 0; i < pSection->numberScenarios; i++)
	{
		if (show)
		{
			if (pSection->pDesc) printf("%s: ", pSection->pDesc);
			printScenario(&pSection->pScenarios[i]);
		}

		runScenario(&pSection->pScenarios[i], show);

		if (show)
		{
			if (pSection->pDesc) printf("%s: ", pSection->pDesc);
			printScenario(&pSection->pScenarios[i]);
		}
	}
}

char didSectionPass(struct CTestSection* pSection)
{
	int numberPass = 0, numberFail = 0;
	for (int i = 0; i < pSection->numberScenarios; i++)
	{
		if (didScenarioPass(&pSection->pScenarios[i]))
			numberPass++;
		else
			numberFail++;
	}

	if (numberPass > 0 && numberFail == 0)
		return EXPECTATION_PASS;

	return EXPECTATION_FAIL;
}

void printSection(struct CTestSection* pSection)
{
	if (pSection->numberScenarios == 0)
		printf("[      ]");
	else if (didSectionPass(pSection))
		printf("[  OK  ]");
	else
		printf("[ FAIL ]");

	if (pSection->pDesc) printf("\t%s\n", pSection->pDesc);
	else printf("\n");

	for (int i = 0; i < pSection->numberScenarios; i++) printScenario(&pSection->pScenarios[i]);

	for (int i = 0; i < 80; i++) printf("+");
	printf("\n");
}
