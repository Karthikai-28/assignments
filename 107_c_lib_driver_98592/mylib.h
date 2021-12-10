#ifndef _MYLIB_H_INCLUDED_210407_
#define _MYLIB_H_INCLUDED_210407_

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//	myLib.h
//
//	Purpose: Header file for Embedded-C student final project.
//	History:	07apr2021	DAM	Initial version for cToF, fToC, nextCyl, dayOfWeek,
//										dateSerialNum, and daysBetween functions.
//				12apr2021	DAM	Added MIN,MAX,BOUND macros. Added distance,
//										slopeIntercept, and linearInterp functions.
//										Changed date functions to use new Date structure.
//				14apr2021	DAM	Added computeIeee754singleFactors function and
//										associated data types.
//				19apr2021	DAM	Added string length, copy, and reverse functions.

#include <stdbool.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define BOUND(lo, val, hi) (		(lo) < (hi) \
										?	(MIN( MAX((lo),(val)), (hi))) \
										:	(MIN( MAX((hi),(val)), (lo))) \
									)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
float cToF(float degC);
float fToC(float degF);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef enum Cylinders
{
	L1, R1,
	L2, R2,

	NUM_CYLS,
	CYL_ERROR = NUM_CYLS

} Cylinder;

////////////////////////////////////////////////////////////////////////////////
// firing pattern is R1, L2, R2, L1
// returns valid nextCyl or CYL_ERROR if invalid nowCyl is passed
Cylinder nextCyl(Cylinder nowCyl);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef enum DaysOfWeek
{
	SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
}DayOfWeek;

////////////////////////////////////////////////////////////////////////////////
typedef struct _Date
{
	unsigned	month;
	unsigned	day;
	unsigned	year;
} Date;

////////////////////////////////////////////////////////////////////////////////
DayOfWeek	dayOfWeek(Date);

////////////////////////////////////////////////////////////////////////////////
// Returns positive number if d2 is after d1.
// Returns negative number if d2 is before d1.

int daysBetween(Date d1, Date d2);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct _Point
{
	float	x;
	float	y;
} Point;

////////////////////////////////////////////////////////////////////////////////
typedef struct _SlopeIntercept
{
	float	slope;
	float	yIntercept;
	bool	valid;
} SlopeIntercept;

////////////////////////////////////////////////////////////////////////////////
typedef struct _LinearInterp
{
	float	yValue;
	bool	valid;
} LinearInterp;

////////////////////////////////////////////////////////////////////////////////
// The distance function returns the linear distance between 2 Points.  The
// distance is always returned as a positive number.
// Helpful standard C library functions (from math.h) may be:
//   sqrtf
//   fabs

float distance(const Point p1, const Point p2);

////////////////////////////////////////////////////////////////////////////////
// Compute slope and y-intercept for 2 given points
// Value returned in valid field:
//		true  - computation successful (i.e., deltaX != 0)
//				- other fields are valid/defined
//		false - computation unsuccessful (i.e., detlaX == 0)
//				- other fields are undefined

SlopeIntercept slopeIntercept(const Point p1, const Point p2);

////////////////////////////////////////////////////////////////////////////////
// Perform linear interpolation.
// Returns the y coordinate for the given x (and points).
// Returns 0 if delta x of p1,p2 is 0
// The limit argument:
//		true  - limit/saturate the result within p1,p2 range
//    false - extrapolate the result if outside the p1,p2 range
// The LinearInterp.valid field:
//		true	- computation successful (i.e., deltaX != 0)
//		false	- computation unsuccessful (i.e., deltaX == 0)

LinearInterp linearInterp(const Point p1, const Point p2, const float x, const bool limit);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct _Ieee754singleFields
{
	uint32_t		fraction	: 23;
	uint32_t		exponent	: 8;
	uint32_t		sign		: 1;
}Ieee754singleFields;

////////////////////////////////////////////////////////////////////////////////
typedef union _Ieee754singlePrecision
{
	float						value;
	Ieee754singleFields	fields;
}Ieee754singlePrecision;

////////////////////////////////////////////////////////////////////////////////
typedef struct _Ieee754singleFactors
{
	float		signFactor;
	float		exponentFactor;
	float		fractionFactor;
}Ieee754singleFactors;

////////////////////////////////////////////////////////////////////////////////
// signFactor     = (-1) raised to the sign field.
// exponentFactor = 2 raised to (the exponent field minus 127).
// fractionFactor = 1 plus (fraction field divided by (1 left shifted by 23 bits).

// The powf function from math.h may be helpful for computing the
// exponentFactor (be sure to do signed integer subtraction when computing the
// exponent to which 2 is being raised).
// Only implement for non-zero normal single precision floats, i.e., where the
// exponent field is in the range 0x01 to 0xfe.  If the exponent field is
// 0x00 or 0xff, then just return 0 (zero) in all factor fields.
// The fractionFactor can be computed by simply dividing the fraction field
// by (1 << 23) (be sure to do a floating point divide, not an integer divide)
// and then add one to that result.

Ieee754singleFactors  computeIeee754singleFactors(const Ieee754singlePrecision);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// returns number of characters in C string (excluding the terminating null)
unsigned stringLength(const char* const pS);

// copy string in 1st parameter to address starting at 2nd paramenter
// return number of characters copied (excluding the terminating null)
unsigned stringCopy(const char* const from, char* to);

// reverse the non-null characters in 'from' string placing the result into
// 'to' string (i.e., "abcd" becomes "dcba".
// return the number of characters copied (excluding the terminating null)
unsigned stringReverse(const char* const from, char* to);

#endif
