#ifndef CAL_POLYNOMIAL_H
#define CAL_POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../task1/BigNumOps.h"
#include "../task1/RealNumOps.h"

int Cardano(char *a, char *b, char *c, char *d, char **p);

int Shengjin(char *a, char *b, char *c, char *d, char **p);

int RelativeEq(char *a, char *b);

int AnswerMatch(char **c, char **s);

#endif //CAL_POLYNOMIAL_H
