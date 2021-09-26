/* 
 * The Data Lab / Systems Programming
 * UNO CSCI 2467 / Fall 2019
 * 
 **********
 * STEP 0 * <Please put your name and UNO email address here>
 **********
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/******************************************************
 * STEP 1: Read the following instructions carefully. *
 ******************************************************/

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

You will ONLY turn in this file (bits.c), everything else
is provided to help you check your work.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

REMINDER: Use the ./btest program to check your functions
          for correctness after making any changes. The
          program ./driver.pl will check for illegal
          operators and give you your final score.
#endif

/******************************************************************************
 * STEP 2: Modify the following functions according to the coding rules given *
 *                                                                            *
 *         You MUST explain each function in a comment                        *
 *         if you want to receive credit                                      *
 *****************************************************************************/

/* We do not support C11 <threads.h>.  */
/***************************************************
 * BOOLEAN operations (8 puzzles, 18 points total) *
 ***************************************************/
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  int z = 0; //Initialize an int filled with '1's as bits to use as a baseline.
  z = ~z;
  z = z & ~x; //Remove all the '1's in z-baseline at the same place as the '1's in x
  z = z & ~y; //Remove all the '1's in z-baseline at the same place as the '1's in y
  return ~z; //Invert the z-baseline to show all bits that were popped out by either x or y having a '1' at that place.
}

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  int result = 0; //Initalize an empty int filled with '0's as baseline
  result = result;
  result = result | ~x; //Create a '1' in result at the place of any '0's in x
  result = result | ~y; //Create a '1' in result at the place of any '0's in y
  return ~result; //Invert the result to show the places where the '1's in x and y didn't pop out in result (or in other words where there were two '1's at the same place
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int z = 0; //Initialize an int filled with '1's as bits to use as a baseline.
  z = ~z;
  z = z & ~x; //Remove all the '1's in z-baseline at the same place as the '1's in x
  z = z & ~y; //Remove all the '1's in z-baseline at the same place as the '1's in y
  z = ~z; //Reverse z to get the regular ORed result
  z = z & ~(x&y); //Remove any '1's where there are two '1's at the sames place in both x and y
  return z; //Invert the z-baseline to show all bits tfrom the previous steps
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  return !!(x^y);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  int mask = 1;
  return ((x&mask)<<31)>>31;
}
/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int specialBits(void) {
    int result = 0;
    result |=  53<<16|12<<12;
    return ~result;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 4
 */
int conditional(int x, int y, int z) {
  return (((!!x)<<31)>>31 & y)|(((!x)<<31)>>31 & z);
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  x = x ^ (x>>16);
  x = x ^ (x>>8);
  x = x ^ (x>>4);
  x = x ^ (x>>2);
  x = x ^ (x>>1);
  return (x & 1);
}
/*******************************************
 * INTEGERS (8 puzzles, 22 points total)   *
 *******************************************/
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return ~(0); //Start of with an int of all 0 bits, then inverse to give -1
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1<<31); //Set MSB bit to 1, the rest to zero, and then invert to get TMax
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x)+1; //Does a twos-complement swap by inverting the bits of target and adding one.
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return (x>>31)&1; //Move MSB to the LSB and & it with 1 to wipe out the rest of the bits
  //This makes it so that if MSB was 1 (Negative), the result is 1 and if it's 0 (Positive), then the result is 0 - both due to wiping out the rest of the bits
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int isPositive(int x) {
  return !(x>>31) ^ !x; //Move MSB to the LSB and & it with 1 to wipe out the rest of the bits
  //This makes it so that if MSB was 1 (Negative), the result is 1 and if it's 0 (Positive), then the result is 0 - both due to wiping out the rest of the bits
  //XOR by !x to deal with case when x = 0 yet needs to return 0
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return 2;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int addOK(int x, int y) {
  return !((((x+y)^y)&((x+y)^x))>>31);
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int result = ((~(x)&(x>>31&1)<<31>>31)+(x>>31&1)); //Deals with if number is negative - returns two's complement of it if so and 0 if number is positive by only matching number if MSB is 1
  result |= (x&(~x>>31&1)<<31>>31); //Same logic as above, but matches if MSB is 0 and deals with positive
  return result;
}
/*************************************************************
 * BONUS puzzles BELOW! be advised, some are quite difficult *
 ************************************************************/
/***************************************************
 INTEGERS and BOOLEAN (3 puzzles, up to 10 points) *
 ***************************************************/
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int byteSwap(int x, int n, int m) {
    return 2;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int result = 0;
  result = result + ((x>>0)&1);
  result = result + ((x>>1)&1);
  result = result + ((x>>2)&1);
  result = result + ((x>>3)&1);
  result = result + ((x>>4)&1);
  result = result + ((x>>5)&1);
  result = result + ((x>>6)&1);
  result = result + ((x>>7)&1);
  result = result + ((x>>8)&1);
  result = result + ((x>>9)&1);
  result = result + ((x>>10)&1);
  result = result + ((x>>11)&1);
  result = result + ((x>>12)&1);
  result = result + ((x>>13)&1);
  result = result + ((x>>14)&1);
  result = result + ((x>>15)&1);
  result = result + ((x>>16)&1);
  result = result + ((x>>17)&1);
  result = result + ((x>>18)&1);
  result = result + ((x>>19)&1);
  result = result + ((x>>20)&1);
  result = result + ((x>>21)&1);
  result = result + ((x>>22)&1);
  result = result + ((x>>23)&1);
  result = result + ((x>>24)&1);
  result = result + ((x>>25)&1);
  result = result + ((x>>26)&1);
  result = result + ((x>>27)&1);
  result = result + ((x>>28)&1);
  result = result + ((x>>29)&1);
  result = result + ((x>>30)&1);
  result = result + ((x>>31)&1);

  return result;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  return (x >> n) & ~(((1&(!!n))<<31)>>(n)<<1);
}
