//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/section.cpp
//
// Tests for sections.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"
#include "../../include/tests.hpp"

#include <iostream>

using namespace std;
using namespace cpptest;

class Scenario1 : public Scenario
{
public:
	Scenario1() : Scenario("Test 1")
	{}

	~Scenario1()
	{}

	void test()
	{
		expectToEqual("", "1", 10, 10);
		expectToEqual("", "2", 3.14f, 3.14f);
	}
};

class Scenario2 : public Scenario
{
public:
	Scenario2() : Scenario("Test 2")
	{}

	~Scenario2()
	{}

	void test()
	{
		expectToEqual("", "1", 10, 10);
		expectToEqual("", "2", 3.14f, 3.0f);
	}
};

class Scenario3 : public Scenario
{
public:
	Scenario3() : Scenario("Test 3")
	{}

	~Scenario3()
	{}

	void test()
	{
		expectToEqual("", "1", 10, 12);
		expectToEqual("", "1", 3.14f, 3.14f);
	}
};

class Scenario4 : public Scenario
{
public:
	Scenario4() : Scenario("Test 4")
	{}

	~Scenario4()
	{}

	void test()
	{
		expectToEqual("", "1", 10, 10);
		expectToEqual("", "1", 3.14f, 3.14f);
	}
};

class SectionOne : public Section
{
public:
	SectionOne() : Section("Section One")
	{
		add(new Scenario1());
		add(new Scenario2());
	}
};

class SectionTwo : public Section
{
public:
	SectionTwo() : Section("Section Two")
	{
		add(new Scenario3());
	}
};

class SectionThree : public Section
{
public:
	SectionThree() : Section("Section Three")
	{
		add(new Scenario4());
	}
};

bool cppTestSection()
{
	Section* pOne = new SectionOne();
	Section* pTwo = new SectionTwo();
	Section* pThree = new SectionThree();

	pOne->print();
	pTwo->print();
	pThree->print();

	pOne->run(true);
	pTwo->run(true);
	pThree->run(true);

	pOne->print();
	pTwo->print();
	pThree->print();

	if (pOne->didPass())
	{
		cout << "Section one should not have passed" << endl;
		return false;
	}
	else if (pTwo->didPass())
	{
		cout << "Section two should not have passed" << endl;
		return false;
	}
	else if (!pThree->didPass())
	{
		cout << "Section three should have passed" << endl;
		return false;
	}

	delete pOne;
	delete pTwo;
	delete pThree;
	return true;
}
