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
	}

	Section::Section(string inputDesc)
	{
		desc = inputDesc;
		scenarios.clear();
	}

	Section::~Section()
	{
		desc = "";

		for (int i = 0; i < scenarios.size(); i++)
			delete scenarios[i];

		scenarios.clear();
	}

	void Section::add(Scenario* pScenario)
	{
		scenarios.push_back(pScenario);
	}

	void Section::run(bool show)
	{
		if (show)
		{
			if (!desc.empty()) cout << "Section: " << desc << endl;
			else cout << "Section: " << endl;
		}

		for (int i = 0; i < scenarios.size(); i++)
		{
			if (show)
			{
				if (!desc.empty()) cout << desc << ": ";
				scenarios[i]->print();
			}

			scenarios[i]->run(show);

			if (show)
			{
				if (!desc.empty()) cout << desc << ": ";
				scenarios[i]->print();
			}
		}
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

		if (numberPass > 0 && numberFail == 0)
			return true;

		return false;
	}

	void Section::print()
	{
		if (scenarios.empty())
			cout << "[      ]";
		else if (didPass())
			cout << "[  OK  ]";
		else
			cout << "[ FAIL ]";

		if (!desc.empty())
			cout << "\t" << desc << endl;
		else
			cout << endl;

		for (int i = 0; i < scenarios.size(); i++)
			scenarios[i]->print();

		for (int i = 0; i < 80; i++) cout << "+";
		cout << endl;
	}
};
