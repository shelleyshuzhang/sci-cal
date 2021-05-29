//
// Created by 张舒 on 5/28/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    char *input;
    input = (char *) malloc(100 * sizeof(char));

    char c;
    int index = 0;

    while ((c = getchar()) != '\n' && index < 100) {
        input[index] = c;
        index++;
    }

    char *suffix;
    suffix = (char *) malloc((index + 1) * sizeof(char));

    char *res = infix_to_suffix(input, index, suffix);

    puts(res);

    cal_suffix(res, (int)strlen(res));

    free(input);

    return 0;
}