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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		int a = 0;
		if (shouldBeTrue) a = 1;

		ExpectationResultInt* pR = new ExpectationResultInt(i, id, a, 1, shouldBeTrue);
		results.push_back(pR);

		if (!shouldBeTrue) cancel();

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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		bool p = pointer == 0;
		ExpectationResultPointer* pR = new ExpectationResultPointer(i, id, pointer, 0, p);
		results.push_back(pR);

		if (!p) cancel();

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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		bool p = pointer != 0;
		ExpectationResultPointer* pR = new ExpectationResultPointer(i, id, pointer, 0, p);
		results.push_back(pR);

		if (!p) cancel();

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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		bool p = pActual == pExpected;
		ExpectationResultPointer* pR = new ExpectationResultPointer(i, id, pActual, pExpected, p);
		results.push_back(pR);

		if (!p) cancel();

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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		bool p = actual == expected;
		ExpectationResultInt* pR = new ExpectationResultInt(i, id, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();

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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		bool p = actual == expected;
		ExpectationResultFloat* pR = new ExpectationResultFloat(i, id, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();

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

		int i = 0;
		for (int e = 0; e < results.size(); e++)
		{
			if (id.compare(results[e]->getId()) == 0) i++;
		}

		bool p = actual == expected;
		ExpectationResultDouble* pR = new ExpectationResultDouble(i, id, actual, expected, p);
		results.push_back(pR);

		if (!p) cancel();

		return p;
	}
};
