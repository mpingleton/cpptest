//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/runner.cpp
//
// Tests for runners.
//
// Created	: 5 April 2025
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
		expectToEqual(10, 10);
		expectToEqual(3, 2);
		expectToEqual(3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual(1.2, 1.2);
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
		expectToEqual(10, 10);
		expectToEqual(2, 2);
		expectToEqual(3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual(1.2, 1.2);

		int a = 0;
		int* b = 0;
		int* c = &a;
		expectPointerNull(b);
		expectPointerInitialized(c);
		expectToEqual(c, &a);
	}
};

class SomeOtherScenario : public Scenario
{
public:
	SomeOtherScenario() : Scenario("Test 3")
	{}

	~SomeOtherScenario()
	{}

	void test()
	{
		expectToEqual(1, 1);
		expectToEqual(2, 2);
	}
};

class YetOtherScenario : public Scenario
{
public:
	YetOtherScenario() : Scenario("Test 4")
	{}

	~YetOtherScenario()
	{}

	void test()
	{
		expectToEqual(3.14f, 3.14f);
		expectToEqual(1.4, 1.4);
	}
};

class SectionOne : public Section
{
public:
	SectionOne() : Section("Section One")
	{
		add(new SomeScenario());
	}
};

class SectionTwo : public Section
{
public:
	SectionTwo() : Section("Section Two")
	{
		add(new AnotherScenario());
	}
};

class SectionThr : public Section
{
public:
	SectionThr() : Section("Section Three")
	{
		add(new SomeOtherScenario());
		add(new YetOtherScenario());
	}
};

bool cppTestRunner()
{
	Runner runner1 = Runner();
	runner1.add(new SectionOne());
	runner1.add(new SectionTwo());

	runner1.print();
	runner1.run(true);
	if (runner1.didPass())
	{
		cout << "Tests should not have passed" << endl;
		return false;
	}

	Runner runner2 = Runner();
	runner2.add(new SectionThr());

	runner2.print();
	runner2.run(true);
	if (!runner2.didPass())
	{
		cout << "Tests should have passed" << endl;
		return false;
	}

	return true;
}
