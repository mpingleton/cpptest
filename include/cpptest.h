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

#define EXPECTATION_EQUAL 0
#define EXPECTATION_NOT_EQUAL 1
#define EXPECTATION_GREATER 2
#define EXPECTATION_SMALLER 3
#define EXPECTATION_GREATER_OR_EQUAL 4
#define EXPECTATION_SMALLER_OR_EQUAL 5

#define EXPECTATION_FAIL 0
#define EXPECTATION_PASS 1

#define SCENARIO_STATUS_PENDING 0
#define SCENARIO_STATUS_RUNNING 1
#define SCENARIO_STATUS_CANCELED 2
#define SCENARIO_STATUS_COMPLETE 3

#define SHOW_NOTHING 0
#define SHOW_ONLY_SECTIONS 1
#define SHOW_ONLY_FAILING 2
#define SHOW_EVERYTHING 3

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
	char* pId;
	struct CTestExpectationResult* pNext;

	char type;
	char comparison;
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
	struct CTestExpectationResult* pFirstResult;
	struct CTestExpectationResult* pLastResult;
	void (*pFunc)(struct CTestScenario* pScenario);
};

// scenario.c
void initScenario(struct CTestScenario* pScenario, const char* pDesc, void (*pFunc)(struct CTestScenario* pScenario));
void freeScenario(struct CTestScenario* pScenario);
void addResultToScenario(struct CTestScenario* pScenario, struct CTestExpectationResult result);
void runScenario(struct CTestScenario* pScenario, char show);
void cancelScenario(struct CTestScenario* pScenario);
char isScenarioCanceled(struct CTestScenario* pScenario);
char didScenarioPass(struct CTestScenario* pScenario);
void printScenario(struct CTestScenario* pScenario, char show);

// expectation.c
char* expectId(char* pBuffer, size_t maxLen, const char* pParentId, const char* pChildId);
char expectPointerNull(struct CTestScenario* pScenario, const char* id, void* pointer);
char expectPointerInitialized(struct CTestScenario* pScenario, const char* id, void* pointer);
char expectToEqualPointer(struct CTestScenario* pScenario, const char* id, void* pActual, void* pExpected);
char expectToEqualInt(struct CTestScenario* pScenario, const char* id, int actual, int expected);
char expectToEqualFloat(struct CTestScenario* pScenario, const char* id, float actual, float expected);
char expectToEqualDouble(struct CTestScenario* pScenario, const char* id, double actual, double expected);

struct CTestSection
{
	char* pDesc;
	int numberScenarios, numberSubsections;
	struct CTestScenario* pScenarios;
	struct CTestScenario* pSubsections; // TODO
};

// section.c
void initSection(struct CTestSection* pSection, const char* pDesc, int numberScenarios);
void addScenarioToSection(struct CTestSection* pSection, const char* pDesc, void (*pFunc)(struct CTestScenario* pScenario));
void addSubsectionToSection(struct CTestSection* pSection, struct CTestSection* pSubsection);
void freeSection(struct CTestSection* pSection);
void runSection(struct CTestSection* pSection, char show);
char didSectionPass(struct CTestSection* pSection);
void printSection(struct CTestSection* pSection, char show);

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
void printTests(struct CTestRunner* pRunner, char show);

#endif
