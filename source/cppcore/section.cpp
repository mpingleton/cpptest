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
		if (show > SHOW_NOTHING)
		{
			if (!desc.empty()) cout << "Section: " << desc << endl;
			else cout << "Section: " << endl;
		}

		for (int i = 0; i < scenarios.size(); i++)
			scenarios[i]->run(show);

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
			cout << "[  \x1b[32mOK\x1b[0m  ]";
		else
			cout << "[ \x1b[31mFAIL\x1b[0m ]";

		if (!desc.empty())
			cout << "\t" << desc << endl;
		else
			cout << endl;

		for (int i = 0; i < scenarios.size(); i++)
			scenarios[i]->print(show);

		for (int i = 0; i < subsections.size(); i++)
			subsections[i]->print(show);
	}
};
