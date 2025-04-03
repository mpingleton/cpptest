//-----------------------------------------------------------------------------
// CPPTEST
//
// tests/expectation_result.cpp
//
// Tests for expectation results.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"
#include "../../include/tests.hpp"

#include <iostream>

using namespace std;
using namespace cpptest;

bool cppTestExpectationResult()
{
	ExpectationResultInt result1 = ExpectationResultInt(0, 1, 2, 2, true);
	ExpectationResultDouble result2 = ExpectationResultDouble(1, 2, 2.0, 3.0, false);
	ExpectationResultDouble result3 = ExpectationResultDouble(2, 3, 3.0, 3.0, true);

	result1.print();
	result2.print();
	result3.print();

	if (!result1.didPass())
	{
		cout << "\tresult1 is not passing" << endl;
		return false;
	}
	else if (result2.didPass())
	{
		cout << "\tresult2 is passing" << endl;
		return false;
	}
	else if (!result3.didPass())
	{
		cout << "\tresult3 is not passing" << endl;
		return false;
	}

	return true;
}