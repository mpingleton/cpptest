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

struct CTestSection* initSection(const char* pDesc)
{
	struct CTestSection* pNew = (struct CTestSection*)malloc(sizeof(struct CTestSection));
	if (pNew == 0) return 0;

	memset(pNew, 0, sizeof(struct CTestSection));

	if (pDesc)
	{
		size_t l = strlen(pDesc);
		pNew->pDesc = (char*)malloc(l + 1);
		strcpy(pNew->pDesc, pDesc);
	}

	return pNew;
}

void addScenarioToSection(struct CTestSection* pSection, const char* pDesc, void (*pFunc)(struct CTestScenario* pScenario))
{
	int i = pSection->numberScenarios;
	pSection->numberScenarios++;

	if (i == 0)
	{
		pSection->pScenarios = (struct CTestScenario*)malloc(sizeof(struct CTestScenario));
		initScenario(pSection->pScenarios, pDesc, pFunc);
	}
	else
	{
		pSection->pScenarios = (struct CTestScenario*)realloc(pSection->pScenarios, sizeof(struct CTestScenario) * pSection->numberScenarios);
		initScenario(&pSection->pScenarios[i], pDesc, pFunc);
	}
}

void addScenarioToSectionByParams(struct CTestSection* pSection, const char* pDesc, struct CTestScenarioInitParams* pParams)
{
	int i = pSection->numberScenarios;
	pSection->numberScenarios++;

	if (i == 0)
	{
		pSection->pScenarios = (struct CTestScenario*)malloc(sizeof(struct CTestScenario));
		initScenario(pSection->pScenarios, pDesc, pParams->pFuncTest);
	}
	else
	{
		pSection->pScenarios = (struct CTestScenario*)realloc(pSection->pScenarios, sizeof(struct CTestScenario) * pSection->numberScenarios);
		initScenario(&pSection->pScenarios[i], pDesc, pParams->pFuncTest);
	}

	pSection->pScenarios[i].pState = pParams->pState;
	pSection->pScenarios[i].pFuncSetupOnce = pParams->pFuncSetupOnce;
	pSection->pScenarios[i].pFuncSetupEach = pParams->pFuncSetupEach;
	pSection->pScenarios[i].pFuncTeardownOnce = pParams->pFuncTeardownOnce;
	pSection->pScenarios[i].pFuncTeardownEach = pParams->pFuncTeardownEach;
	pSection->pScenarios[i].pFuncShouldRepeat = pParams->pFuncShouldRepeat;
}

void addSubsectionToSection(struct CTestSection* pSection, struct CTestSection* pSubsection)
{
	int i = pSection->numberSubsections;
	pSection->numberSubsections++;

	if (i == 0)
		pSection->pSubsections = (struct CTestSection**)malloc(sizeof(struct CTestSection*));
	else
		pSection->pSubsections = (struct CTestSection**)realloc(pSection->pSubsections, sizeof(struct CTestSection*) * pSection->numberSubsections);

	pSection->pSubsections[i] = pSubsection;
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

	if (pSection->pSubsections)
	{
		for (int i = 0; i < pSection->numberSubsections; i++)
		{
			freeSection(pSection->pSubsections[i]);
			free(pSection->pSubsections[i]);
		}

		memset(pSection->pSubsections, 0, sizeof(struct CTestSection*) * pSection->numberSubsections);
		free(pSection->pSubsections);
	}

	memset(pSection, 0, sizeof(struct CTestSection));
}

void runSection(struct CTestSection* pSection, char show)
{
	for (int i = 0; i < pSection->numberScenarios; i++)
	{
		if (show > SHOW_NOTHING)
		{
			printf("\x1b[2K");
			printProgress("\x1b[34m\x1b[1mRunning Scenario\x1b[0m", i + 1, pSection->numberScenarios);

			printf("\n\x1b[2K");
		}

		runScenario(&pSection->pScenarios[i], show);
		
		if (show > SHOW_NOTHING) printf("\x1b[2K\x1b[1F\x1b[2K");
	}

	for (int i = 0; i < pSection->numberSubsections; i++)
		runSection(pSection->pSubsections[i], show);

	fflush(0);
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

	for (int i = 0; i < pSection->numberSubsections; i++)
	{
		if (didSectionPass(pSection->pSubsections[i]))
			numberPass++;
		else
			numberFail++;
	}

	if (numberPass > 0 && numberFail == 0)
		return EXPECTATION_PASS;

	return EXPECTATION_FAIL;
}

