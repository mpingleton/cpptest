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
		pScenario->pDesc = (char*)malloc(lenDesc + 1);
		strcpy(pScenario->pDesc, pDesc);
	}

	pScenario->pFirstResult = 0;
	pScenario->pLastResult = 0;
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

	if (pScenario->pFirstResult)
		freeExpectationResult(pScenario->pFirstResult);

	memset(pScenario, 0, sizeof(struct CTestScenario));
}

void addResultToScenario(struct CTestScenario* pScenario, struct CTestExpectationResult* pResult)
{
	if (pScenario->pFirstResult)
	{
		struct CTestExpectationResult* pCurrent = pScenario->pFirstResult;
		while (pCurrent)
		{
			if (pCurrent->pId == 0 && pResult->pId == 0)
				pResult->index++;
			else if (pCurrent->pId == 0 || pResult->pId == 0)
				continue;
			else if (strcmp(pCurrent->pId, pResult->pId) == 0)
				pResult->index++;

			pCurrent = pCurrent->pNext;
		}

		pScenario->pLastResult->pNext = pResult;
	}
	else
		pScenario->pFirstResult = pResult;

	pScenario->pLastResult = pResult;
}

void runScenario(struct CTestScenario* pScenario, char show)
{
	if (pScenario->status == SCENARIO_STATUS_PENDING)
	{
		pScenario->status = SCENARIO_STATUS_RUNNING;

		if (show)
		{
			if (show > SHOW_NOTHING) printScenario(pScenario, show);
			fflush(0);
		}

		pScenario->pFunc(pScenario);
		if (pScenario->status == SCENARIO_STATUS_RUNNING)
			pScenario->status = SCENARIO_STATUS_COMPLETE;

		if (show > SHOW_NOTHING) printScenario(pScenario, show);
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
		struct CTestExpectationResult* pR = pScenario->pFirstResult;
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

void printScenario(struct CTestScenario* pScenario, char show)
{
	putchar(' ');
	if (pScenario->status == SCENARIO_STATUS_RUNNING)
		printf("[ >>>> ]");
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

		if (show == SHOW_EVERYTHING)
		{
			struct CTestExpectationResult* pR = pScenario->pFirstResult;
			while (pR)
			{
				printExpectationResult(pR);
				pR = pR->pNext;
			}
		}
		else if (show == SHOW_ONLY_FAILING)
		{
			struct CTestExpectationResult* pR = pScenario->pFirstResult;
			while (pR)
			{
				if (!didExpectationResultPass(pR))
					printExpectationResult(pR);

				pR = pR->pNext;
			}
		}
	}
}
