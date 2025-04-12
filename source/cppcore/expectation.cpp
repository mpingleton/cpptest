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

#include <string>

namespace cpptest
{
	bool Scenario::expect(string parentId, string inputId, bool shouldBeTrue)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		int a = 0;
		if (shouldBeTrue) a = 1;
		else cancel();

		addResult(new ExpectationResultInt(id, a, 1, EXPECTATION_EQUAL, shouldBeTrue));
		return shouldBeTrue;
	}

	bool Scenario::expectPointerNull(string parentId, string inputId, void* pointer)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		bool p = pointer == 0;
		if (!p) cancel();

		addResult(new ExpectationResultPointer(id, pointer, 0, EXPECTATION_EQUAL, p));
		return p;
	}

	bool Scenario::expectPointerInitialized(string parentId, string inputId, void* pointer)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		bool p = pointer != 0;
		if (!p) cancel();

		addResult(new ExpectationResultPointer(id, pointer, 0, EXPECTATION_NOT_EQUAL, p));
		return p;
	}

	bool Scenario::expectToEqual(string parentId, string inputId, void* pActual, void* pExpected)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		bool p = pActual == pExpected;
		if (!p) cancel();

		addResult(new ExpectationResultPointer(id, pActual, pExpected, EXPECTATION_EQUAL, p));
		return p;
	}

	bool Scenario::expectToEqual(string parentId, string inputId, int actual, int expected)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		bool p = actual == expected;
		if (!p) cancel();

		addResult(new ExpectationResultInt(id, actual, expected, EXPECTATION_EQUAL, p));
		return p;
	}

	bool Scenario::expectToEqual(string parentId, string inputId, float actual, float expected)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		bool p = (actual >= expected - 0.1f) && (actual <= expected + 0.1f);
		if (!p) cancel();

		addResult(new ExpectationResultFloat(id, actual, expected, EXPECTATION_EQUAL, p));
		return p;
	}

	bool Scenario::expectToEqual(string parentId, string inputId, double actual, double expected)
	{
		string id = "";
		if (!parentId.empty())
		{
			id.append(parentId);
			id.append("\\");
		}
		id.append(inputId);

		bool p = (actual >= expected - 0.1) && (actual <= expected + 0.1);
		if (!p) cancel();

		addResult(new ExpectationResultDouble(id, actual, expected, EXPECTATION_EQUAL, p));
		return p;
	}
};
