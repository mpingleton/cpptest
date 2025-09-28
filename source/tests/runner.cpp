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

		expectToEqual("TEST", "1", 10, 10);
		expectToEqual("TEST", "1", 3, 2);
		expectToEqual("TEST", "2", 3.14f, 3.14f);
		expectToEqual("TEST", "3", "Hello world!", "Hello world!");
		expectToEqual("TEST", "3", "Hello world", "Hello world!");

		if (isCanceled()) return;

		expectToEqual("TEST", "3", 1.2, 1.2);
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

		expectToEqual("", "1", 10, 10);
		expectToEqual("", "1", 2, 2);
		expectToEqual("", "2", 3.14f, 3.14f);

		if (isCanceled()) return;

		expectToEqual("", "3", 1.2, 1.2);

		int a = 0;
		int* b = 0;
		int* c = &a;
		expectPointerNull("", "4", b);
		expectPointerInitialized("", "5", c);
		expectToEqual("", "6", c, &a);
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

		expectToEqual("", "1", 1, 1);
		expectToEqual("", "2", 2, 2);
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

		for (int i = 0; i < 10000; i++)
		{
			expectToEqual("", "1", 3.14f, 3.14f);
			expectToEqual("", "2", 1.4, 1.4);
		}
	}
};

class FineOneMoreScenario1 : public Scenario
{
public:
	FineOneMoreScenario1() : Scenario("Test 5")
	{}

	~FineOneMoreScenario1()
	{}

	void test()
	{
		sleep(2);

		for (int i = 0; i < 10000; i++)
		{
			expectToEqual("", "1", 3.14f, 3.14f);
			expectToEqual("", "2", 1.4, 1.4);
		}
	}
};

class FineOneMoreScenario2 : public Scenario
{
public:
	FineOneMoreScenario2() : Scenario("Test 6")
	{}

	~FineOneMoreScenario2()
	{}

	void test()
	{
		sleep(2);

		for (int i = 0; i < 10000; i++)
		{
			expectToEqual("", "1", 3.14f, 3.14f);
			expectToEqual("", "2", 1.4, 1.4);

			if (i == 4000) throw runtime_error("This is a test exception which should be caught by the base class Scenario at i = 4000");
		}
	}
};

class FirstStressTest : public Scenario
{
	int r = 0;
	int suO = 0, suE = 0;
	int tdO = 0, tdE = 0;

public:
	FirstStressTest() : Scenario("Stress Test Scenario 1")
	{}

	~FirstStressTest()
	{}

	void setupOnce()
	{
		suO++;
	}

	void teardownOnce()
	{
		tdO++;
	}

	void setupEach()
	{
		suE++;
	}

	void teardownEach()
	{
		tdE++;
	}

	bool shouldRepeat()
	{
		if (r >= 10)
			return false;
		
		r++;
		return true;
	}

	void test()
	{
		sleep(1);

		expectToEqual("", "setupOnce called", suO, 1);
		expectToEqual("", "teardownOnce called", tdO, 0);

		expectToEqual("", "setupEach", suE, r + 1);
		expectToEqual("", "teardownEach", tdE, r);
	}
};

class SecondStressTest : public Scenario
{
	int r = 0, t = 0;
	int suO = 0, suE = 0;
	int tdO = 0, tdE = 0;

public:
	SecondStressTest() : Scenario("Stress Test Scenario 2")
	{}

	~SecondStressTest()
	{}

	void setupOnce()
	{
		suO++;
	}

	void teardownOnce()
	{
		tdO++;
	}

	void setupEach()
	{
		suE++;
	}

	void teardownEach()
	{
		tdE++;
	}

	bool shouldRepeat()
	{
		if (r >= 10000)
			return false;
		
		r++;
		return true;
	}
	
	void test()
	{
		t++;

		if (r < 10000) return;

		expectToEqual("", "r", r, t - 1);

		expectToEqual("", "setupOnce called", suO, 1);
		expectToEqual("", "teardownOnce called", tdO, 0);

		expectToEqual("", "setupEach", suE, r + 1);
		expectToEqual("", "teardownEach", tdE, r);
	}
};

class ThirdStressTest : public Scenario
{
	int r = 0, t = 0;
	int suO = 0, suE = 0;
	int tdO = 0, tdE = 0;

public:
	ThirdStressTest() : Scenario("Stress Test Scenario 3")
	{}

	~ThirdStressTest()
	{}

	void setupOnce()
	{
		suO++;
	}

	void teardownOnce()
	{
		tdO++;
	}

	void setupEach()
	{
		suE++;
	}

	void teardownEach()
	{
		tdE++;
	}

	bool shouldRepeat()
	{
		if (r >= 10000)
			return false;
		
		r++;
		return true;
	}
	
	void test()
	{
		t++;
		expectToEqual("", "r", r, t - 1);

		expectToEqual("", "setupOnce called", suO, 1);
		expectToEqual("", "teardownOnce called", tdO, 0);

		expectToEqual("", "setupEach", suE, r + 1);
		expectToEqual("", "teardownEach", tdE, r);
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

class SectionFour1 : public Section
{
public:
	SectionFour1() : Section("Section Four")
	{
		add(new FineOneMoreScenario1());
	}
};

class SectionFive1 : public Section
{
public:
	SectionFive1() : Section("Section Five")
	{
		add(new FineOneMoreScenario2());
	}
};

class SectionThr1 : public Section
{
public:
	SectionThr1() : Section("Section Three")
	{
		add(new SomeOtherScenario1());
		add(new YetOtherScenario1());
		add(new SectionFour1());
	}
};

class StressTestSectionA : public Section
{
public:
	StressTestSectionA() : Section("Stress Testing A")
	{
		add(new FirstStressTest());
	}
};

class StressTestSectionB : public Section
{
public:
	StressTestSectionB() : Section("Stress Testing B")
	{
		add(new SecondStressTest());
		add(new ThirdStressTest());
	}
};

bool cppTestRunner()
{
	Runner runner1 = Runner();
	runner1.add(new SectionOne1());
	runner1.add(new SectionFive1());
	runner1.add(new SectionTwo1());	

	runner1.run(SHOW_EVERYTHING);
	if (runner1.didPass())
	{
		cout << "Tests should not have passed" << endl;
		return false;
	}

	Runner runner2 = Runner();
	runner2.add(new SectionThr1());

	runner2.run(SHOW_EVERYTHING);
	if (!runner2.didPass())
	{
		cout << "Tests should have passed" << endl;
		return false;
	}

	runner1.print(SHOW_EVERYTHING);
	runner2.print(SHOW_EVERYTHING);

	Runner runner3 = Runner();
	runner3.add(new StressTestSectionA());
	runner3.add(new StressTestSectionB());

	runner3.run(SHOW_EVERYTHING);
	if (!runner3.didPass())
	{
		cout << "Tests should have passed" << endl;
		return false;
	}

	runner3.print(SHOW_ONLY_FAILING);

	return true;
}
