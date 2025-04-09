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

void freeExpectationResult(struct CTestExpectationResult* pResult)
{
	struct CTestExpectationResult* pCurrent = pResult;
	struct CTestExpectationResult* pNext = 0;
	while (pCurrent)
	{
		pNext = pCurrent->pNext;

		if (pCurrent->pId)
		{
			size_t l = strlen(pCurrent->pId);
			memset(pCurrent->pId, 0, l);
			free(pCurrent->pId);
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
	putchar('\t');

	if (didExpectationResultPass(pResult))
		printf("[  OK  ]");
	else
		printf("[ FAIL ]");

	printf(" (%s - %i)\t", pResult->pId, pResult->index);

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
		printf("Actual: %i\tExpected: %i", pResult->actual.intValue, pResult->expected.intValue);
		break;
	}
	case EXPECTATION_FLOAT:
	{
		printf("Actual: %f\tExpected: %f", pResult->actual.floatValue, pResult->expected.floatValue);
		break;
	}
	case EXPECTATION_DOUBLE:
	{
		printf("Actual: %f\tExpected: %f", pResult->actual.doubleValue, pResult->expected.doubleValue);
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
