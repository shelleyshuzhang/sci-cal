#ifndef _BIG_OP_H_
#define _BIG_OP_H_

#include <stdlib.h>
#include <string.h>

/**
 * Reverse the Big Number
 *
 * @param a (char*) the big number to be reversed
 * @return reversed big number
 */
char *BigNumReverse(char *a);

/**
 * Compare two unsigned Big Number
 *
 * @param a (char*) First unsigned big number
 * @param b (char*) Second unsigned big number
 * @return (int) 1 if a bigger than b, 0 if
 *          equal, -1 if a smaller than b
 */
int UnsignedBigNumCmp(char *a, char *b);

/**
 * Add two unsigned big numbers
 *
 * @param a (char*) First unsigned big number
 * @param b (char*) Second unsigned big number
 * @return (char*) the result of a + b
 */
char *UnsignedBigNumAdd(char *a, char *b);

/**
 * Minus two unsigned big numbers
 *
 * @param a (char*) First unsigned big number
 * @param b (char*) Second unsigned big number
 * @return (char*) the result of a - b
 */
char *UnsignedBigNumSub(char *a, char *b);

/**
 * Multiply two unsigned big numbers
 *
 * @param a (char*) First unsigned big number
 * @param b (char*) Second unsigned big number
 * @return (char*) the result of a * b
 */
char *UnsignedBigNumMul(char *a, char *b);

/**
 * Divide two unsigned big numbers
 *
 * @param a (char*) First unsigned big number
 * @param b (char*) Second unsigned big number
 * @return (char*) the result of a / b
 */
char *UnsignedBigNumDiv(char *a, char *b);

/**
 * The power of a Big Number
 *
 * @param a (char*) The unsigned big number
 * @param b (int) The power
 * @return (char*) the result of a^(b)
 */
char *UnsignedBigNumPow(char *a, int b);

/**
 * The root of a Big Number
 *
 * @param a (char*) The unsigned big number
 * @param num (int) The root
 * @return (char*) the result of a^(1/b)
 */
char *UnsignedBigNumRoot(char *a, int num);

/**
 * The square root of a Big Number
 *
 * @param a (char*) The unsigned big number
 * @return (char*) the result of a^(1/2)
 */
char *UnsignedBigNumSqrt(char *a);

/**
 * Divide two unsigned big numbers, with reminder
 *
 * @param a (char*) First unsigned big number
 * @param b (char*) Second unsigned big number
 * @return (char*) the result of a / b,
 *          also keep track of the reminder
 */
char *UnsignedBigNumDiv_Rem(char *a, char *b, char *rem);

#endif
