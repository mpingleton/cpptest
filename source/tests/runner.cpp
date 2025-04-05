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

#include <unistd.h>
#include <iostream>

using namespace std;
using namespace cpptest;

class SomeScenario1 : public Scenario
{
public:
	SomeScenario1() : Scenario("Test 1")
	{}

	~SomeScenario1()
	{}

	void test()
	{
		sleep(3);

		expectToEqual(1, 10, 10);
		expectToEqual(1, 3, 2);
		expectToEqual(2, 3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual(3, 1.2, 1.2);
	}
};

class AnotherScenario1 : public Scenario
{
public:
	AnotherScenario1() : Scenario("Test 2")
	{}

	~AnotherScenario1()
	{}

	void test()
	{
		sleep(3);

		expectToEqual(1, 10, 10);
		expectToEqual(1, 2, 2);
		expectToEqual(2, 3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual(3, 1.2, 1.2);

		int a = 0;
		int* b = 0;
		int* c = &a;
		expectPointerNull(4, b);
		expectPointerInitialized(5, c);
		expectToEqual(6, c, &a);
	}
};

class SomeOtherScenario1 : public Scenario
{
public:
	SomeOtherScenario1() : Scenario("Test 3")
	{}

	~SomeOtherScenario1()
	{}

	void test()
	{
		sleep(3);

		expectToEqual(1, 1, 1);
		expectToEqual(2, 2, 2);
	}
};

class YetOtherScenario1 : public Scenario
{
public:
	YetOtherScenario1() : Scenario("Test 4")
	{}

	~YetOtherScenario1()
	{}

	void test()
	{
		sleep(3);

		expectToEqual(1, 3.14f, 3.14f);
		expectToEqual(2, 1.4, 1.4);
	}
};

class SectionOne1 : public Section
{
public:
	SectionOne1() : Section("Section One")
	{
		add(new SomeScenario1());
	}
};

class SectionTwo1 : public Section
{
public:
	SectionTwo1() : Section("Section Two")
	{
		add(new AnotherScenario1());
	}
};

class SectionThr1 : public Section
{
public:
	SectionThr1() : Section("Section Three")
	{
		add(new SomeOtherScenario1());
		add(new YetOtherScenario1());
	}
};

bool cppTestRunner()
{
	Runner runner1 = Runner();
	runner1.add(new SectionOne1());
	runner1.add(new SectionTwo1());

	runner1.run(true);
	if (runner1.didPass())
	{
		cout << "Tests should not have passed" << endl;
		return false;
	}

	Runner runner2 = Runner();
	runner2.add(new SectionThr1());

	runner2.run(true);
	if (!runner2.didPass())
	{
		cout << "Tests should have passed" << endl;
		return false;
	}

	runner1.print();
	runner2.print();

	return true;
}
