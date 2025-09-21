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
		char prog[101] = {};
		if (show > SHOW_NOTHING)
		{
			printf("\x1b[2K");
			int pn = i * 100 / pSection->numberScenarios;

			char progStr[100] = {};
			sprintf(progStr, "<Running Scenario \x1b[1m%i/%i\x1b[0m>", i + 1, pSection->numberScenarios);

			size_t progLen = strlen(progStr);
			if (progLen > 0)
			{
				int progStrS = 50 - progLen / 2;
				for (int pi = 0; pi < progLen; pi++)
					prog[progStrS + pi] = progStr[pi];
			}
			
			for (int pi = 0; pi < 100; pi++)
			{
				if (prog[pi] == 0)
				{
					if ((pi < 90 && i == pSection->numberScenarios - 1) || pi < pn)
						prog[pi] = '=';
					else
						prog[pi] = ' ';
				}
				else if (prog[pi] == ' ')
				{
					if ((pi < 90 && i == pSection->numberScenarios - 1) || pi < pn)
						prog[pi] = '-';
				}
			}

			printf("[%s]\n\x1b[2K", prog);
		}

		runScenario(&pSection->pScenarios[i], show);
		
		if (show > SHOW_NOTHING) printf("\x1b[1F");
	}

	for (int i = 0; i < pSection->numberSubsections; i++)
		runSection(pSection->pSubsections[i], show);
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

void printSection(struct CTestSection* pSection, char show)
{
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

	for (int i = 0; i < pSection->numberScenarios; i++)
	{
		if (i == pSection->numberScenarios - 1)
		{
			printf(" \x1b[30m\\-\x1b[0m ");
			printScenario(&pSection->pScenarios[i], show, "    ");
		}
		else
		{
			printf(" \x1b[30m|-\x1b[0m ");
			printScenario(&pSection->pScenarios[i], show, " \x1b[30m| \x1b[0m ");
		}
	}

	for (int i = 0; i < pSection->numberSubsections; i++)
		printSection(pSection->pSubsections[i], show);

	putchar('\n');
}
