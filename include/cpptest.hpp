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
		string id;
		char comparison;
		bool passing;

	public:
		ExpectationResult* pNext;

		ExpectationResult();
		virtual ~ExpectationResult();

		string getId();
		bool didPass();
		virtual void print();
	};

	class ExpectationResultPointer : public ExpectationResult
	{
		void* pActual;
		void* pExpected;

	public:
		ExpectationResultPointer(int i, string inputId, void* pA, void* pE, bool pass);
		~ExpectationResultPointer();

		void print();
	};

	class ExpectationResultInt : public ExpectationResult
	{
		int actual;
		int expected;

	public:
		ExpectationResultInt(int i, string inputId, int a, int e, bool pass);
		~ExpectationResultInt();

		void print();
	};

	class ExpectationResultFloat : public ExpectationResult
	{
		float actual;
		float expected;

	public:
		ExpectationResultFloat(int i, string inputId, float a, float e, bool pass);
		~ExpectationResultFloat();

		void print();
	};

	class ExpectationResultDouble : public ExpectationResult
	{
		double actual;
		double expected;

	public:
		ExpectationResultDouble(int i, string inputId, double a, double e, bool pass);
		~ExpectationResultDouble();

		void print();
	};

	class Scenario
	{
		char status;
		string desc;
		ExpectationResult* pFirstResult;
		ExpectationResult* pLastResult;

	protected:
		virtual void test();
		void cancel();

	public:
		Scenario();
		Scenario(string inputDesc);
		virtual ~Scenario();

		bool isCanceled();

		bool expect(string parentId, string inputId, bool shouldBeTrue);
		bool expectPointerNull(string parentId, string inputId, void* pointer);
		bool expectPointerInitialized(string parentId, string inputId, void* pointer);
		bool expectToEqual(string parentId, string inputId, void* pActual, void* pExpected);
		bool expectToEqual(string parentId, string inputId, int actual, int expected);
		bool expectToEqual(string parentId, string inputId, float actual, float expected);
		bool expectToEqual(string parentId, string inputId, double actual, double expected);

		void addResult(ExpectationResult result);
		void run(char show);
		bool didPass();
		void print(char show);
	};

	class Section
	{
		string desc;
		vector<Scenario*> scenarios;
		vector<Section*> subsections; // TODO

	protected:
		void add(Scenario* pScenario);
		void add(Section* pSection);

	public:
		Section();
		Section(string inputDesc);
		virtual ~Section();

		void run(char show);
		bool didPass();
		void print(char show);
	};

	class Runner
	{
		vector<Section*> sections;

	public:
		Runner();
		~Runner();

		void add(Section* pSection);
		void run(char show);
		bool didPass();
		void print(char show);
	};
};

#endif
