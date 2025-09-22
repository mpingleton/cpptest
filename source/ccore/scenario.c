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
	pScenario->pState = 0;
	pScenario->status = SCENARIO_STATUS_PENDING;
	pScenario->loops = 0;

	size_t lenDesc = strlen(pDesc);
	if (lenDesc > 0)
	{
		pScenario->pDesc = (char*)malloc(lenDesc + 1);
		strcpy(pScenario->pDesc, pDesc);
	}

	pScenario->pFirstResult = 0;
	pScenario->pLastResult = 0;
	pScenario->pFuncSetupOnce = 0;
	pScenario->pFuncSetupEach = 0;
	pScenario->pFuncTeardownOnce = 0;
	pScenario->pFuncTeardownEach = 0;
	pScenario->pFuncShouldRepeat = 0;
	pScenario->pFuncTest = pFunc;
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
			if (show > SHOW_NOTHING)
			{
				printScenario(pScenario, show, "");
				printf("\t\t\t\t\t\t\t\t");
			}

			fflush(0);
		}

		if (pScenario->pFuncSetupOnce)
			pScenario->pFuncSetupOnce(pScenario->pState);

		do
		{	
			if (pScenario->pFuncSetupEach)
				pScenario->pFuncSetupEach(pScenario->pState);

			pScenario->pFuncTest(pScenario);

			if (pScenario->pFuncTeardownEach)
				pScenario->pFuncTeardownEach(pScenario->pState);

			pScenario->loops++;

			if (pScenario->status != SCENARIO_STATUS_RUNNING)
				break;

			if (show)
			{
				if (show > SHOW_NOTHING)
				{
					printf("\r\x1b[2K");
					printScenario(pScenario, show, "");
					printf("\t\t\t\t\t\t\t\t");
				}

				fflush(0);
			}
	
			if (pScenario->pFuncShouldRepeat == 0)
				break;
		}
		while (pScenario->pFuncShouldRepeat(pScenario));

		if (pScenario->pFuncTeardownOnce)
			pScenario->pFuncTeardownOnce(pScenario->pState);

		if (pScenario->status == SCENARIO_STATUS_RUNNING)
			pScenario->status = SCENARIO_STATUS_COMPLETE;
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

void printScenario(struct CTestScenario* pScenario, char show, char* pStartLine)
{
	if (pScenario->status == SCENARIO_STATUS_RUNNING)
	{
		printf("[ \x1b[34m\x1b[1m");

		if (pScenario->loops > 0)
		{
			int ml = pScenario->loops % 4;
			for (int i = 0; i < 4; i++)
			{
				if (i == ml) printf("\x1b[93m>\x1b[34m");
				else printf(">");
			}
		}
		else printf(">>>>");

		printf("\x1b[0m ]");
	}
	else if (pScenario->status == SCENARIO_STATUS_CANCELED)
		printf("[\x1b[91m\x1b[1mCANCEL\x1b[0m]");
	else if (pScenario->status == SCENARIO_STATUS_COMPLETE)
	{
		if (didScenarioPass(pScenario)) printf("[  \x1b[32m\x1b[1mOK\x1b[0m  ]");
		else printf("[ \x1b[91m\x1b[1mFAIL\x1b[0m ]");
	}
	else
		printf("[  --  ]");

	if (pScenario->pDesc) printf(" %s", pScenario->pDesc);

	if (pScenario->status != SCENARIO_STATUS_RUNNING)
	{
		printf("\n");

		if (show == SHOW_EVERYTHING)
		{
			struct CTestExpectationResult* pR = pScenario->pFirstResult;
			while (pR)
			{
				printf("%s", pStartLine);
				if (pR->pNext)
					printf("   \x1b[90m|---\x1b[0m");
				else
					printf("   \x1b[90m\\---\x1b[0m");

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
				{
					printf("%s", pStartLine);
					if (pR->pNext)
						printf("   \x1b[90m|---\x1b[0m");
					else
						printf("   \x1b[90m\\---\x1b[0m");
				
					printExpectationResult(pR);
				}

				pR = pR->pNext;
			}
		}
	}
}
