//-----------------------------------------------------------------------------
// CPPTEST
//
// cppcore/expectation.cpp
//
// Scenario class's expectation methods.
//
// Created	: 3 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"

namespace cpptest
{
	void Scenario::expect(int id, bool shouldBeTrue)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		int a = 0;
		if (shouldBeTrue) a = 1;

		ExpectationResultInt* pR = new ExpectationResultInt(i, id, a, 1, shouldBeTrue);
		results.push_back(pR);

		if (!shouldBeTrue) cancel();
	}

	void Scenario::expectPointerNull(int id, void* pointer)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		bool p = pointer == 0;
		ExpectationResultPointer* pR = new ExpectationResultPointer(i, id, pointer, 0, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectPointerInitialized(int id, void* pointer)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		bool p = pointer != 0;
		ExpectationResultPointer* pR = new ExpectationResultPointer(i, id, pointer, 0, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(int id, void* pActual, void* pExpected)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		bool p = pActual == pExpected;
		ExpectationResultPointer* pR = new ExpectationResultPointer(i, id, pActual, pExpected, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(int id, int actual, int expected)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		bool p = actual == expected;
		ExpectationResultInt* pR = new ExpectationResultInt(i, id, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(int id, float actual, float expected)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		bool p = actual == expected;
		ExpectationResultFloat* pR = new ExpectationResultFloat(i, id, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(int id, double actual, double expected)
	{
		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (results[e]->getId() == id) i++;
		}

		bool p = actual == expected;
		ExpectationResultDouble* pR = new ExpectationResultDouble(i, id, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();
	}
};
