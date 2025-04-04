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
	void Scenario::expect(bool shouldBeTrue)
	{
		int a = 0;
		if (shouldBeTrue) a = 1;

		ExpectationResultInt* pR = new ExpectationResultInt(0, 0, a, 1, shouldBeTrue);
		results.push_back(pR);

		if (!shouldBeTrue) cancel();
	}

	void Scenario::expectPointerNull(void* pointer)
	{
		bool p = pointer == 0;
		ExpectationResultPointer* pR = new ExpectationResultPointer(0, 0, pointer, 0, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectPointerInitialized(void* pointer)
	{
		bool p = pointer != 0;
		ExpectationResultPointer* pR = new ExpectationResultPointer(0, 0, pointer, 0, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(void* pActual, void* pExpected)
	{
		bool p = pActual == pExpected;
		ExpectationResultPointer* pR = new ExpectationResultPointer(0, 0, pActual, pExpected, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(int actual, int expected)
	{
		bool p = actual == expected;
		ExpectationResultInt* pR = new ExpectationResultInt(0, 0, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(float actual, float expected)
	{
		bool p = actual == expected;
		ExpectationResultFloat* pR = new ExpectationResultFloat(0, 0, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();
	}

	void Scenario::expectToEqual(double actual, double expected)
	{
		bool p = actual == expected;
		ExpectationResultDouble* pR = new ExpectationResultDouble(0, 0, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();
	}
};