void printSection(struct CTestSection* pSection, char show, char* pStartLine)
{
	if (pStartLine) printf("%s", pStartLine);

	if (pSection->numberScenarios == 0 && pSection->numberSubsections == 0)
		printf("[      ]");
	else if (didSectionPass(pSection))
		printf("[  \x1b[32m\x1b[1mOK\x1b[0m  ]");
	else
		printf("[ \x1b[91m\x1b[1mFAIL\x1b[0m ]");

	if (pSection->pDesc)
		printf(" %s\n", pSection->pDesc);
	else
		printf("\n");

	const char* pSubStartLineA = "    ";
	const char* pSubStartLineB = " \x1b[30m| \x1b[0m ";
	const char* pSubStartLineC = " \x1b[30m\\ \x1b[0m ";
	size_t lenSubStartLineA = strlen(pSubStartLineA);
	size_t lenSubStartLineB = strlen(pSubStartLineB);
	size_t lenSubStartLineC = strlen(pSubStartLineC);

	char* pStartLineA = 0;
	char* pStartLineB = 0;
	char* pStartLineC = 0;
	if (pStartLine)
	{
		size_t lenStartLine = strlen(pStartLine);

		pStartLineA = (char*)malloc(lenStartLine + lenSubStartLineA + 1);
		pStartLineB = (char*)malloc(lenStartLine + lenSubStartLineB + 1);
		pStartLineC = (char*)malloc(lenStartLine + lenSubStartLineC + 1);
		memset(pStartLineA, 0, lenStartLine + lenSubStartLineA + 1);
		memset(pStartLineB, 0, lenStartLine + lenSubStartLineB + 1);
		memset(pStartLineC, 0, lenStartLine + lenSubStartLineC + 1);

		strcpy(pStartLineA, pStartLine);
		strcpy(&pStartLineA[lenStartLine], pSubStartLineA);

		strcpy(pStartLineB, pStartLine);
		strcpy(&pStartLineB[lenStartLine], pSubStartLineB);
		
		strcpy(pStartLineC, pStartLine);
		strcpy(&pStartLineC[lenStartLine], pSubStartLineC);
	}
	else
	{
		pStartLineA = (char*)malloc(lenSubStartLineA + 1);
		pStartLineB = (char*)malloc(lenSubStartLineB + 1);
		pStartLineC = (char*)malloc(lenSubStartLineC + 1);
		memset(pStartLineA, 0, lenSubStartLineA + 1);
		memset(pStartLineB, 0, lenSubStartLineB + 1);
		memset(pStartLineC, 0, lenSubStartLineC + 1);
		
		strcpy(pStartLineA, pSubStartLineA);
		strcpy(pStartLineB, pSubStartLineB);
		strcpy(pStartLineC, pSubStartLineC);
	}

	for (int i = 0; i < pSection->numberScenarios; i++)
	{
		if (pStartLine) printf("%s", pStartLine);

		if (i == pSection->numberScenarios - 1)
		{
			printf(" \x1b[30m\\-\x1b[0m ");
			printScenario(&pSection->pScenarios[i], show, pStartLineA);
		}
		else
		{
			printf(" \x1b[30m|-\x1b[0m ");
			printScenario(&pSection->pScenarios[i], show, pStartLineB);
		}
	}

	if (pSection->numberSubsections == 0 && pStartLine == 0)
	{
		printf("%s\n", pStartLineA);
	}

	for (int i = 0; i < pSection->numberSubsections; i++)
	{
		printSection(pSection->pSubsections[i], show, pStartLineB);

		if (i == pSection->numberSubsections - 1)
			printf("%s\n\n", pStartLineC);
		else
			printf("%s\n", pStartLineB);
	}

	free(pStartLineA);
	free(pStartLineB);
	free(pStartLineC);
}
