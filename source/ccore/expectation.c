//-----------------------------------------------------------------------------
// CPPTEST
//
// ccore/expectation.c
//
// Functions which test expectations.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"

#include <stdlib.h>
#include <string.h>

char* expectId(char* pBuffer, size_t maxLen, const char* pParentId, const char* pChildId)
{
	memset(pBuffer, 0, maxLen);

	strcpy(pBuffer, pParentId);
	strcat(pBuffer, "\\");
	strcat(pBuffer, pChildId);

	return pBuffer;
}

char expectPointerNull(struct CTestScenario* pScenario, const char* id, void* pointer)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_POINTER;
	pR->comparison = EXPECTATION_EQUAL;
	pR->actual.pointerValue = pointer;
	pR->expected.pointerValue = 0;

	if (pointer == 0)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	addResultToScenario(pScenario, pR);
	return pR->result;
}

char expectPointerInitialized(struct CTestScenario* pScenario, const char* id, void* pointer)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_POINTER;
	pR->comparison = EXPECTATION_NOT_EQUAL;
	pR->actual.pointerValue = pointer;
	pR->expected.pointerValue = 0;

	if (pointer != 0)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	addResultToScenario(pScenario, pR);
	return pR->result;
}

char expectToEqualPointer(struct CTestScenario* pScenario, const char* id, void* pActual, void* pExpected)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_POINTER;
	pR->comparison = EXPECTATION_EQUAL;
	pR->actual.pointerValue = pActual;
	pR->expected.pointerValue = pExpected;

	if (pActual == pExpected)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	addResultToScenario(pScenario, pR);
	return pR->result;
}

char expectToEqualInt(struct CTestScenario* pScenario, const char* id, int actual, int expected)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_INT;
	pR->comparison = EXPECTATION_EQUAL;
	pR->actual.intValue = actual;
	pR->expected.intValue = expected;

	if (actual == expected)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	addResultToScenario(pScenario, pR);
	return pR->result;
}

char expectToEqualFloat(struct CTestScenario* pScenario, const char* id, float actual, float expected)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_FLOAT;
	pR->comparison = EXPECTATION_EQUAL;
	pR->actual.floatValue = actual;
	pR->expected.floatValue = expected;
	pR->pNext = 0;

	if ((actual >= expected - 0.1) && (actual <= expected + 0.1))
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	addResultToScenario(pScenario, pR);
	return pR->result;
}

char expectToEqualDouble(struct CTestScenario* pScenario, const char* id, double actual, double expected)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_DOUBLE;
	pR->comparison = EXPECTATION_EQUAL;
	pR->actual.doubleValue = actual;
	pR->expected.doubleValue = expected;

	if ((actual >= expected - 0.1) && (actual <= expected + 0.1))
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	addResultToScenario(pScenario, pR);
	return pR->result;
}

char expectToEqualString(struct CTestScenario* pScenario, const char* id, const char* actual, const char* expected)
{
	struct CTestExpectationResult* pR = initExpectationResult(id);
	if (pR == 0)
	{
		cancelScenario(pScenario);
		return EXPECTATION_FAIL;
	}

	pR->type = EXPECTATION_STRING;
	pR->comparison = EXPECTATION_EQUAL;

	size_t sizeA = 0;
	if (actual)
	{
		sizeA = strlen(actual);
		if (sizeA > 0)
		{
			pR->actual.pStringValue = (char*)malloc(sizeA + 1);
			strcpy(pR->actual.pStringValue, actual);
		}
		else pR->actual.pStringValue = 0;
	}
	else pR->actual.pStringValue = 0;

	size_t sizeE = 0;
	if (expected)
	{
		sizeE = strlen(expected);
		if (sizeE > 0)
		{
			pR->expected.pStringValue = (char*)malloc(sizeE + 1);
			strcpy(pR->expected.pStringValue, expected);
		}
		else pR->expected.pStringValue = 0;
	}
	else pR->expected.pStringValue = 0;
	
	if (actual == 0 || expected == 0)
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}
	else if (sizeA != sizeE)
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}
	else if (strcmp(pR->actual.pStringValue, pR->expected.pStringValue) != 0)
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}
	else pR->result = EXPECTATION_PASS;

	addResultToScenario(pScenario, pR);
	return pR->result;
}
