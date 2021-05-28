#ifndef _BIG_OP_H_
#define _BIG_OP_H_
char *BigNumReverse(char *a);
int UnsignedBigNumCmp(char *a, char *b);
char *UnsignedBigNumAdd(char *a, char *b);
char *UnsignedBigNumSub(char *a, char *b);
char *UnsignedBigNumMul(char *a, char *b);
char *UnsignedBigNumDiv(char *a, char *b);
char *UnsignedBigNumPow(char *a, int b);
char *UnsignedBigNumRoot(char *a, int num);
char *UnsignedBigNumSqrt(char *a);
char *UnsignedBigNumDiv_Rem(char *a, char *b, char *rem);
#endif
