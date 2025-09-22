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

#include <string.h>

namespace cpptest
{
	Scenario::Scenario()
	{
		status = SCENARIO_STATUS_PENDING;
		desc = "";
		pFirstResult = 0;
		pLastResult = 0;
		didExc = false;
		loops = 0;
	}

	Scenario::Scenario(string inputDesc)
	{
		status = SCENARIO_STATUS_PENDING;
		desc = inputDesc;
		pFirstResult = 0;
		pLastResult = 0;
		didExc = false;
		loops = 0;
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
		didExc = false;
		loops = 0;
	}

	void Scenario::setupOnce()
	{}

	void Scenario::setupEach()
	{}

	void Scenario::teardownOnce()
	{}

	void Scenario::teardownEach()
	{}

	bool Scenario::shouldRepeat()
	{
		return false;
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
				if (strcmp(pCurrent->getId().c_str(), pResult->getId().c_str()) == 0)
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
				if (show > SHOW_NOTHING)
				{
					print(show, "");
					cout << "\t\t\t\t\t\t\t\t";
				}

				fflush(0);
			}

			try
			{
				setupOnce();

				do
				{
					setupEach();
					test();
					teardownEach();
					loops++;

					if (status != SCENARIO_STATUS_RUNNING) break;

					if (show)
					{
						if (show > SHOW_NOTHING)
						{
							cout << "\r\x1b[2K";
							print(show, "");
							cout << "\t\t\t\t\t\t\t\t";
						}

						fflush(0);
					}
				}
				while (shouldRepeat());

				teardownOnce();
			}
			catch (const exception& e)
			{
				cancel();
				didExc = true;
				strExc = e.what();
			}

			if (status == SCENARIO_STATUS_RUNNING)
				status = SCENARIO_STATUS_COMPLETE;
		}
	}

	bool Scenario::didPass()
	{
		if (status == SCENARIO_STATUS_COMPLETE)
		{
			if (didExc) return false;

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

	void Scenario::print(char show, const string& startLine)
	{
		if (status == SCENARIO_STATUS_RUNNING)
		{
			cout << "[ \x1b[34m\x1b[1m";

			if (loops > 0)
			{
				int ml = loops % 4;
				for (int i = 0; i < 4; i++)
				{
					if (i == ml) cout << "\x1b[93m>\x1b[34m";
					else cout << ">";
				}
			}
			else cout << ">>>>";

			cout << "\x1b[0m ]";
		}
		else if (status == SCENARIO_STATUS_CANCELED)
			cout << "[\x1b[91m\x1b[1mCANCEL\x1b[0m]";
		else if (status == SCENARIO_STATUS_COMPLETE)
		{
			if (didPass()) cout << "[  \x1b[32m\x1b[1mOK\x1b[0m  ]";
			else cout << "[ \x1b[91m\x1b[1mFAIL\x1b[0m ]";
		}
		else
			cout << "[  --  ]";

		cout << " " << desc;

		if (status != SCENARIO_STATUS_RUNNING)
		{
			cout << endl;

			if (show == SHOW_EVERYTHING)
			{
				ExpectationResult* pR = pFirstResult;
				while (pR)
				{
					cout << startLine;
					if (pR->pNext || didExc)
						cout << "   \x1b[90m|---\x1b[0m";
					else
						cout << "   \x1b[90m\\---\x1b[0m";

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
					{
						cout << startLine;
						if (pR->pNext || didExc)
							cout << "   \x1b[90m|---\x1b[0m";
						else
							cout << "   \x1b[90m\\---\x1b[0m";
				
						pR->print();
					}

					pR = pR->pNext;
				}
			}

			if (didExc && show >= SHOW_ONLY_FAILING)
			{
				cout << startLine;
				cout << "   \x1b[90m\\---\x1b[0m";
				cout << " [ \x1b[91m\x1b[1mFAIL\x1b[0m ]";
				cout << " \x1b[1mThrew Exception:\t\x1b[91m" << strExc;
				cout << "\x1b[0m" << endl;
			}
		}
	}
};
