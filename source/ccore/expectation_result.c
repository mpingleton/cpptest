//-----------------------------------------------------------------------------
// CPPTEST
//
// ccore/expectation_result.c
//
// Functions which handle expectation results.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"

#include <stdlib.h>
#include <string.h>

struct CTestExpectationResult* initExpectationResult(const char* pId)
{
	struct CTestExpectationResult* pNew = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	if (pNew == 0) return 0;

	memset(pNew, 0, sizeof(struct CTestExpectationResult));

	if (pId)
	{
		size_t l = strlen(pId);
		pNew->pId = (char*)malloc(l + 1);
		strcpy(pNew->pId, pId);
	}

	return pNew;
}

void freeExpectationResult(struct CTestExpectationResult* pResult)
{
	struct CTestExpectationResult* pCurrent = pResult;
	while (pCurrent)
	{
		struct CTestExpectationResult* pNext = pCurrent->pNext;

		if (pCurrent->pId)
		{
			size_t l = strlen(pCurrent->pId);
			memset(pCurrent->pId, 0, l);
			free(pCurrent->pId);
		}

		if (pCurrent->type == EXPECTATION_STRING)
		{
			if (pCurrent->actual.pStringValue)
			{
				size_t lenA = strlen(pCurrent->actual.pStringValue);
				memset(pCurrent->actual.pStringValue, 0, lenA);
				free(pCurrent->actual.pStringValue);
			}

			if (pCurrent->expected.pStringValue)
			{
				size_t lenE = strlen(pCurrent->expected.pStringValue);
				memset(pCurrent->expected.pStringValue, 0, lenE);
				free(pCurrent->expected.pStringValue);	
			}
		}

		memset(pCurrent, 0, sizeof(struct CTestExpectationResult));
		free(pCurrent);

		pCurrent = pNext;
	}
}

char didExpectationResultPass(struct CTestExpectationResult* pResult)
{
	return pResult->result;
}

void printExpectationResult(struct CTestExpectationResult* pResult)
{
	putchar(' ');

	if (didExpectationResultPass(pResult))
		printf("[  \x1b[32m\x1b[1mOK\x1b[0m  ]");
	else
		printf("[ \x1b[91m\x1b[1mFAIL\x1b[0m ]");

	printf(" (%s - %i)\t", pResult->pId, pResult->index);

	char comp[4] = {};
	switch (pResult->comparison)
	{
	case EXPECTATION_NOT_EQUAL:
	{
		strcpy((char*)&comp, "!");
		break;
	}
	case EXPECTATION_GREATER:
	{
		strcpy((char*)&comp, ">");
		break;
	}
	case EXPECTATION_GREATER_OR_EQUAL:
	{
		strcpy((char*)&comp, ">=");
		break;
	}
	case EXPECTATION_SMALLER:
	{
		strcpy((char*)&comp, "<");
		break;
	}
	case EXPECTATION_SMALLER_OR_EQUAL:
	{
		strcpy((char*)&comp, "<=");
		break;
	}
	}

	switch (pResult->type)
	{
	case EXPECTATION_POINTER:
	{
		if (pResult->actual.pointerValue == pResult->expected.pointerValue)
			printf("Pointers Match");
		else
			printf("Pointers Don't Match");

		break;
	}
	case EXPECTATION_INT:
	{
		printf("Actual: %i\tExpected: %s%i", pResult->actual.intValue, comp, pResult->expected.intValue);
		break;
	}
	case EXPECTATION_FLOAT:
	{
		printf("Actual: %f\tExpected: %s%f", pResult->actual.floatValue, comp, pResult->expected.floatValue);
		break;
	}
	case EXPECTATION_DOUBLE:
	{
		printf("Actual: %f\tExpected: %s%f", pResult->actual.doubleValue, comp, pResult->expected.doubleValue);
		break;
	}
	case EXPECTATION_STRING:
	{
		if (pResult->actual.pStringValue)
			printf("Actual: \"%s\"", pResult->actual.pStringValue);
		else
			printf("Actual: (null)");

		putchar('\t');

		if (pResult->expected.pStringValue)
			printf("Expected: %s\"%s\"", comp, pResult->expected.pStringValue);
		else
			printf("Expected: (null)");

		break;
	}
	default:
	{
		printf("(Unrecognized Result Type)");
		break;
	}
	}

	printf("\n");
}
