#ifndef CAL_POLYNOMIAL_H
#define CAL_POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../task1/BigNumOps.h"
#include "../task1/RealNumOps.h"

#define COMPARE_TOLERANT "0.000000000001"

int Cardano(char *a, char *b, char *c, char *d, char **p);

int Shengjin(char *a, char *b, char *c, char *d, char **p);

int RelativeEq(char *a, char *b, char *compare_tolerant);

int AnswerMatch(char **c, char **s, char *compare_tolerant);

#endif //CAL_POLYNOMIAL_H
