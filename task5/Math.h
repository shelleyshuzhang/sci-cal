#ifndef CAL_MATH_H
#define CAL_MATH_H

#include <stdlib.h>
#include <string.h>
#include "../task1/RealNumOps.h"
#include "../task1/BigNumOps.h"

/**
 *
 * @param a (char) a degree
 * @return
 */
char *RealBigNumSin(char *a);

char *RealBigNumCos(char *a);

char *RealBigNumTan(char *a);

char *RealBigNumLn(char *a);

/**
 *
 * @param in (char*) arc sin
 * @return the radian of arc sin(in)
 */
char* RealBigArcSin(char* in);

char* RealBigArcCos(char* in);

char* RealBigArcTan(char* in);

double d_asin(double in);

double d_acos(double in);

double d_atan(double in);

char* convert_radian(char* radian);

char* convert_degree(char* degree);

#endif //CAL_MATH_H
