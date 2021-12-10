////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//	myLibTest.c
//
//	Purpose: Test driver for Embedded-C student final project.
//	History:	07apr2021	DAM	Initial version for cToF, fToC, and nextCyl
//										functions.
//				12apr2021	DAM	Added tests for daysBetween, dayOfWeek, distance,
//										slopeIntercept, and linearInterp functions.
//				14apr2021	DAM	Added tests for computeIeee754singleFactors function.
//				19apr2021	DAM	Added tests for string length, copy, and reverse
//										functions.

#include "myLib.h"


////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	unsigned errorCount = 0;

	////////////////////////////////////////////////////////////
	{	// test cToF function

		const struct
		{
			float	celsius;
			int	resultTimes10;
		} tests[] = { {0, 320}, {100, 2120}, {1.5F, 347} };

		int	i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			float f = cToF(tests[i].celsius);
			if((int)((f * 10) + .5F) != tests[i].resultTimes10) ++errorCount;
		}
	}

	////////////////////////////////////////////////////////////
	{	// test fToC function

		const struct
		{
			float	fahrenheit;
			int	resultTimes10;
		} tests[] = { {127.4F, 530}, {123, 506} };

		int	i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			float c = fToC(tests[i].fahrenheit);
			if((int)((c * 10) + .5F) != tests[i].resultTimes10) ++errorCount;
		}
	}

	////////////////////////////////////////////////////////////
	{	// test nextCyl function

		const struct
		{
			Cylinder	nowCyl;
			Cylinder	nextCyl;
		} tests[] = { {R1, L2}, {L2, R2}, {R2, L1}, {L1, R1}, {NUM_CYLS, CYL_ERROR} };

		int i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
			if(nextCyl(tests[i].nowCyl) != tests[i].nextCyl) ++errorCount;

		if(nextCyl((Cylinder)-1) != CYL_ERROR) ++errorCount;
	}


	////////////////////////////////////////////////////////////
	{	// test dayOfWeek function

		struct
		{
			Date			d;
			DayOfWeek	dow;
		} tests[] = {	{{ 2, 3,1979}, SATURDAY},
							{{ 1, 1,1990}, MONDAY},
							{{ 2, 1,1980}, FRIDAY},
							{{ 3,31,1999}, WEDNESDAY},
							{{12,31,1998}, THURSDAY}
						};

		int i;
		for(i = sizeof(tests)/sizeof(tests[0]) - 1; i >= 0; i--)
		{
			if(dayOfWeek(tests[i].d) != tests[i].dow) ++errorCount;
		}
	}

	////////////////////////////////////////////////////////////
	{	// test daysBetween function

		struct
		{
			Date	d1;
			Date	d2;
			int	daysBetween;
		} tests[] = {	{{ 2, 3,1979}, { 2, 4,1979},      1},
							{{ 2, 3,1979}, { 2, 3,1979},      0},
							{{ 2, 3,1979}, { 2, 2,1979},     -1},
							{{12,31,1998}, { 1, 1,1990},  -3286},
							{{ 3, 2,1900}, { 2,27,2000},  36521},
							{{ 2,27,2000}, { 3, 2,1900}, -36521}
						};

		int i;
		for(i = sizeof(tests)/sizeof(tests[0]) - 1; i >= 0; i--)
		{
			if(daysBetween(tests[i].d1, tests[i].d2) != tests[i].daysBetween) ++errorCount;
		}
	}

	////////////////////////////////////////////////////////////
	{	// test distance function

		const struct
		{
			Point		p1;
			Point		p2;
			unsigned	centiDist;
		} tests[] =	{	{{ 1.F,  1.F}, { 2.F,  2.F},  141U},
							{{-1.F, -1.F}, {-2.F, -2.F},  141U},
							{{ 0.F, -2.F}, { 0.F,  2.F},  400U},
							{{-1.F,  3.F}, { 1.F,  3.F},  200U},
							{{-1.F,  3.F}, {-1.F,  3.F},    0U},
							{{10.F, 10.F}, {20.F, 30.F}, 2236U}
						};

		int i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
			if((unsigned)(distance(tests[i].p1, tests[i].p2) * 100) != tests[i].centiDist)
				++errorCount;
	}


	////////////////////////////////////////////////////////////
	{	// test slopeIntercept function

		const unsigned DONT_CARE = -1;

		const struct
		{
			Point			p1;
			Point			p2;
			bool			valid;
			int			centiSlope;
			int			centiIntercept;
		} tests[] =	{	{{ 0.F,  0.F}, { 1.F,  1.F}, true,		   100, 			  0},
							{{ 0.F,  0.F}, { 0.F,  1.F}, false, DONT_CARE,  DONT_CARE},
							{{-2.F, -2.F}, { 3.F,  5.F}, true,		   140, 			 80},
							{{ 2.F,  2.F}, {-3.F, -5.F}, true,		   140, 		   -80},
							{{ 2.F,  2.F}, { 4.F,  2.F}, true,		     0, 		   200}
						};

		int i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			SlopeIntercept	si = slopeIntercept(tests[i].p1, tests[i].p2);
			if(si.valid != tests[i].valid)
				++errorCount;
			else if(si.valid)
			{
				if((int)(si.slope * 100 + (si.slope < 0 ? -.5F : +.5F)) != tests[i].centiSlope)
					++errorCount;

				if((int)(si.yIntercept * 100 + (si.yIntercept < 0 ? -.5F : +.5F)) != tests[i].centiIntercept)
					++errorCount;
			}
		}
	}


	////////////////////////////////////////////////////////////
	{	// test linearInterp function

		const unsigned DONT_CARE = -1;

		const struct
		{
			Point		p1;
			Point		p2;
			float		x;
			bool		limit;
			bool		valid;
			int		centiY;
		} tests[] = {	{{ 0, 0}, { 1,  1},  .5F, false, true,         50},
							{{ 0, 0}, {-1, -1}, -.5F, false, true,        -50},
							{{ 0, 0}, { 0, -1}, -.5F, false, false, DONT_CARE},
							{{ 0, 0}, { 1,  1},  2.F, false, true,        200},
							{{ 0, 0}, { 1,  1},  2.F, true,  true,        100},
							{{ 0, 0}, { 1,  1}, -1.F, true,  true,          0},
							{{-1,-1}, {-3, -5}, -2.F, true,  true,       -300},
							{{-1,-1}, {-3, -5}, -7.F, true,  true,       -500}
						};

		int i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			LinearInterp li = linearInterp(tests[i].p1, tests[i].p2, tests[i].x, tests[i].limit);
			if(li.valid != tests[i].valid)
				++errorCount;
			else if(li.valid)
			{
				if((int)(li.yValue * 100 + (li.yValue < 0 ? -.5F : +.5F)) != tests[i].centiY)
					++errorCount;
			}
		}
	}


	////////////////////////////////////////////////////////////
	{	// test computeIeee754singleFactors function

		const struct
		{
			float			testValue;
			uint32_t		sign;
			uint32_t		exponent;
			uint32_t		fraction;
		} tests[] =	{	{      0.00F,	0x00000000, 0x00000000, 0x00000000},
							{   1000.75F,	0x3f800000, 0x44000000, 0x3ffa3000},
							{20.0625e-8F,	0x3f800000, 0x34000000, 0x3FD76B61},
							{     -1.25F,	0xbf800000, 0x3f800000, 0x3fa00000},
							{ 1.125e-37F,	0x3f800000, 0x02000000, 0x3f992087},
							{   3.75e37F,	0x3f800000, 0x7d800000, 0x3fe1b1e6},
							{  -.015625F,	0xbf800000, 0x3c800000, 0x3f800000}
						};

		int i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			Ieee754singleFactors		isf;
			Ieee754singlePrecision	isp;
			float							computed;

			isp.value	= tests[i].testValue;
			isf			= computeIeee754singleFactors(isp);
			computed		= isf.signFactor * isf.exponentFactor * isf.fractionFactor;

			if(computed != tests[i].testValue)
				++errorCount;
			else if(*((unsigned*)&isf.signFactor) != tests[i].sign)
				++errorCount;
			else if(*((unsigned*)&isf.exponentFactor) != tests[i].exponent)
				++errorCount;
			else if(*((unsigned*)&isf.fractionFactor) != tests[i].fraction)
				++errorCount;
		}
	}

	////////////////////////////////////////////////////////////
	{	// test stringLength function

		const struct
		{
			const char* const	s;
			const unsigned		l;
		} tests[] =	{	{"string1",			 7U},
							{"",					 0U},
							{"test string",	11U}
						};

		int i;
		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			if(stringLength(tests[i].s) != tests[i].l)
				++errorCount;
		}
	}

	////////////////////////////////////////////////////////////
	{	// test stringCopy function

		const struct
		{
			const char* const	s;
			const unsigned		l;
		} tests[] =	{	{"string1",			 7U},
							{"",					 0U},
							{"test string",	11U}
						};

		char	myBuff[32];
		int	i;

		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			if(stringCopy(tests[i].s, myBuff) == tests[i].l)
			{
				int index = (int)(tests[i].l);
				do
				{
					if(tests[i].s[index] != myBuff[index])
					{
						++errorCount;
						break;
					}
				}while(--index >= 0);
			}
			else
				++errorCount;
		}
	}


	////////////////////////////////////////////////////////////
	{	// test stringReverse function

		const struct
		{
			const char* const	s;
			const unsigned		l;
		} tests[] =	{	{"string1",			 7U},
							{"",					 0U},
							{"test string",	11U}
						};

		char	myBuff[32];
		int	i;

		for(i = sizeof(tests) / sizeof(tests[0]) - 1; i >= 0; i--)
		{
			if(stringReverse(tests[i].s, myBuff) == tests[i].l)
			{
				int indexR = (int)(tests[i].l);

				if(myBuff[indexR] != '\0')
					++errorCount;
				else
				{
					int indexL = 0;
					while(--indexR >= 0)
					{
						if(myBuff[indexL] != tests[i].s[indexR])
						{
							++errorCount;
							break;
						}

						++indexL;
					}
				}
			}
			else
				++errorCount;
		}
	}


	return errorCount;
}
