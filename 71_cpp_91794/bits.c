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
  return ~(~x & ~y);
}

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
return ~(~x | ~y);
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {
  return ~(~(~x & y) & ~(x & ~y)); 
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  return !!(~(x ^ ~y));
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  return ~(x & 0x1) + 1;
}
/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int specialBits(void) {
    return ~(215 << 14);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 4
 */
int conditional(int x, int y, int z) {
  x = !x;				// x is bang'd to make a 0 or a 1
	x = ~x + 1;			// x is inverted to be 0xfffffffe or 0xffffffff, then add one to cause either overflow or make all 1's
	return ((y & ~x) | (z & x)); 
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  x = x ^ (x << 16);  // odd_0 = odd   ^ even   
	x = x ^ (x << 8);   // odd_1 = odd_0 ^ even
	x = x ^ (x << 4);   // odd_2 = odd_1 ^ even
	x = x ^ (x << 2);   // odd_3 = odd_2 ^ even
	x = x ^ (x << 1);   // odd_4 = odd_3 ^ even

	return !!(x >> 31); // (odd_4 >> 31) results in 0xFFFFFFFF or 0x00000000.
		   	    // if 0x00000000, then even bits; if 0xFFFFFFFF, then odd bits.
			    // double bang will convert to 0x0 even, 0x1 for odd
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
   return ~(0x1) + 0x1; // negates to make -1.
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(0x1 << 31); 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~(x) + 0x1; //twos complement gives the negative vr
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return !!((0x1 << 31) & x);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int isPositive(int x) {
  return !!(((~x + 1) & ~x) & (0x1 << 31)); 
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return (~((x | (~x + 1)) >> 31) & 0x1);
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
int msb, z; // msb created to mask x and y and validate if
       		    // they are negative or positive; z is used to
		    // store the result of x + y, and is checked
		    // with msb to determine if the result is 
		    // negative or positive.
	
	msb = 0x1 << 31; //mask
	z = x + y;
	z = z & msb; // result is 0x80000000 or 0x00000000

	/*
	 * (x & msb) and (y & msb) are used to check signs of x and y.
	 * 
	 * these values are XOR'd together to determine if both signs are
	 * the same:
	 * 
	 * 0x80000000 ^ 0x80000000 = 0
	 * 0x0 ^ 0x0 = 0
	 *
	 * if the value returns 1, we know it's ok to add,
	 * because overflow does not occur on +, - or vise versa.
	 * overflow only occurs when signs are the same, therefore 
	 * receiving the value 0 is needed to determine the next check...
	 *
	 * if both x and y are the same sign, then we can assume (x & msb) 
	 * will suffice to represent both signs. note that z has already 
	 * been calculated to determine if its signed or unsigned, this 
	 * is XOR'd with x to check and see if both signsare the same.
	 *
	 * if both signs are same, in this case we will use both signed, 
	 * 0x10000000 ^ 0x10000000 = 0x0, which will then be bang'd once 
	 * to return 1 for an OK to add. if they aren't the same value 
	 * after determining that both signs are the same, result will 
	 * be 1, and bang'd will return 0.
	 *
	 * the outside double bang is there to confirm a 0 or 1 instead
	 * of ---> 0x10000000 or 0x0 from the left hand side.
	 *
	 * */
	return !!((x & msb) ^ (y & msb)) | !((x & msb) ^ z);
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
return 2;
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
    int first_index, sec_index, first_val, sec_val, hex_ff; // declaring variables that will be used later
	int first_to_sec, sec_to_first, result; 		// these will store the swapped positions for each of the values from each index.

	first_index = (x >> (n << 3)); // (n << 3) will shift x by 0, 8, 16, or 24 depending on the values entered. 
				       // the values 0000, 1000, 10000, 11000 are created this will put two hexdecimals
				       // in the lower 8 bits to be masked.
	sec_index   = (x >> (m << 3)); // (m << 3) will shift x by 0, 8, 16, or 24 as well to be able to mask the lower 8 bits.
	
	hex_ff = 0xFF; //will be used to mask off 2 hexdecimals represented by first_index and second_index
	
	first_val = (first_index & hex_ff); // the mask will store the value inside as a 2 hex value
	sec_val   = (sec_index   & hex_ff); // the second index value stored as a 2 hex value

	first_to_sec = (first_val << (m << 3)); // the first_val will be shifted back to sec_index
	sec_to_first = (sec_val   << (n << 3)); // sec_val will be shifted back to first_index 
	
	result = (first_to_sec | sec_to_first); // the result ORs both values. ie if byteSwap(0x12345678, 1, 3) ---> 0x56001200
	
	x = (~((hex_ff << (m << 3)) | (hex_ff << (n << 3))) & x); // (0xFF00FF00 is created by ORing both hex_ff shifted to the left by 
								  // m amount, and the lower half by n amount. x being 0x12345678 will
								  // get back 0x12003400 which is not what we need, so instead we complement
								  // 0xFF00FF00 to get 0x00FF00FF & x which will get 0x00340078.

	return (result | x);					  // (0x56001200 | 0x00340078) ==> 0x56341278
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
x = x + (x >> 16);
	x = x + (x >> 8);
	x = x + (x >> 4);
	x = x + (x >> 2);
	x = x + (x >> 1);
	
	return x & 63;
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
  int msb, cancel_if_pos, remove_extra_bit;
	
	x = x >> n; // shift x by the specified amount, note that this will maintain the sign bit if neg

	msb = 0x1 << 31; 		    // creates a mask of 0x80000000
	cancel_if_pos = ~(!!(x & msb)) + 1; // x is masked to determine if operation needs to be done,
       					    // gives 0x0 if x == positive, or 0xFFFFFFFF if x == negative.
	
	msb = msb >> n; 	      // msb is shifted by the same amount to mask out the negative values
	remove_extra_bit = msb << 1;  // msb is shifted back one b/c of the extra bits that aren't needed in front of the value
				      // ie, if msb is 0xFF------, then the remove_extra_bit will make msb = 0xFE------

	remove_extra_bit = (msb ^ remove_extra_bit); // remove_extra_bit will get rid of the extra bit that overlaps msb's 
						     // value (designed to remove the sign bits).
						     
	msb = msb ^ remove_extra_bit; // msb is corrected with a new value with the removed extra bit 
				      // (only keeping the signed bits).
	
	return (x & ~(cancel_if_pos)) | (x & (cancel_if_pos) & (x ^ msb));
}
