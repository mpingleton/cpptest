//-----------------------------------------------------------------------------
// CPPTEST
//
// cpptest.hpp
//
// Primary header file for the CPPTEST library's C++ testing framework.
// Contains initial definitions for the Runner, Section, Scenario.
//
// Created	: 18 November 2024
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#ifndef CPPTEST_HPP
#define CPPTEST_HPP

#include "./cpptest.h"

#include <iostream>
#include <vector>

namespace cpptest
{
	using namespace std;

	class ExpectationResult
	{
	protected:
		int index;
		int expectationId;
		bool passing;

	public:
		ExpectationResult();
		virtual ~ExpectationResult();

		bool didPass();
		virtual void print();
	};

	class ExpectationResultPointer : public ExpectationResult
	{
		void* pActual;
		void* pExpected;

	public:
		ExpectationResultPointer(int i, int id, void* pA, void* pE, bool pass);
		~ExpectationResultPointer();

		void print();
	};

	class ExpectationResultInt : public ExpectationResult
	{
		int actual;
		int expected;

	public:
		ExpectationResultInt(int i, int id, int a, int e, bool pass);
		~ExpectationResultInt();

		void print();
	};

	class ExpectationResultFloat : public ExpectationResult
	{
		float actual;
		float expected;

	public:
		ExpectationResultFloat(int i, int id, float a, float e, bool pass);
		~ExpectationResultFloat();

		void print();
	};

	class ExpectationResultDouble : public ExpectationResult
	{
		double actual;
		double expected;

	public:
		ExpectationResultDouble(int i, int id, double a, double e, bool pass);
		~ExpectationResultDouble();

		void print();
	};

	class Scenario
	{
		char status;
		string desc;
		vector<ExpectationResult*> results;

	protected:
		void cancel();

	public:
		Scenario();
		Scenario(string inputDesc);
		virtual ~Scenario();

		virtual void test();
		bool isCanceled();

		void expect(bool shouldBeTrue);
		void expectPointerNull(void* pointer);
		void expectPointerInitialized(void* pointer);
		void expectToEqual(void* pActual, void* pExpected);
		void expectToEqual(int actual, int expected);
		void expectToEqual(float actual, float expected);
		void expectToEqual(double actual, double expected);

		void run();
		bool didPass();
		void print();
	};

	class Section
	{
		string desc;
		vector<Scenario*> scenarios;

	public:
		Section();
		Section(string inputDesc);
		virtual ~Section();

		void run();
		bool didPass();
		void print();
	};

	class Runner
	{
		vector<Section*> sections;

	public:
		Runner();
		~Runner();

		void run(bool show);
		bool didPass();
		void print();
	};
};

#endif