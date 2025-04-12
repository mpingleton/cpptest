//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/scenario.c
//
// Tests for scenarios and expectations.
//
// Created	: 3 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../../include/tests.h"

#include <stdlib.h>
#include <string.h>

void someScenario(struct CTestScenario* pScenario)
{
	char b[100] = {};

	expectToEqualInt(pScenario, expectId((char*)&b, 100, "TEST", "1"), 10, 10);
	expectToEqualInt(pScenario, expectId((char*)&b, 100, "TEST", "1"), 3, 2);
	expectToEqualFloat(pScenario, expectId((char*)&b, 100, "TEST", "1"), 3.14f, 3.14f);

	if (isScenarioCanceled(pScenario)) return;

	expectToEqualDouble(pScenario, expectId((char*)&b, 100, "TEST", "1"), 1.2, 1.2);
}

void anotherScenario(struct CTestScenario* pScenario)
{
	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualInt(pScenario, "1", 2, 2);
	expectToEqualFloat(pScenario, "1", 3.14f, 3.14f);

	if (isScenarioCanceled(pScenario)) return;

	expectToEqualDouble(pScenario, "1", 1.2, 1.2);

	int a = 0;
	int* b = 0;
	int* c = &a;
	expectPointerNull(pScenario, "1", b);
	expectPointerInitialized(pScenario, "1", c);
	expectToEqualPointer(pScenario, "1", c, &a);
}

int cTestScenario()
{
	struct CTestScenario* pScenario1 = (struct CTestScenario*)malloc(sizeof(struct CTestScenario));
	memset(pScenario1, 0, sizeof(struct CTestScenario));
	initScenario(pScenario1, "Test 1", &someScenario);

	runScenario(pScenario1, 1);
	if (!isScenarioCanceled(pScenario1))
	{
		printf("Scenario should have been canceled\n");
		return 0;
	}
	else if (didScenarioPass(pScenario1))
	{
		printf("Scenario is passing when it shouldn't\n");
		return 0;
	}

	struct CTestExpectationResult* pE = pScenario1->pFirstResult;
	if (pE == 0)
	{
		printf("First result not present\n");
		return 0;
	}

	pE = pE->pNext;
	if (pE == 0)
	{
		printf("Second result not present\n");
		return 0;
	}

	pE = pE->pNext;
	if (pE == 0)
	{
		printf("Third result not present\n");
		return 0;
	}
	else if (pE != pScenario1->pLastResult)
	{
		printf("Last result mismatch\n");
		return 0;
	}
	else if (pE->pNext != 0)
	{
		printf("A fourth result is present where it shouldn't be\n");
		return 0;
	}

	printScenario(pScenario1, SHOW_EVERYTHING);
	freeScenario(pScenario1);
	free(pScenario1);

	struct CTestScenario* pScenario2 = (struct CTestScenario*)malloc(sizeof(struct CTestScenario));
	memset(pScenario2, 0, sizeof(struct CTestScenario));
	initScenario(pScenario2, "Test 2", &anotherScenario);

	runScenario(pScenario2, SHOW_EVERYTHING);
	if (isScenarioCanceled(pScenario2))
	{
		printf("Scenario was unduly canceled\n");
		return 0;
	}
	else if (!didScenarioPass(pScenario2))
	{
		printf("Scenario failed when it should have passed\n");
		return 0;
	}

	pE = pScenario2->pFirstResult;
	if (pE == 0)
	{
		printf("First result not present\n");
		return 0;
	}

	pE = pE->pNext;
	if (pE == 0)
	{
		printf("Second result not present\n");
		return 0;
	}

	pE = pE->pNext;
	if (pE == 0)
	{
		printf("Third result not present\n");
		return 0;
	}
	else if (pE != pScenario2->pLastResult)
	{
		printf("Last result mismatch\n");
		return 0;
	}
	else if (pE->pNext == 0)
	{
		printf("Fourth result not present\n");
		return 0;
	}

	printScenario(pScenario2, SHOW_EVERYTHING);
	freeScenario(pScenario2);
	free(pScenario2);

	return 1;
}
