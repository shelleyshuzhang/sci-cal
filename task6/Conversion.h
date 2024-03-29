#ifndef CAL_CONVERSION_H
#define CAL_CONVERSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../task1/RealNumOps.h"
#include "../task1/BigNumOps.h"
#include "../task2/AlgeExp.h"

char *deep_copy(char *s, int offset);

char *dec_to_binary(char *dec_s);

char *dec_to_oct(char *dec_s);

char *dec_to_hex(char *dec_s);

char *binary_to_dec(char *bin_s);

char *oct_to_dec(char *oct_s);

char *hex_to_dec(char *hex_s);

char *clean_exp(char *exp);

#endif //CAL_CONVERSION_H
