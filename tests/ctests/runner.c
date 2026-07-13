//-----------------------------------------------------------------------------
// CPPTEST
//
// runner.c
//
// Tests for runners.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"
#include "../tests.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void someScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualInt(pScenario, "1", 3, 2);
	expectToEqualFloat(pScenario, "2", 3.14f, 3.14f);
	expectToEqualString(pScenario, "3", "Hello world!", "Hello world!");
	expectToEqualString(pScenario, "3", "Hello world", "Hello world!");

	if (isScenarioCanceled(pScenario)) return;

	expectToEqualDouble(pScenario, "3", 1.2, 1.2);
}

void anotherScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualInt(pScenario, "1", 10, 10);
	expectToEqualInt(pScenario, "1", 2, 2);
	expectToEqualFloat(pScenario, "2", 3.14f, 3.14f);

	if (isScenarioCanceled(pScenario)) return;

	expectToEqualDouble(pScenario, "3", 1.2, 1.2);

	int a = 0;
	int* b = 0;
	int* c = &a;
	expectPointerNull(pScenario, "4", b);
	expectPointerInitialized(pScenario, "5", c);
	expectToEqualPointer(pScenario, "6", c, &a);
}

void someotherScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	expectToEqualInt(pScenario, "1", 1, 1);
	expectToEqualInt(pScenario, "2", 2, 2);
}

void yetotherScenario1(struct CTestScenario* pScenario)
{
	sleep(3);

	for (int i = 0; i < 10000; i++)
	{
		expectToEqualFloat(pScenario, "1", 3.14f, 3.14f);
		expectToEqualDouble(pScenario, "2", 1.4, 1.4);
	}
}

void fineonemoreScenario1(struct CTestScenario* pScenario)
{
	sleep(2);

	for (int i = 0; i < 10000; i++)
	{
		expectToEqualFloat(pScenario, "1", 3.14f, 3.14f);
		expectToEqualDouble(pScenario, "2", 1.4, 1.4);
	}
}

struct StressTestState
{
	int r, t;
	int suO, suE;
	int tdO, tdE;
};

void setupOnceFirstStressTest(void* pState)
{
	((struct StressTestState*)pState)->suO++;
}

void setupEachFirstStressTest(void* pState)
{
	((struct StressTestState*)pState)->suE++;
}

void teardownOnceFirstStressTest(void* pState)
{
	((struct StressTestState*)pState)->tdO++;
}

void teardownEachFirstStressTest(void* pState)
{
	((struct StressTestState*)pState)->tdE++;
}

int shouldRepeatFirstStressTest(struct CTestScenario* pScenario)
{
	struct StressTestState* pState = (struct StressTestState*)pScenario->pState;
	if (pState->r >= 10)
		return 0;

	pState->r++;
	return 1;
}

void testFirstStressTest(struct CTestScenario* pScenario)
{
	struct StressTestState* pState = (struct StressTestState*)pScenario->pState;
	
	sleep(1);

	expectToEqualInt(pScenario, "setupOnce called", pState->suO, 1);
	expectToEqualInt(pScenario, "teardownOnce called", pState->tdO, 0);

	expectToEqualInt(pScenario, "setupEach", pState->suE, pState->r + 1);
	expectToEqualInt(pScenario, "teardownEach", pState->tdE, pState->r);
}

void setupOnceSecondStressTest(void* pState)
{
	((struct StressTestState*)pState)->suO++;
}

void setupEachSecondStressTest(void* pState)
{
	((struct StressTestState*)pState)->suE++;
}

void teardownOnceSecondStressTest(void* pState)
{
	((struct StressTestState*)pState)->tdO++;
}

void teardownEachSecondStressTest(void* pState)
{
	((struct StressTestState*)pState)->tdE++;
}

int shouldRepeatSecondStressTest(struct CTestScenario* pScenario)
{
	struct StressTestState* pState = (struct StressTestState*)pScenario->pState;
	if (pState->r >= 10000)
		return 0;

	pState->r++;
	return 1;
}

void testSecondStressTest(struct CTestScenario* pScenario)
{
	struct StressTestState* pState = (struct StressTestState*)pScenario->pState;
	pState->t++;

	if (pState->r < 10000) return;	

	expectToEqualInt(pScenario, "setupOnce called", pState->suO, 1);
	expectToEqualInt(pScenario, "teardownOnce called", pState->tdO, 0);

	expectToEqualInt(pScenario, "setupEach", pState->suE, pState->r + 1);
	expectToEqualInt(pScenario, "teardownEach", pState->tdE, pState->r);
}

void setupOnceThirdStressTest(void* pState)
{
	((struct StressTestState*)pState)->suO++;
}

void setupEachThirdStressTest(void* pState)
{
	((struct StressTestState*)pState)->suE++;
}

void teardownOnceThirdStressTest(void* pState)
{
	((struct StressTestState*)pState)->tdO++;
}

void teardownEachThirdStressTest(void* pState)
{
	((struct StressTestState*)pState)->tdE++;
}

int shouldRepeatThirdStressTest(struct CTestScenario* pScenario)
{
	struct StressTestState* pState = (struct StressTestState*)pScenario->pState;
	if (pState->r >= 10000)
		return 0;

	pState->r++;
	return 1;
}

