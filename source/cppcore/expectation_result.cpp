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
	case EXPECTATION_NOT_EQUAL: return "!";
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
		comparison = 0;
		passing = false;
		pNext = 0;
	}

	ExpectationResult::ExpectationResult(string inputId, char c, bool pass)
	{
		index = 0;
		id = inputId;
		comparison = c;
		passing = pass;
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

	ExpectationResultPointer::ExpectationResultPointer(string inputId, void* pA, void* pE, char c, bool pass) : ExpectationResult(inputId, c, pass)
	{
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

	ExpectationResultInt::ExpectationResultInt(string inputId, int a, int e, char c, bool pass) : ExpectationResult(inputId, c, pass)
	{
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

	ExpectationResultFloat::ExpectationResultFloat(string inputId, float a, float e, char c, bool pass) : ExpectationResult(inputId, c, pass)
	{
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

	ExpectationResultDouble::ExpectationResultDouble(string inputId, double a, double e, char c, bool pass) : ExpectationResult(inputId, c, pass)
	{
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
