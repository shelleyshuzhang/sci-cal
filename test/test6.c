#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header.h"

#define FINAL_ACCURACY 10

int main() {

    char *str;
    char *bin, *oct, *hexadecimal;
    bin = "0b1110111011";
    oct = "0o337";
    hexadecimal = "0xAA13D";
    str = binary_to_dec(bin);
    printf("%s\n", str);
    str = oct_to_dec(oct);
    printf("%s\n", str);
    str = hex_to_dec(hexadecimal);
    printf("%s\n", str);

    free(str);


    char *input;
    input = (char *) malloc(100 * sizeof(char));
    memset(input, '\0', 100);

    char c;
    int index = 0;

    while ((c = getchar()) != '\n' && index < 100) {
        input[index++] = c;
    }
    input[index] = '\0';

    char *cleaned_input;
    cleaned_input = clean_exp(input);
    printf("%s\n", cleaned_input);

    char *res = infix_to_suffix(cleaned_input,
                                (int) strlen(cleaned_input));
    char *result;
    result = cal_suffix(res, (int) strlen(res));
    result = make_prec(result, FINAL_ACCURACY);
    printf("%s\n", result);
    char *c_encoded = dec_to_binary(result);
    printf("%s\n", c_encoded);
    c_encoded = dec_to_oct(result);
    printf("%s\n", c_encoded);
    c_encoded = dec_to_hex(result);
    printf("%s\n", c_encoded);

    free(input);
    free(cleaned_input);

    free(res);
    free(result);
    free(c_encoded);

    return 0;
}