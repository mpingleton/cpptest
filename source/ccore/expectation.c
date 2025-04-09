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
	size_t lenParentId = strlen(pParentId);
	size_t lenChildId = strlen(pChildId);

	int c = 0;
	for (int i = 0; i < lenParentId; i++)
	{
		if (c >= maxLen) return pBuffer;
		pBuffer[c] = pParentId[i];
		c++;
	}

	if (c >= maxLen) return pBuffer;
	pBuffer[c] = '\\';
	c++;

	for (int i = 0; i <  lenChildId; i++)
	{
		if (c >= maxLen) return pBuffer;
		pBuffer[c] = pChildId[i];
		c++;
	}

	if (c >= maxLen) return pBuffer;
	pBuffer[c] = '\0';

	return pBuffer;
}

char expectPointerNull(struct CTestScenario* pScenario, const char* id, void* pointer)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->type = EXPECTATION_POINTER;
	pR->actual.pointerValue = pointer;
	pR->expected.pointerValue = 0;

	size_t sizeId = strlen(id);
	if (sizeId > 0)
	{
		pR->pId = (char*)malloc(sizeId);
		strcpy(pR->pId, id);
	}
	else pR->pId = 0;

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
		while (pRes->pNext)
		{
			if (strcmp(pRes->pId, id) == 0) pR->index++;
			pRes = pRes->pNext;
		}
		if (strcmp(pRes->pId, id) == 0) pR->index++;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;

	return pR->result;
}

char expectPointerInitialized(struct CTestScenario* pScenario, const char* id, void* pointer)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->type = EXPECTATION_POINTER;
	pR->actual.pointerValue = pointer;
	pR->expected.pointerValue = 0;

	size_t sizeId = strlen(id);
	if (sizeId > 0)
	{
		pR->pId = (char*)malloc(sizeId);
		strcpy(pR->pId, id);
	}
	else pR->pId = 0;

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
		while (pRes->pNext)
		{
			if (strcmp(pRes->pId, id) == 0) pR->index++;
			pRes = pRes->pNext;
		}
		if (strcmp(pRes->pId, id) == 0) pR->index++;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;

	return pR->result;
}

char expectToEqualPointer(struct CTestScenario* pScenario, const char* id, void* pActual, void* pExpected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->type = EXPECTATION_POINTER;
	pR->actual.pointerValue = pActual;
	pR->expected.pointerValue = pExpected;

	size_t sizeId = strlen(id);
	if (sizeId > 0)
	{
		pR->pId = (char*)malloc(sizeId);
		strcpy(pR->pId, id);
	}
	else pR->pId = 0;

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
		while (pRes->pNext)
		{
			if (strcmp(pRes->pId, id) == 0) pR->index++;
			pRes = pRes->pNext;
		}
		if (strcmp(pRes->pId, id) == 0) pR->index++;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;

	return pR->result;
}

char expectToEqualInt(struct CTestScenario* pScenario, const char* id, int actual, int expected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->type = EXPECTATION_INT;
	pR->actual.intValue = actual;
	pR->expected.intValue = expected;

	size_t sizeId = strlen(id);
	if (sizeId > 0)
	{
		pR->pId = (char*)malloc(sizeId);
		strcpy(pR->pId, id);
	}
	else pR->pId = 0;

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
		while (pRes->pNext)
		{
			if (strcmp(pRes->pId, id) == 0) pR->index++;
			pRes = pRes->pNext;
		}
		if (strcmp(pRes->pId, id) == 0) pR->index++;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;

	return pR->result;
}

char expectToEqualFloat(struct CTestScenario* pScenario, const char* id, float actual, float expected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->type = EXPECTATION_FLOAT;
	pR->actual.floatValue = actual;
	pR->expected.floatValue = expected;

	size_t sizeId = strlen(id);
	if (sizeId > 0)
	{
		pR->pId = (char*)malloc(sizeId);
		strcpy(pR->pId, id);
	}
	else pR->pId = 0;

	if ((actual >= expected - 0.01) && (actual <= expected + 0.01))
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext)
		{
			if (strcmp(pRes->pId, id) == 0) pR->index++;
			pRes = pRes->pNext;
		}
		if (strcmp(pRes->pId, id) == 0) pR->index++;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;

	return pR->result;
}

char expectToEqualDouble(struct CTestScenario* pScenario, const char* id, double actual, double expected)
{
	struct CTestExpectationResult* pR = (struct CTestExpectationResult*)malloc(sizeof(struct CTestExpectationResult));
	pR->index = 0;
	pR->type = EXPECTATION_DOUBLE;
	pR->actual.doubleValue = actual;
	pR->expected.doubleValue = expected;

	size_t sizeId = strlen(id);
	if (sizeId > 0)
	{
		pR->pId = (char*)malloc(sizeId);
		strcpy(pR->pId, id);
	}
	else pR->pId = 0;

	if ((actual >= expected - 0.01) && (actual <= expected + 0.01))
		pR->result = EXPECTATION_PASS;
	else
	{
		pR->result = EXPECTATION_FAIL;
		cancelScenario(pScenario);
	}

	if (pScenario->pResults)
	{
		struct CTestExpectationResult* pRes = pScenario->pResults;
		while (pRes->pNext)
		{
			if (strcmp(pRes->pId, id) == 0) pR->index++;
			pRes = pRes->pNext;
		}
		if (strcmp(pRes->pId, id) == 0) pR->index++;
		pRes->pNext = pR;
	}
	else
		pScenario->pResults = pR;

	return pR->result;
}
