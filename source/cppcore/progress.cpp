//-----------------------------------------------------------------------------
// CPPTEST
//
// cppcore/progress.cpp
//
// Function which prints a progress bar to the terminal screen.
//
// Created	: 21 September 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#define PROGRESS_BUFFER_LEN 4096

void cpptest::coutProgress(const string& caption, int numerator, int denominator)
{
	struct winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	int progWidth = ws.ws_col - 2;
	if (progWidth >= PROGRESS_BUFFER_LEN)
		return;

	char prog[PROGRESS_BUFFER_LEN];
	memset(&prog, 0, PROGRESS_BUFFER_LEN);

	int pn = (numerator * progWidth) / denominator;

	char progStr[PROGRESS_BUFFER_LEN];
	memset(&progStr, 0, PROGRESS_BUFFER_LEN);
	snprintf(progStr, PROGRESS_BUFFER_LEN, "<%s \x1b[1m(%i/%i)\x1b[0m>", caption.c_str(), numerator, denominator);

	int progStrLen = strlen(progStr);
	int progLen = 0;
	
	int es = 0;
	for (int i = 0; i < progStrLen; i++)
	{
		char c = progStr[i];

		if (es)
		{
			if (c == 'm')
				es = 0;
		}
		else
		{
			if (c == '\x1b')
				es = 1;
			else
				progLen++;
		}
	}

	int progPos = (progWidth / 2) - (progLen / 2);

	int progI = 0;
	prog[progI] = '[';
	progI++;
	
	for (int pi = 0; pi < progPos; pi++)
	{
		if (numerator >= denominator || pi < pn)
			prog[progI] = '=';
		else
			prog[progI] = ' ';

		progI++;
	}

	for (int pi = 0; pi < progStrLen; pi++)
	{
		char c = progStr[pi];

		if ((c == ' ' || c == '\t') && (pi < pn))
			prog[progI] = '~';
		else
			prog[progI] = c;

		progI++;
	}

	for (int pi = progPos + progLen; pi < progWidth; pi++)
	{
		if (numerator >= denominator || pi < pn)
			prog[progI] = '=';
		else
			prog[progI] = ' ';

		progI++;
	}
	
	prog[progI] = ']';
	progI++;

	cout << prog;
}
