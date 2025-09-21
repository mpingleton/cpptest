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
			char prog[101] = {};
			if (show > SHOW_NOTHING)
			{
				printf("\x1b[2K");
				int pn = i * 100 / scenarios.size();

				char progStr[100] = {};
				sprintf(progStr, "<Running Scenario \x1b[1m%i/%li\x1b[0m>", i + 1, scenarios.size());

				size_t progLen = strlen(progStr);
				if (progLen > 0)
				{
					int progStrS = 50 - progLen / 2;
					for (int pi = 0; pi < progLen; pi++)
						prog[progStrS + pi] = progStr[pi];
				}
				
				for (int pi = 0; pi < 100; pi++)
				{
					if (prog[pi] == 0)
					{
						if ((pi < 90 && i == scenarios.size() - 1) || pi < pn)
							prog[pi] = '=';
						else
							prog[pi] = ' ';
					}
					else if (prog[pi] == ' ')
					{
						if ((pi < 90 && i == scenarios.size() - 1) || pi < pn)
							prog[pi] = '-';
					}
				}

				printf("[%s]\n\x1b[2K", prog);
			}

			scenarios[i]->run(show);

			if (show > SHOW_NOTHING) printf("\x1b[1F");
		}

		for (int i = 0; i < subsections.size(); i++)
			subsections[i]->run(show);
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

	void Section::print(char show)
	{
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

		for (int i = 0; i < scenarios.size(); i++)
		{
			if (i == scenarios.size() - 1)
			{
				cout << " \x1b[30m\\-\x1b[0m ";
				scenarios[i]->print(show, "    ");
			}
			else
			{
				cout << " \x1b[30m|-\x1b[0m ";
				scenarios[i]->print(show, " \x1b[30m| \x1b[0m ");
			}
		}

		for (int i = 0; i < subsections.size(); i++)
			subsections[i]->print(show);

		cout << endl;
	}
};
