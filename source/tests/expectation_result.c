//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/expectation_result.c
//
// Tests for expectation results.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../../include/tests.h"

#include <stdlib.h>

int cTestExpectationResult()
{
	// TODO: Create a few expectation results in a linked list.
	struct CTestExpectationResult* pResult1 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult1->index = 0;
	pResult1->expectationId = 1;
	pResult1->type = EXPECTATION_INT;
	pResult1->result = EXPECTATION_PASS;
	pResult1->actual.intValue = 2;
	pResult1->expected.intValue = 2;

	struct CTestExpectationResult* pResult2 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult1->pNext = pResult2;
	pResult2->index = 1;
	pResult2->expectationId = 2;
	pResult2->type = EXPECTATION_DOUBLE;
	pResult2->result = EXPECTATION_FAIL;
	pResult2->actual.doubleValue = 2.0;
	pResult2->expected.doubleValue = 3.0;

	struct CTestExpectationResult* pResult3 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult2->pNext = pResult3;
	pResult3->index = 2;
	pResult3->expectationId = 3;
	pResult3->type = EXPECTATION_DOUBLE;
	pResult3->result = EXPECTATION_PASS;
	pResult3->actual.doubleValue = 3.0;
	pResult3->expected.doubleValue = 3.0;

	printExpectationResult(pResult1);
	printExpectationResult(pResult2);
	printExpectationResult(pResult3);

	// TODO: Did they pass?
	if (!didExpectationResultPass(pResult1))
	{
		printf("\tresult1 is not passing\n");
		return 0;
	}
	else if (didExpectationResultPass(pResult2))
	{
		printf("\tresult2 is passing\n");
		return 0;
	}
	else if (!didExpectationResultPass(pResult3))
	{
		printf("\tresult3 is not passing\n");
		return 0;
	}

	// TODO: Free them.
	freeExpectationResult(pResult1);

	return 1;
}