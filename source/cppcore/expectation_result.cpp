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

#include <string>

using namespace std;

string comp(int comparison)
{
	switch (comparison)
	{
	case EXPECTATION_GREATER: return ">";
	case EXPECTATION_GREATER_OR_EQUAL: return ">=";
	case EXPECTATION_SMALLER: return "<";
	case EXPECTATION_SMALLER_OR_EQUAL: return "<=";
	default: return "";
	}
}

namespace cpptest
{
	ExpectationResult::ExpectationResult()
	{
		index = 0;
		id = "";
		comparison = EXPECTATION_EQUAL;
		passing = false;
		pNext = 0;
	}

	ExpectationResult::~ExpectationResult()
	{
		index = 0;
		id = "";
		comparison = 0;
		passing = false;
		pNext = 0;
	}

	string ExpectationResult::getId()
	{
		return id;
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

		cout << " (" << id << " - " << to_string(index) << ")\t";
	}

	ExpectationResultPointer::ExpectationResultPointer(int i, string inputId, void* pA, void* pE, bool pass) : ExpectationResult()
	{
		index = i;
		id = inputId;
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

	ExpectationResultInt::ExpectationResultInt(int i, string inputId, int a, int e, bool pass) : ExpectationResult()
	{
		index = i;
		id = inputId;
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
		cout << "Actual: " << to_string(actual) << "\tExpected: " << comp(comparison) << to_string(expected) << endl;
	}

	ExpectationResultFloat::ExpectationResultFloat(int i, string inputId, float a, float e, bool pass) : ExpectationResult()
	{
		index = i;
		id = inputId;
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
		cout << "Actual: " << to_string(actual) << "\tExpected: " << comp(comparison) << to_string(expected) << endl;
	}

	ExpectationResultDouble::ExpectationResultDouble(int i, string inputId, double a, double e, bool pass) : ExpectationResult()
	{
		index = i;
		id = inputId;
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
		cout << "Actual: " << to_string(actual) << "\tExpected: " << comp(comparison) << to_string(expected) << endl;
	}
};
