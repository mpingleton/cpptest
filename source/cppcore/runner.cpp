//-----------------------------------------------------------------------------
// CPPTEST
//
// cppcore/runner.cpp
//
// Runner class's expectation methods.
//
// Created	: 5 April 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"

namespace cpptest
{
	Runner::Runner()
	{
		sections.clear();
	}

	Runner::~Runner()
	{
		for (int i = 0; i < sections.size(); i++)
			delete sections[i];

		sections.clear();
	}

	void Runner::add(Section* pSection)
	{
		sections.push_back(pSection);
	}

	void Runner::run(char show)
	{
		for (int i = 0; i < sections.size(); i++)
			sections[i]->run(show);
	}

	bool Runner::didPass()
	{
		int numberPass = 0, numberFail = 0;
		for (int i = 0; i < sections.size(); i++)
		{
			if (sections[i]->didPass())
				numberPass++;
			else
				numberFail++;
		}

		if (numberPass > 0 && numberFail == 0)
			return true;

		return false;
	}

	void Runner::print(char show)
	{
		if (show == SHOW_NOTHING) return;
		for (int i = 0; i < sections.size(); i++)
			sections[i]->print(show);
	}
};
