//-----------------------------------------------------------------------------
// CPPTEST
//
// cppcore/section.c
//
// Functions for handling sections.
//
// Created	: 4 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"

#include <string.h>

namespace cpptest
{
	Section::Section()
	{
		desc = "";
		scenarios.clear();
		subsections.clear();
	}

	Section::Section(string inputDesc)
	{
		desc = inputDesc;
		scenarios.clear();
		subsections.clear();
	}

	Section::~Section()
	{
		desc = "";

		for (int i = 0; i < scenarios.size(); i++)
			delete scenarios[i];

		for (int i = 0; i < subsections.size(); i++)
			delete subsections[i];

		scenarios.clear();
		subsections.clear();
	}

	void Section::add(Scenario* pScenario)
	{
		scenarios.push_back(pScenario);
	}

	void Section::add(Section* pSection)
	{
		subsections.push_back(pSection);
	}

	void Section::run(char show)
	{
		for (int i = 0; i < scenarios.size(); i++)
		{
			if (show > SHOW_NOTHING)
			{
				printf("\x1b[2K");
				coutProgress("\x1b[34m\x1b[1mRunning Scenario\x1b[0m", i + 1, scenarios.size());

				printf("\n\x1b[2K");
			}

			scenarios[i]->run(show);

			if (show > SHOW_NOTHING) printf("\x1b[2K\x1b[1F\x1b[2K");
		}

		for (int i = 0; i < subsections.size(); i++)
			subsections[i]->run(show);

		fflush(0);
	}

	bool Section::didPass()
	{
		int numberPass = 0, numberFail = 0;
		for (int i = 0; i < scenarios.size(); i++)
		{
			if (scenarios[i]->didPass())
				numberPass++;
			else
				numberFail++;
		}

		for (int i = 0; i < subsections.size(); i++)
		{
			if (subsections[i]->didPass())
				numberPass++;
			else
				numberFail++;
		}

		if (numberPass > 0 && numberFail == 0)
			return true;

		return false;
	}

	void Section::print(char show, const string& startLine)
	{
		if (!startLine.empty()) cout << startLine;

		if (scenarios.empty() && subsections.empty())
			cout << "[      ]";
		else if (didPass())
			cout << "[  \x1b[32m\x1b[1mOK\x1b[0m  ]";
		else
			cout << "[ \x1b[91m\x1b[1mFAIL\x1b[0m ]";

		if (!desc.empty())
			cout << " " << desc << endl;
		else
			cout << endl;

		string startLineA = startLine;
		startLineA.append("    ");

		string startLineB = startLine;
		startLineB.append(" \x1b[30m| \x1b[0m ");

		string startLineC = startLine;
		startLineC.append(" \x1b[30m\\ \x1b[0m ");

		for (int i = 0; i < scenarios.size(); i++)
		{
			if (!startLine.empty()) cout << startLine;

			if (i == scenarios.size() - 1)
			{
				cout << " \x1b[30m\\-\x1b[0m ";
				scenarios[i]->print(show, startLineA);
			}
			else
			{
				cout << " \x1b[30m|-\x1b[0m ";
				scenarios[i]->print(show, startLineB);
			}
		}

		if (subsections.size() == 0 && startLine.empty())
			cout << startLineA << endl;

		for (int i = 0; i < subsections.size(); i++)
		{
			subsections[i]->print(show, startLineB);

			if (i == subsections.size() - 1)
				cout << startLineC << endl << endl;
			else
				cout << startLineB << endl;
		}
	}

	const string& Section::getDesc()
	{
		return desc;
	}
};
