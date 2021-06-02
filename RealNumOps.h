#ifndef _REAL_OP_H_
#define _REAL_OP_H_

#include <stdlib.h>
#include <string.h>
#include "BigNumOps.h"

char *fill_zero(char *a, int osize, int nsize);

char *remove_zero(char *a);

char *format_real(char *a, int sign, int point);

char *make_prec(char *a, int prec);

int RealBigNumCmp(char *a, char *b);

int RealBigNumAbsCmp(char *a, char *b);

char *RealBigNumAdd(char *a, char *b);

char *RealBigNumSub(char *a, char *b);

char *RealBigNumMul(char *a, char *b);

char *RealBigNumDiv(char *a, char *b);

char *RealBigNumDiv_Rem(char *a, char *b, char *rem);

char *RealBigNumPow(char *a, int num);

char *RealBigNumRoot(char *a, int num);

char *RealBigNumSqrt(char *a);

char *RealBigNumSin(char *a);

char *RealBigNumCos(char *a);

char *RealBigNumLn(char *a);

char *IntBigNumGcd(char *a, char *b);

#endif
