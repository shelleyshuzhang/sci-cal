#ifndef _ALL_HEADER_H_
#define _ALL_HEADER_H_

#include "BigNumOps.h"
#include "RealNumOps.h"
#include "AlgeExp.h"
#include "Quadratic.h"
#include "Conversion.h"

int Cardano(char *a, char *b, char *c, char *d, char **result);
int Shengjin(char *a, char *b, char *c, char *d, char **result);
int AnswerMatch(char **c, char **s);

void Gauss(char **aa, char **ab, char **x, int n);

#endif
