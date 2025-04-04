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

void expectPointerNull(struct CTestScenario* pScenario, void* pointer)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->expectationId = 0;
	pR->type = EXPECTATION_POINTER;
	pR->actual.pointerValue = pointer;
	pR->expected.pointerValue = 0;

	if (pointer == 0)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext) pRes = pRes->pNext;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;
}

void expectPointerInitialized(struct CTestScenario* pScenario, void* pointer)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->expectationId = 0;
	pR->type = EXPECTATION_POINTER;
	pR->actual.pointerValue = pointer;
	pR->expected.pointerValue = 0;

	if (pointer != 0)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext) pRes = pRes->pNext;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;
}

void expectToEqualPointer(struct CTestScenario* pScenario, void* pActual, void* pExpected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->expectationId = 0;
	pR->type = EXPECTATION_POINTER;
	pR->actual.pointerValue = pActual;
	pR->expected.pointerValue = pExpected;

	if (pActual == pExpected)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext) pRes = pRes->pNext;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;
}

void expectToEqualInt(struct CTestScenario* pScenario, int actual, int expected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->expectationId = 0;
	pR->type = EXPECTATION_INT;
	pR->actual.intValue = actual;
	pR->expected.intValue = expected;

	if (actual == expected)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext) pRes = pRes->pNext;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;
}

void expectToEqualFloat(struct CTestScenario* pScenario, float actual, float expected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->expectationId = 0;
	pR->type = EXPECTATION_FLOAT;
	pR->actual.floatValue = actual;
	pR->expected.floatValue = expected;

	if (actual == expected)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext) pRes = pRes->pNext;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;
}

void expectToEqualDouble(struct CTestScenario* pScenario, double actual, double expected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->expectationId = 0;
	pR->type = EXPECTATION_DOUBLE;
	pR->actual.doubleValue = actual;
	pR->expected.doubleValue = expected;

	if (actual == expected)
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext) pRes = pRes->pNext;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;
}