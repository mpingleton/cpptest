//-----------------------------------------------------------------------------
// CPPTEST
//
// cpptest.h
//
// Primary include header file for the CPPTEST library's C testing framework.
// Contains initial definitions for the Runner, Section, Scenario and
// prototype functions for handling each.
//
// Created	: 26 March 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#ifndef CPPTEST_H
#define CPPTEST_H

#include <stdio.h>

#define EXPECTATION_POINTER 1
#define EXPECTATION_INT 2
#define EXPECTATION_FLOAT 3
#define EXPECTATION_DOUBLE 4

#define EXPECTATION_FAIL 0
#define EXPECTATION_PASS 1

#define SCENARIO_STATUS_PENDING 0
#define SCENARIO_STATUS_RUNNING 1
#define SCENARIO_STATUS_CANCELED 2
#define SCENARIO_STATUS_COMPLETE 3

union CTestExpectationValue
{
	void* pointerValue;
	int intValue;
	float floatValue;
	double doubleValue;
};

struct CTestExpectationResult
{
	int index;
	int expectationId;
	struct CTestExpectationResult* pNext;

	char type;
	char result;
	union CTestExpectationValue actual;
	union CTestExpectationValue expected;
};

// expectation_result.c
void freeExpectationResult(struct CTestExpectationResult* pResult);
char didExpectationResultPass(struct CTestExpectationResult* pResult);
void printExpectationResult(struct CTestExpectationResult* pResult);

struct CTestScenario
{
	char status;
	char* pDesc;
	struct CTestExpectationResult* pResults;
	void (*pFunc)(struct CTestScenario* pScenario);
};

// scenario.c
void initScenario(struct CTestScenario* pScenario, const char* pDesc, void (*pFunc)(struct CTestScenario* pScenario));
void freeScenario(struct CTestScenario* pScenario);
void runScenario(struct CTestScenario* pScenario);
void cancelScenario(struct CTestScenario* pScenario);
char isScenarioCanceled(struct CTestScenario* pScenario);
char didScenarioPass(struct CTestScenario* pScenario);
void printScenario(struct CTestScenario* pScenario);

// expectation.c
void expectPointerNull(struct CTestScenario* pScenario, void* pointer);
void expectPointerInitialized(struct CTestScenario* pScenario, void* pointer);
void expectToEqualPointer(struct CTestScenario* pScenario, void* pActual, void* pExpected);
void expectToEqualInt(struct CTestScenario* pScenario, int actual, int expected);
void expectToEqualFloat(struct CTestScenario* pScenario, float actual, float expected);
void expectToEqualDouble(struct CTestScenario* pScenario, double actual, double expected);

struct CTestSection
{
	char* pDesc;
	int numberScenarios;
	struct CTestScenario* pScenarios;
};

// section.c
void initSection(struct CTestSection* pSection, const char* pDesc, int numberScenarios);
void freeSection(struct CTestSection* pSection);
void runSection(struct CTestSection* pSection, char show);
char didSectionPass(struct CTestSection* pSection);
void printSection(struct CTestSection* pSection);

struct CTestRunner
{
	int numberSections;
	struct CTestSection* pSection;
};

// runner.c
void initTests(struct CTestRunner* pRunner, int numberSections);
void freeTests(struct CTestRunner* pRunner);
void runTests(struct CTestRunner* pRunner, char show);
char didTestsPass(struct CTestRunner* pRunner);
void printTests(struct CTestRunner* pRunner);

#endif
