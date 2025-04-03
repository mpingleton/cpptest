//-----------------------------------------------------------------------------
// CPPTEST
//
// cppcore/expectation_result.cpp
//
// Methods for the ExpectationResult class and all its derivative classes.
//
// Created	: 2 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"

namespace cpptest
{
	ExpectationResult::ExpectationResult()
	{
		index = 0;
		expectationId = 0;
		passing = false;
	}

	ExpectationResult::~ExpectationResult()
	{
		index = 0;
		expectationId = 0;
		passing = false;
	}

	bool ExpectationResult::didPass()
	{
		return passing;
	}

	void ExpectationResult::print()
	{
		cout << '\t';
		if (didPass())
			cout << "[  OK  ]";
		else
			cout << "[ FAIL ]";

		cout << " (" << to_string(expectationId) << " - " << to_string(index) << ")\t";
	}

	ExpectationResultPointer::ExpectationResultPointer(int i, int id, void* pA, void* pE, bool pass) : ExpectationResult()
	{
		index = i;
		expectationId = id;
		passing = pass;
		pActual = pA;
		pExpected = pE;
	}

	ExpectationResultPointer::~ExpectationResultPointer()
	{
		pActual = 0;
		pExpected = 0;
	}

	void ExpectationResultPointer::print()
	{
		ExpectationResult::print();

		if (pActual == pExpected)
			cout << "Pointers Match" << endl;
		else
			cout << "Pointers Don't Match" << endl;
	}

	ExpectationResultInt::ExpectationResultInt(int i, int id, int a, int e, bool pass) : ExpectationResult()
	{
		index = i;
		expectationId = id;
		passing = pass;
		actual = a;
		expected = e;
	}

	ExpectationResultInt::~ExpectationResultInt()
	{
		actual = 0;
		expected = 0;
	}

	void ExpectationResultInt::print()
	{
		ExpectationResult::print();
		cout << "Actual: " << to_string(actual) << "\tExpected: " << to_string(expected) << endl;
	}

	ExpectationResultFloat::ExpectationResultFloat(int i, int id, float a, float e, bool pass) : ExpectationResult()
	{
		index = i;
		expectationId = id;
		passing = pass;
		actual = a;
		expected = e;
	}

	ExpectationResultFloat::~ExpectationResultFloat()
	{
		actual = 0.0f;
		expected = 0.0f;
	}

	void ExpectationResultFloat::print()
	{
		ExpectationResult::print();
		cout << "Actual: " << to_string(actual) << "\tExpected: " << to_string(expected) << endl;
	}

	ExpectationResultDouble::ExpectationResultDouble(int i, int id, double a, double e, bool pass) : ExpectationResult()
	{
		index = i;
		expectationId = id;
		passing = pass;
		actual = a;
		expected = e;
	}

	ExpectationResultDouble::~ExpectationResultDouble()
	{
		actual = 0.0;
		expected = 0.0;
	}

	void ExpectationResultDouble::print()
	{
		ExpectationResult::print();
		cout << "Actual: " << to_string(actual) << "\tExpected: " << to_string(expected) << endl;
	}
};