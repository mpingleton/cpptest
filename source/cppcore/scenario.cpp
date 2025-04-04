//-----------------------------------------------------------------------------
// CPPTEST
//
// cppcore/scenario.cpp
//
// Methods for the Scenario class.
//
// Created	: 3 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"

namespace cpptest
{
	Scenario::Scenario()
	{
		status = SCENARIO_STATUS_PENDING;
		desc = "";
		results.clear();
	}

	Scenario::Scenario(string inputDesc)
	{
		status = SCENARIO_STATUS_PENDING;
		desc = inputDesc;
		results.clear();
	}

	Scenario::~Scenario()
	{
		status = SCENARIO_STATUS_PENDING;
		desc = "";

		for (int i = 0; i < results.size(); i++)
			delete results[i];
		results.clear();
	}

	void Scenario::test()
	{
		cancel();
	}

	void Scenario::cancel()
	{
		status = SCENARIO_STATUS_CANCELED;
	}

	bool Scenario::isCanceled()
	{
		if (status == SCENARIO_STATUS_CANCELED)
			return true;
		else
			return false;
	}

	void Scenario::run()
	{
		if (status == SCENARIO_STATUS_PENDING)
		{
			status = SCENARIO_STATUS_RUNNING;
			test();
			if (status == SCENARIO_STATUS_RUNNING)
				status = SCENARIO_STATUS_COMPLETE;
		}
	}

	bool Scenario::didPass()
	{
		if (status == SCENARIO_STATUS_COMPLETE)
		{
			int numberPassed = 0, numberFailed = 0;
			for (int i = 0; i < results.size(); i++)
			{
				if (results[i]->didPass())
					numberPassed++;
				else
					numberFailed++;
			}

			if (numberPassed > 0 && numberFailed == 0)
				return true;
		}

		return false;
	}

	void Scenario::print()
	{
		if (status == SCENARIO_STATUS_RUNNING)
			cout << "[      ]\t";
		else if (status == SCENARIO_STATUS_CANCELED)
			cout << "[CANCEL]\t";
		else if (status == SCENARIO_STATUS_COMPLETE)
		{
			if (didPass()) cout << "[  OK  ]\t";
			else cout << "[ FAIL ]\t";
		}
		else
			cout << "[  --  ]\t";

		cout << desc;

		if (status == SCENARIO_STATUS_RUNNING)
			cout << "\r";
		else
		{
			cout << endl;
			for (int i = 0; i < results.size(); i++)
				results[i]->print();

			for (int i = 0; i < 80; i++) cout << "-";
			cout << endl;
		}
	}
};