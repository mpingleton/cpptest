//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/scenario.cpp
//
// Tests for scenarios and expectations.
//
// Created	: 3 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"
#include "../../include/tests.hpp"

#include <iostream>

using namespace std;
using namespace cpptest;

class SomeScenario : public Scenario
{
public:
	SomeScenario() : Scenario("Test 1")
	{}

	~SomeScenario()
	{}

	void test()
	{
		expectToEqual("", "1", 10, 10);
		expectToEqual("", "1", 3, 2);
		expectToEqual("", "1", 3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual("", "1", 1.2, 1.2);
	}
};

class AnotherScenario : public Scenario
{
public:
	AnotherScenario() : Scenario("Test 2")
	{}

	~AnotherScenario()
	{}

	void test()
	{
		expectToEqual("", "1", 10, 10);
		expectToEqual("", "1", 2, 2);
		expectToEqual("", "1", 3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual("", "1", 1.2, 1.2);

		int a = 0;
		int* b = 0;
		int* c = &a;
		expectPointerNull("", "1", b);
		expectPointerInitialized("", "1", c);
		expectToEqual("", "1", c, &a);
	}
};

bool cppTestScenario()
{
	Scenario* pScenario1 = new SomeScenario();
	pScenario1->run(SHOW_EVERYTHING);
	if (!pScenario1->isCanceled())
	{
		cout << "Scenario should have been canceled" << endl;
		return false;
	}
	else if (pScenario1->didPass())
	{
		cout << "Scenario is passing when it shouldn't" << endl;
		return false;
	}
	pScenario1->print(SHOW_EVERYTHING);
	delete pScenario1;

	Scenario* pScenario2 = new AnotherScenario();
	pScenario2->run(SHOW_EVERYTHING);
	if (pScenario2->isCanceled())
	{
		cout << "Scenario was unduly canceled" << endl;
		return false;
	}
	else if (!pScenario2->didPass())
	{
		cout << "Scenario failed when it should have passed" << endl;
		return false;
	}
	pScenario2->print(SHOW_EVERYTHING);
	delete pScenario2;

	return true;
}
