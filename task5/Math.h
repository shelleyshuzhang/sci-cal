#ifndef CAL_MATH_H
#define CAL_MATH_H

#include <stdlib.h>
#include <string.h>
#include "../task1/RealNumOps.h"
#include "../task1/BigNumOps.h"

char *RealBigNumSin(char *a);

char *RealBigNumCos(char *a);

char *RealBigNumTan(char *a);

char *RealBigNumSec(char *a);

char *RealBigNumCsc(char *a);

char *RealBigNumCot(char *a);

char *RealBigNumLn(char *a);

char *RealBigNumLog(char *base, char *value);

char *RealBigArcSin(char *in);

char *RealBigArcCos(char *in);

char *RealBigArcTan(char *in);

char *RealBigArcSec(char *in);

char *RealBigArcCsc(char *in);

char *RealBigArcCot(char *in);

double d_asin(double in);

double d_acos(double in);

double d_atan(double in);

char *convert_radian(char *radian);

char *convert_degree(char *degree);

#endif //CAL_MATH_H
