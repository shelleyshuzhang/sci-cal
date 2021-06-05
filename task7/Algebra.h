#ifndef CAL_ALGEBRA_H
#define CAL_ALGEBRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../task1/BigNumOps.h"
#include "../task1/RealNumOps.h"

char *IntBigNumGcd(char *a, char *b);

void Gauss(char **aa, char **ab, char **x, int n);

#endif //CAL_ALGEBRA_H
