//-----------------------------------------------------------------------------
// CPPTEST
//
// expectation_result.c
//
// Tests for expectation results.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../tests.h"

#include <stdlib.h>
#include <string.h>

const char* pHello = "Hello world!";
const char* pBye = "Goodbye world!";

int cTestExpectationResult()
{
	struct CTestExpectationResult* pResult1 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult1->index = 0;
	pResult1->pId = (char*)malloc(sizeof("TEST1"));
	strcpy(pResult1->pId, "TEST1");
	pResult1->type = EXPECTATION_INT;
	pResult1->comparison = EXPECTATION_EQUAL;
	pResult1->result = EXPECTATION_PASS;
	pResult1->actual.intValue = 2;
	pResult1->expected.intValue = 2;

	struct CTestExpectationResult* pResult2 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult1->pNext = pResult2;
	pResult2->index = 0;
	pResult2->pId = (char*)malloc(sizeof("TEST2"));
	strcpy(pResult2->pId, "TEST2");
	pResult2->type = EXPECTATION_DOUBLE;
	pResult2->comparison = EXPECTATION_EQUAL;
	pResult2->result = EXPECTATION_FAIL;
	pResult2->actual.doubleValue = 2.0;
	pResult2->expected.doubleValue = 3.0;

	struct CTestExpectationResult* pResult3 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult2->pNext = pResult3;
	pResult3->index = 0;
	pResult3->pId = (char*)malloc(sizeof("TEST3"));
	strcpy(pResult3->pId, "TEST3");
	pResult3->type = EXPECTATION_DOUBLE;
	pResult3->comparison = EXPECTATION_EQUAL;
	pResult3->result = EXPECTATION_PASS;
	pResult3->actual.doubleValue = 3.0;
	pResult3->expected.doubleValue = 3.0;

	struct CTestExpectationResult* pResult4 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult3->pNext = pResult4;
	pResult4->index = 0;
	pResult4->pId = (char*)malloc(sizeof("TEST4"));
	strcpy(pResult4->pId, "TEST4");
	pResult4->type = EXPECTATION_STRING;
	pResult4->comparison = EXPECTATION_EQUAL;
	pResult4->result = EXPECTATION_PASS;
	pResult4->actual.pStringValue = (char*)malloc(strlen(pHello));
	pResult4->expected.pStringValue = (char*)malloc(strlen(pHello));
	strcpy(pResult4->actual.pStringValue, pHello);
	strcpy(pResult4->expected.pStringValue, pHello);
	
	struct CTestExpectationResult* pResult5 = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pResult4->pNext = pResult5;
	pResult5->index = 0;
	pResult5->pId = (char*)malloc(sizeof("TEST5"));
	strcpy(pResult5->pId, "TEST5");
	pResult5->type = EXPECTATION_STRING;
	pResult5->comparison = EXPECTATION_EQUAL;
	pResult5->result = EXPECTATION_FAIL;
	pResult5->actual.pStringValue = (char*)malloc(strlen(pBye));
	pResult5->expected.pStringValue = (char*)malloc(strlen(pHello));
	strcpy(pResult5->actual.pStringValue, pBye);
	strcpy(pResult5->expected.pStringValue, pHello);

	//printExpectationResult(pResult1);
	//printExpectationResult(pResult2);
	//printExpectationResult(pResult3);
	//printExpectationResult(pResult4);
	//printExpectationResult(pResult5);

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
	else if (!didExpectationResultPass(pResult4))
	{
		printf("\tresult4 is not passing\n");
		return 0;
	}
	else if (didExpectationResultPass(pResult5))
	{
		printf("\tresult5 is passing\n");
		return 0;
	}

	freeExpectationResult(pResult1);

	return 1;
}
