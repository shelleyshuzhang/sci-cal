#ifndef _REAL_OP_H_
#define _REAL_OP_H_

#include <stdlib.h>
#include <string.h>
#include "BigNumOps.h"

#define REAL_ACCURACY 10

/**
 *
 * @param a
 * @param o_size
 * @param n_size
 * @return
 */
char *fill_zero(char *a, int o_size, int n_size);

/**
 *
 * @param a
 * @return
 */
char *remove_zero(char *a);

/**
 *
 * @param a
 * @param sign
 * @param point
 * @return
 */
char *format_real(char *a, int sign, int point);

/**
 *
 * @param a
 * @param prec
 * @return
 */
char *make_prec(char *a, int prec);

/**
 *
 * @param a
 * @param b
 * @return
 */
int RealBigNumCmp(char *a, char *b);

/**
 *
 * @param a
 * @param b
 * @return
 */
int RealBigNumAbsCmp(char *a, char *b);

/**
 *
 * @param a
 * @param b
 * @return
 */
char *RealBigNumAdd(char *a, char *b);

/**
 *
 * @param a
 * @param b
 * @return
 */
char *RealBigNumSub(char *a, char *b);

/**
 *
 * @param a
 * @param b
 * @return
 */
char *RealBigNumMul(char *a, char *b);

/**
 *
 * @param a
 * @param b
 * @return
 */
char *RealBigNumDiv(char *a, char *b);

/**
 *
 * @param a
 * @param b
 * @param rem
 * @return
 */
char *RealBigNumDiv_Rem(char *a, char *b, char *rem);

/**
 *
 * @param a
 * @param num
 * @return
 */
char *RealBigNumPow(char *a, int num);

/**
 *
 * @param a
 * @param num
 * @return
 */
char *RealBigNumRoot(char *a, int num);

/**
 *
 * @param a
 * @return
 */
char *RealBigNumSqrt(char *a);

#endif
