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
		string id;
		char comparison;
		bool passing;

	public:
		int index;
		ExpectationResult* pNext;

		ExpectationResult();
		ExpectationResult(string inputId, char c, bool pass);
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
		ExpectationResultPointer(string inputId, void* pA, void* pE, char c, bool pass);
		~ExpectationResultPointer();

		void print();
	};

	class ExpectationResultInt : public ExpectationResult
	{
		int actual;
		int expected;

	public:
		ExpectationResultInt(string inputId, int a, int e, char c, bool pass);
		~ExpectationResultInt();

		void print();
	};

	class ExpectationResultFloat : public ExpectationResult
	{
		float actual;
		float expected;

	public:
		ExpectationResultFloat(string inputId, float a, float e, char c, bool pass);
		~ExpectationResultFloat();

		void print();
	};

	class ExpectationResultDouble : public ExpectationResult
	{
		double actual;
		double expected;

	public:
		ExpectationResultDouble(string inputId, double a, double e, char c, bool pass);
		~ExpectationResultDouble();

		void print();
	};

	class Scenario
	{
		char status;
		string desc;
		ExpectationResult* pFirstResult;
		ExpectationResult* pLastResult;
		bool didExc;
		string strExc;

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

		void addResult(ExpectationResult* pResult);
		void run(char show);
		bool didPass();
		void print(char show, const string& startLine);
	};

	class Section
	{
		string desc;
		vector<Scenario*> scenarios;
		vector<Section*> subsections;

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

		const string& getDesc();
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

	void coutProgress(const string& caption, int numerator, int denominator);
};

#endif
