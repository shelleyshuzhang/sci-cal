#include "Conversion.h"

#define BIN_MAX_LEN 100
#define OCT_MAX_LEN 70
#define HEX_MAX_LEN 30

char hex[16] = {'0', '1', '2', '3', '4', '5', '6',
                '7', '8', '9', 'A', 'B', 'C', 'D',
                'E', 'F'};
char octal[8] = {'0', '1', '2', '3', '4', '5', '6',
                 '7'};
char binary[2] = {'0', '1'};
char dec[10] = {'0', '1', '2', '3', '4',
                '5', '6', '7', '8', '9'};
char hex_leftover[16][3] = {"0\0", "1\0", "2\0",
                            "3\0", "4\0", "5\0",
                            "6\0", "7\0", "8\0",
                            "9\0", "10", "11",
                            "12", "13", "14",
                            "15"};

char *deep_copy(char *s, int offset) {
    unsigned long len = strlen(s);
    int index = offset;
    char *copy;
    copy = (char *) malloc(sizeof(char) * (len + offset + 1));
    memset(copy, '\0', (len + offset + 1));
    while (index < len + offset) {
        copy[index] = s[index - offset];
        index = index + 1;
    }
    copy[index] = '\0';
    return copy;
}

// all positive integer
char *dec_to_binary(char *dec_s) {
    int neg = 0;
    if (RealBigNumCmp(dec_s, "0") < 0) {
        neg = 1;
        dec_s = RealBigNumSub("0", dec_s);
    }
    dec_s = make_prec(dec_s, -1);
    char *bin_s;
    bin_s = (char *) malloc(sizeof(char) * BIN_MAX_LEN);
    memset(bin_s, '\0', BIN_MAX_LEN);
    int len = BIN_MAX_LEN;
    unsigned long index = 0;
    char *digit = dec_s;
    char *leftover;
    while (RealBigNumCmp(digit, "0") > 0) {
        if (index > len - 3) {
            len *= 2;
            bin_s = realloc(bin_s, sizeof(char) * len);
        }
        char *copy;
        copy = deep_copy(digit, 0);
        digit = RealBigNumDiv(digit, "2");
        digit = make_prec(digit, -1);
        leftover = RealBigNumSub(copy,
                                 RealBigNumMul(digit, "2"));
        int encoded = atoi(leftover);
        bin_s[index++] = binary[encoded];
        free(copy);
    }
    bin_s = BigNumReverse(bin_s);
    bin_s[index] = '\0';
    free(digit);
    free(leftover);
    if (neg) {
        // TODO: 有时间可以处理有符号数情况
        return bin_s;
    } else {
        char *start;
        start = deep_copy(bin_s, 2);
        free(bin_s);
        start[0] = '0';
        start[1] = 'b';
        return start;
    }
}

// all positive integer
char *dec_to_oct(char *dec_s) {
    int neg = 0;
    if (RealBigNumCmp(dec_s, "0") < 0) {
        neg = 1;
        dec_s = RealBigNumSub("0", dec_s);
    }
    dec_s = make_prec(dec_s, -1);
    char *oct_s;
    oct_s = (char *) malloc(sizeof(char) * OCT_MAX_LEN);
    memset(oct_s, '\0', OCT_MAX_LEN);
    int len = OCT_MAX_LEN;
    unsigned long index = 0;
    char *digit = dec_s;
    char *leftover;
    while (RealBigNumCmp(digit, "0") > 0) {
        if (index > len - 3) {
            len *= 2;
            oct_s = realloc(oct_s, sizeof(char) * len);
        }
        char *copy;
        copy = deep_copy(digit, 0);
        digit = RealBigNumDiv(digit, "8");
        digit = make_prec(digit, -1);
        leftover = RealBigNumSub(copy,
                                 RealBigNumMul(digit, "8"));
        int encoded = atoi(leftover);
        oct_s[index++] = octal[encoded];
        free(copy);
    }
    oct_s = BigNumReverse(oct_s);
    oct_s[index] = '\0';
    free(digit);
    free(leftover);
    if (neg) {
        // TODO: 有时间可以处理有符号数情况
        return oct_s;
    } else {
        char *start;
        start = deep_copy(oct_s, 2);
        free(oct_s);
        start[0] = '0';
        start[1] = 'o';
        return start;
    }
}

// all positive integer
char *dec_to_hex(char *dec_s) {
    int neg = 0;
    if (RealBigNumCmp(dec_s, "0") < 0) {
        neg = 1;
        dec_s = RealBigNumSub("0", dec_s);
    }
    dec_s = make_prec(dec_s, -1);
    char *hex_s;
    hex_s = (char *) malloc(sizeof(char) * HEX_MAX_LEN);
    memset(hex_s, '\0', HEX_MAX_LEN);
    int len = HEX_MAX_LEN;
    unsigned long index = 0;
    char *digit = dec_s;
    char *leftover;
    while (RealBigNumCmp(digit, "0") > 0) {
        if (index > len - 3) {
            len *= 2;
            hex_s = realloc(hex_s, sizeof(char) * len);
        }
        char *copy;
        copy = deep_copy(digit, 0);
        digit = RealBigNumDiv(digit, "16");
        digit = make_prec(digit, -1);
        leftover = RealBigNumSub(copy,
                                 RealBigNumMul(digit, "16"));
        int encoded = atoi(leftover);
        hex_s[index++] = hex[encoded];
        free(copy);
    }
    hex_s = BigNumReverse(hex_s);
    hex_s[index] = '\0';
    free(digit);
    free(leftover);
    if (neg) {
        // TODO: 有时间可以处理有符号数情况
        return hex_s;
    } else {
        char *start;
        start = deep_copy(hex_s, 2);
        free(hex_s);
        start[0] = '0';
        start[1] = 'x';
        return start;
    }
}

