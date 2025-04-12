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
		pFirstResult = 0;
		pLastResult = 0;
	}

	Scenario::Scenario(string inputDesc)
	{
		status = SCENARIO_STATUS_PENDING;
		desc = inputDesc;
		pFirstResult = 0;
		pLastResult = 0;
	}

	Scenario::~Scenario()
	{
		status = SCENARIO_STATUS_PENDING;
		desc = "";

		ExpectationResult* pCurrent = pFirstResult;
		while (pCurrent)
		{
			ExpectationResult* pNext = pCurrent->pNext;
			delete pCurrent;
			pCurrent = pNext;
		}

		pFirstResult = 0;
		pLastResult = 0;
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

	void Scenario::addResult(ExpectationResult* pResult)
	{
		if (pFirstResult)
		{
			ExpectationResult* pCurrent = pFirstResult;
			while (pCurrent)
			{
				if (pCurrent->getId().compare(pResult->getId()) == 0)
					pResult->index++;

				pCurrent = pCurrent->pNext;
			}

			pLastResult->pNext = pResult;
		}
		else
			pFirstResult = pResult;

		pLastResult = pResult;
	}

	void Scenario::run(char show)
	{
		if (status == SCENARIO_STATUS_PENDING)
		{
			status = SCENARIO_STATUS_RUNNING;

			if (show)
			{
				if (show > SHOW_NOTHING) print(show);
				fflush(0);
			}

			test();
			if (status == SCENARIO_STATUS_RUNNING)
				status = SCENARIO_STATUS_COMPLETE;

			if (show > SHOW_NOTHING) print(show);
		}
	}

	bool Scenario::didPass()
	{
		if (status == SCENARIO_STATUS_COMPLETE)
		{
			int numberPassed = 0, numberFailed = 0;
			ExpectationResult* pR = pFirstResult;
			while (pR != 0)
			{
				if (pR->didPass())
					numberPassed++;
				else
					numberFailed++;

				pR = pR->pNext;
			}

			if (numberPassed > 0 && numberFailed == 0)
				return true;
		}

		return false;
	}

	void Scenario::print(char show)
	{
		cout << " ";
		if (status == SCENARIO_STATUS_RUNNING)
			cout << "[ >>>> ]";
		else if (status == SCENARIO_STATUS_CANCELED)
			cout << "[CANCEL]";
		else if (status == SCENARIO_STATUS_COMPLETE)
		{
			if (didPass()) cout << "[  OK  ]";
			else cout << "[ FAIL ]";
		}
		else
			cout << "[  --  ]";

		cout << "\t" << desc;

		if (status == SCENARIO_STATUS_RUNNING)
			cout << "\r";
		else
		{
			cout << endl;

			if (show == SHOW_EVERYTHING)
			{
				ExpectationResult* pR = pFirstResult;
				while (pR)
				{
					pR->print();
					pR = pR->pNext;
				}
			}
			else if (show == SHOW_ONLY_FAILING)
			{
				ExpectationResult* pR = pFirstResult;
				while (pR)
				{
					if (!pR->didPass())
						pR->print();

					pR = pR->pNext;
				}
			}
		}
	}
};