void testThirdStressTest(struct CTestScenario* pScenario)
{
	struct StressTestState* pState = (struct StressTestState*)pScenario->pState;

	pState->t++;
	expectToEqualInt(pScenario, "r", pState->r, pState->t - 1);

	expectToEqualInt(pScenario, "setupOnce called", pState->suO, 1);
	expectToEqualInt(pScenario, "teardownOnce called", pState->tdO, 0);

	expectToEqualInt(pScenario, "setupEach", pState->suE, pState->r + 1);
	expectToEqualInt(pScenario, "teardownEach", pState->tdE, pState->r);
}

struct CTestSection* initSectionOne()
{
	struct CTestSection* pSection = initSection("Section One");
	addScenarioToSection(pSection, "Test 1", &someScenario1);

	return pSection;
}

struct CTestSection* initSectionTwo()
{
	struct CTestSection* pSection = initSection("Section Two");
	addScenarioToSection(pSection, "Test 2", &anotherScenario1);

	return pSection;
}

struct CTestSection* initSectionThr()
{
	struct CTestSection* pSection = initSection("Section Three");
	addScenarioToSection(pSection, "Test 3", &someotherScenario1);
	addScenarioToSection(pSection, "Test 4", &yetotherScenario1);

	return pSection;
}

struct CTestSection* initSectionFour()
{
	struct CTestSection* pSection = initSection("Section Four");
	addScenarioToSection(pSection, "Test 5", &fineonemoreScenario1);

	return pSection;
}

struct CTestSection* initStressTestSectionA(struct StressTestState* pState)
{
	struct CTestScenarioInitParams first = {};
	first.pState = pState;
	first.pFuncTest = &testFirstStressTest;
	first.pFuncSetupOnce = &setupOnceFirstStressTest;
	first.pFuncSetupEach = &setupEachFirstStressTest;
	first.pFuncTeardownEach = &teardownEachFirstStressTest;
	first.pFuncTeardownOnce = &teardownOnceFirstStressTest;
	first.pFuncShouldRepeat = &shouldRepeatFirstStressTest;

	struct CTestSection* pSection = initSection("Stress Testing A");
	addScenarioToSectionByParams(pSection, "Stress Test Scenario 1", &first);

	return pSection;
}

struct CTestSection* initStressTestSectionB(struct StressTestState* pStateA, struct StressTestState* pStateB)
{
	struct CTestScenarioInitParams second = {};
	second.pState = pStateA;
	second.pFuncTest = &testSecondStressTest;
	second.pFuncSetupOnce = &setupOnceSecondStressTest;
	second.pFuncSetupEach = &setupEachSecondStressTest;
	second.pFuncTeardownEach = &teardownEachSecondStressTest;
	second.pFuncTeardownOnce = &teardownOnceSecondStressTest;
	second.pFuncShouldRepeat = &shouldRepeatSecondStressTest;
	
	struct CTestScenarioInitParams third = {};
	third.pState = pStateB;
	third.pFuncTest = &testThirdStressTest;
	third.pFuncSetupOnce = &setupOnceThirdStressTest;
	third.pFuncSetupEach = &setupEachThirdStressTest;
	third.pFuncTeardownEach = &teardownEachThirdStressTest;
	third.pFuncTeardownOnce = &teardownOnceThirdStressTest;
	third.pFuncShouldRepeat = &shouldRepeatThirdStressTest;
	
	struct CTestSection* pSection = initSection("Stress Testing B");
	addScenarioToSectionByParams(pSection, "Stress Test Scenario 2", &second);
	addScenarioToSectionByParams(pSection, "Stress Test Scenario 3", &third);

	return pSection;	
}

int cTestRunner()
{
	struct CTestSection* pSections[4];
	pSections[0] = initSectionOne();
	pSections[1] = initSectionTwo();
	pSections[2] = initSectionThr();
	pSections[3] = initSectionFour();

	struct CTestRunner runner1 = {};
	initTests(&runner1);
	addSectionToTest(&runner1, pSections[0]);
	addSectionToTest(&runner1, pSections[1]);

	runTests(&runner1, SHOW_NOTHING);
	if (didTestsPass(&runner1))
	{
		printf("Tests should not have passed\n");
		return 0;
	}

	struct CTestRunner runner2 = {};
	initTests(&runner2);
	addSubsectionToSection(pSections[2], pSections[3]);
	addSectionToTest(&runner2, pSections[2]);

	runTests(&runner2, SHOW_NOTHING);
	if (!didTestsPass(&runner2))
	{
		printf("Tests should have passed\n");
		return 0;
	}

	//printTests(&runner1, SHOW_NOTHING);
	//printTests(&runner2, SHOW_NOTHING);

	freeTests(&runner1);
	freeTests(&runner2);

	struct CTestSection* pStressTests[2];
	struct StressTestState stressTestStates[3] = {};
	pStressTests[0] = initStressTestSectionA(&stressTestStates[0]);
	pStressTests[1] = initStressTestSectionB(&stressTestStates[1], &stressTestStates[2]);

	struct CTestRunner runner3 = {};
	initTests(&runner3);
	addSectionToTest(&runner3, pStressTests[0]);
	addSectionToTest(&runner3, pStressTests[1]);

	runTests(&runner3, SHOW_NOTHING);
	if (!didTestsPass(&runner3))
	{
		printf("Tests should have passed\n");
		return 0;
	}

	//printTests(&runner3, SHOW_NOTHING);

	freeTests(&runner3);
	
	return 1;
}
