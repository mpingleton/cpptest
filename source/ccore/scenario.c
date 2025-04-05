//-----------------------------------------------------------------------------
// CPPTEST
//
// ccore/scenario.c
//
// Functions for handling scenarios.
//
// Created	: 3 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"

#include <stdlib.h>
#include <string.h>

void initScenario(struct CTestScenario* pScenario, const char* pDesc, void (*pFunc)(struct CTestScenario* pScenario))
{
	pScenario->status = SCENARIO_STATUS_PENDING;

	size_t lenDesc = strlen(pDesc);
	if (lenDesc > 0)
	{
		pScenario->pDesc = (char*)malloc(lenDesc);
		strcpy(pScenario->pDesc, pDesc);
	}

	pScenario->pResults = 0;
	pScenario->pFunc = pFunc;
}

void freeScenario(struct CTestScenario* pScenario)
{
	if (pScenario->pDesc)
	{
		size_t lenDesc = strlen(pScenario->pDesc);
		memset(pScenario->pDesc, 0, lenDesc);
		free(pScenario->pDesc);
	}

	if (pScenario->pResults) freeExpectationResult(pScenario->pResults);

	memset(pScenario, 0, sizeof(struct CTestScenario));
}

void runScenario(struct CTestScenario* pScenario, char show)
{
	if (pScenario->status == SCENARIO_STATUS_PENDING)
	{
		pScenario->status = SCENARIO_STATUS_RUNNING;
		if (show) printScenario(pScenario);

		pScenario->pFunc(pScenario);
		if (pScenario->status == SCENARIO_STATUS_RUNNING)
			pScenario->status = SCENARIO_STATUS_COMPLETE;

		if (show) printScenario(pScenario);
	}
}

void cancelScenario(struct CTestScenario* pScenario)
{
	pScenario->status = SCENARIO_STATUS_CANCELED;
}

char isScenarioCanceled(struct CTestScenario* pScenario)
{
	if (pScenario->status == SCENARIO_STATUS_CANCELED)
		return 1;
	else
		return 0;
}

char didScenarioPass(struct CTestScenario* pScenario)
{
	if (pScenario->status == SCENARIO_STATUS_COMPLETE)
	{
		int numberPassed = 0, numberFailed = 0;
		struct CTestExpectationResult* pR = pScenario->pResults;
		while (pR != 0)
		{
			if (didExpectationResultPass(pR))
				numberPassed++;
			else
				numberFailed++;

			pR = pR->pNext;
		}

		if (numberPassed > 0 && numberFailed == 0)
			return EXPECTATION_PASS;
	}

	return EXPECTATION_FAIL;
}

void printScenario(struct CTestScenario* pScenario)
{
	putchar(' ');
	if (pScenario->status == SCENARIO_STATUS_RUNNING)
		printf("[      ]");
	else if (pScenario->status == SCENARIO_STATUS_CANCELED)
		printf("[CANCEL]");
	else if (pScenario->status == SCENARIO_STATUS_COMPLETE)
	{
		if (didScenarioPass(pScenario)) printf("[  OK  ]");
		else printf("[ FAIL ]");
	}
	else
		printf("[  --  ]");

	if (pScenario->pDesc) printf("\t%s", pScenario->pDesc);

	if (pScenario->status == SCENARIO_STATUS_RUNNING)
		printf("\r");
	else
	{
		printf("\n");
		struct CTestExpectationResult* pR = pScenario->pResults;
		while (pR)
		{
			printExpectationResult(pR);
			pR = pR->pNext;
		}

		for (int i = 0; i < 80; i++) printf("-");
		printf("\n");
	}
}
