//-----------------------------------------------------------------------------
// CPPTEST
//
// cpptest.hpp
//
// Primary inlcude header file for the CPPTEST library.
// Contains initial defintions for the Runner, Suite, Case,
// and Assertion classes.
//
// Created	: 18 November 2024
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#ifndef CPPTEST_HPP
#define CPPTEST_HPP

#include <iostream>
#include <vector>

namespace cpptest
{
	using namespace std;

	class Assertion
	{
		string d;
		string e, a;
		bool p;

	public:
		Assertion();
		~Assertion();

		bool isComplete();
		bool isPassing();
		string toString(int columnWidth);
	};

	class Case
	{
		string d;
		bool w;
		vector<Assertion> vA;

	protected:
		void expect(string description, bool condition);

	public:
		Case();
		Case(string description);
		~Case();

		void skip();
		bool isPassing();
		int numberTotalAssertions();
		int numberFailingAssertions();
		string toString(int columnWidth, bool verbose);
	};

	class Suite
	{
		vector<Case*> vpC;

	protected:
		void add(Case* pCase);

	public:
		Suite();
		~Suite();

		string toString(int columnWidth);
	};

	class Runner
	{
		vector<Suite> vS;

	public:
		Runner();
		~Runner();

		void run();
		int numberTotalSuites();
		string toString(int columnWidth, bool verbose);
	};
};

#endif