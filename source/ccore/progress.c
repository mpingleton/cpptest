//-----------------------------------------------------------------------------
// CPPTEST
//
// ccore/progress.c
//
// Function which prints a progress bar to the terminal screen.
//
// Created	: 21 September 2025
// Author	: Michael Pingleton
//-----------------------------------------------------------------------------

#include "../../include/cpptest.h"

#include <stdlib.h>
#include <string.h>

#define PROGRESS_WIDTH 125

void printProgress(const char* pCaption, int numerator, int denominator)
{
	char prog[PROGRESS_WIDTH + 1] = {};
	int pn = (numerator * PROGRESS_WIDTH) / denominator;

	char progStr[PROGRESS_WIDTH] = {};
	snprintf(progStr, PROGRESS_WIDTH, "<%s \x1b[1m(%i/%i)\x1b[0m>", pCaption, numerator, denominator);

	size_t progLen = strlen(progStr);
	if (progLen > 0)
	{
		int progStrS = (PROGRESS_WIDTH / 2) - (progLen / 2);
		for (int pi = 0; pi < progLen; pi++)
			prog[progStrS + pi] = progStr[pi];
	}
		
	for (int pi = 0; pi < PROGRESS_WIDTH; pi++)
	{
		if (prog[pi] == 0)
		{
			if ((pi < 90 && numerator == denominator - 1) || pi < pn)
				prog[pi] = '=';
			else
				prog[pi] = ' ';
		}
		else if (prog[pi] == ' ')
		{
			if ((pi < 90 && numerator == denominator - 1) || pi < pn)
				prog[pi] = '-';
		}
	}

	printf("[%s]", prog);
}