char *binary_to_dec(char *bin_s) {
    int neg = 0;
    if (neg) {
        // TODO: 有时间可以处理有符号数情况
    }

    int index = 2;
    char *res = RealBigNumAdd("0", "0");
    while (bin_s[index] != '\0') {
        int decoded = bin_s[index++] - '0';
        if (decoded <= 1 && decoded >= 0) {
            // * 2 + decoded
            char leftover[2];
            leftover[1] = '\0';
            leftover[0] = binary[decoded];
            res = RealBigNumMul(res, "2");
            res = RealBigNumAdd(res, leftover);
        }
    }

    return res;
}

char *oct_to_dec(char *oct_s) {
    int neg = 0;
    if (neg) {
        // TODO: 有时间可以处理有符号数情况
    }

    int index = 2;
    char *res = RealBigNumAdd("0", "0");
    while (oct_s[index] != '\0') {
        int decoded = oct_s[index++] - '0';
        if (decoded <= 7 && decoded >= 0) {
            // * 8 + decoded
            char leftover[2];
            leftover[1] = '\0';
            leftover[0] = octal[decoded];
            res = RealBigNumMul(res, "8");
            res = RealBigNumAdd(res, leftover);
        }
    }

    return res;
}

char *hex_to_dec(char *hex_s) {
    int neg = 0;
    if (neg) {
        // TODO: 有时间可以处理有符号数情况
    }

    int index = 2;
    char *res = RealBigNumAdd("0", "0");

    while (hex_s[index] != '\0') {
        char current = hex_s[index++];
        int decoded;
        if (isnumber(current)) {
            decoded = current - '0';
        } else {
            current = (char) tolower(current);
            decoded = 10 + (current - 'a');
        }
        if (decoded <= 15 && decoded >= 0) {
            // * 16 + decoded
            res = RealBigNumMul(res, "16");
            res = RealBigNumAdd(res, hex_leftover[decoded]);
        }
    }

    return res;
}

char *clean_exp(char *exp) {
    unsigned long len = strlen(exp);
    char *res = (char *) malloc(sizeof(char) * len);
    unsigned long res_len = len;
    int res_index = 0;
    int index = 0;
    int need_decode = 0;

    char *to_decode;
    to_decode = (char *) malloc(sizeof(char) * BIN_MAX_LEN);
    memset(to_decode, '\0', BIN_MAX_LEN);
    int decode_len = HEX_MAX_LEN;
    int decode_index = 0;
    int decode_case = -1;

    while (exp[index] != '\0' || need_decode != 0) {
        if (exp[index] == '\0') {
            char *decoded;

            switch (decode_case) {
                case 1:
                    // hex case
                    decoded = hex_to_dec(to_decode);
                    break;
                case 2:
                    // oct case
                    decoded = oct_to_dec(to_decode);
                    break;
                case 3:
                    // binary case
                    decoded = binary_to_dec(to_decode);
                    break;
                default:
                    continue;
            }

            int i = 0;
            while (decoded[i] != '\0') {

                if (res_index > res_len - 3) {
                    res_len *= 2;
                    res = realloc(res,
                                  sizeof(char) * res_len);
                }

                res[res_index++] = decoded[i++];
            }
            free(decoded);

            memset(to_decode, '\0', decode_len);
            need_decode = 0;
            decode_index = 0;
            decode_case = -1;

        } else {
            char c = exp[index++];

            if (res_index > res_len - 3) {
                res_len *= 2;
                res = realloc(res,
                              sizeof(char) * res_len);
            }

            if (need_decode && (isnumber(c) || ishexnumber(c))) {

                if (decode_index > decode_len - 3) {
                    decode_len *= 2;
                    to_decode = realloc(to_decode,
                                        sizeof(char) * decode_len);
                }

                // hex number lower -> upper
                if (ishexnumber(c)) {
                    c = (char) toupper(c);
                }

                to_decode[decode_index++] = c;

            } else if (need_decode) {

                char *decoded;

                switch (decode_case) {
                    case 1:
                        // hex case
                        decoded = hex_to_dec(to_decode);
                        break;
                    case 2:
                        // oct case
                        decoded = oct_to_dec(to_decode);
                        break;
                    case 3:
                        // binary case
                        decoded = binary_to_dec(to_decode);
                        break;
                    default:
                        continue;
                }

                int i = 0;
                while (decoded[i] != '\0') {

                    if (res_index > res_len - 3) {
                        res_len *= 2;
                        res = realloc(res,
                                      sizeof(char) * res_len);
                    }

                    res[res_index++] = decoded[i++];
                }

                res[res_index++] = c;

                free(decoded);

                memset(to_decode, '\0', decode_len);
                need_decode = 0;
                decode_index = 0;
                decode_case = -1;

            } else if (c == '0') {
                if (index < len) {
                    char c_next = exp[index];

                    c_next = (char) tolower(c_next);
                    if (c_next == 'b') {
                        need_decode = 1;
                        decode_case = 3;
                        to_decode[decode_index++] = '0';
                        to_decode[decode_index++] = c_next;
                        index++;
                        continue;
                    } else if (c_next == 'x') {
                        need_decode = 1;
                        decode_case = 1;
                        to_decode[decode_index++] = '0';
                        to_decode[decode_index++] = c_next;
                        index++;
                        continue;
                    } else if (c_next == 'o') {
                        need_decode = 1;
                        decode_case = 2;
                        to_decode[decode_index++] = '0';
                        to_decode[decode_index++] = c_next;
                        index++;
                        continue;
                    }
                }
                res[res_index++] = c;
            } else {
                res[res_index++] = c;
            }
        }
    }
    res[res_index] = '\0';

    free(to_decode);

    return res;

}
