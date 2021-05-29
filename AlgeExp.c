//
// Created by 张舒 on 5/29/21.
//

// TODO: FREE all malloc !!!!!!
// 开方用 ^(1/n) 表示

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "RealNumOps.h"
#include "BigNumOps.h"
#include "AlgeExp.h"

#define STACK_INIT_SIZE 400
#define STACK_INCREASE 200
#define BIG_N_INIT_SIZE 30
#define BIG_N_INCREASE 15

void cal_suffix(char *suffix, int len) {
    charStack exp;
    init_char_stack(&exp);
    int index = 0;
    char c;
    int is_digit = 0;

    while (index < len) {
        c = *(suffix + index);
        if (isdigit(c) || c == '.') {
            if (!is_digit) {
                push_char('$', &exp);
                if (c == '.') {
                    push_char('0', &exp);
                }
                is_digit = 1;
            }
            push_char(c, &exp);
            index++;
            continue;
        } else if (c == '$') {
            is_digit = 0;
            index++;
            continue;
        } else {
            char *bigN1;
            char *bigN2;
            bigN1 = (char *) malloc((BIG_N_INIT_SIZE) * sizeof(char));
            bigN2 = (char *) malloc((BIG_N_INIT_SIZE) * sizeof(char));
            int len1 = BIG_N_INIT_SIZE;
            int len2 = BIG_N_INIT_SIZE;
            bigN1 = pop_top_str(&exp, bigN1, len1);
            bigN1 = BigNumReverse(bigN1);
            bigN2 = pop_top_str(&exp, bigN2, len2);
            bigN2 = BigNumReverse(bigN2);

            if (bigN1[0] == '\0' || bigN2[0] == '\0') {
                printf("输入的表达式错误，运算符号与所需数字数量不匹配\n");
                exit(0);
            } else {
                char *result;
                if (c == '^') {
                    // TODO
                } else if (c == '*') {
                    result = RealBigNumMul(bigN1, bigN2);
                } else if (c == '/') {
                    result = RealBigNumDiv(bigN2, bigN1);
                } else if (c == '+') {
                    result = RealBigNumAdd(bigN1, bigN2);
                } else if (c == '-') {
                    result = RealBigNumSub(bigN2, bigN1);
                }
                free(bigN1);
                free(bigN2);
                int res_len = (int) strlen(result);
                push_top_str(&exp, result, res_len);
                free(result);
            }
            index++;
            continue;
        }
    }

    char *bigN3;
    bigN3 = (char *) malloc((BIG_N_INIT_SIZE) * sizeof(char));
    int len3 = BIG_N_INIT_SIZE;
    bigN3 = pop_top_str(&exp, bigN3, len3);

    bigN3 = BigNumReverse(bigN3);

    puts(bigN3);

    free(bigN3);
    clean_char_stack(&exp);

}

char *pop_top_str(charStack *s, char *str, int len) {
    int index = 0;
    while (!char_stack_empty(*s)) {

        if (index >= len - 2) {
            len *= 2;
            str = (char *) realloc(str, (len) * sizeof(char));
        }

        char s_top;
        pop_char(&s_top, s);
        if (s_top == '$') {
            str[index] = '\0';
            return str;
        } else {
            str[index++] = s_top;
        }
    }
    str[index] = '\0';
    return str;
}

void push_top_str(charStack *s, const char *str, int len) {
    int index = 0;
    if (len != 0) {
        push_char('$', s);
    }
    while (index < len) {
        push_char(*(str + index), s);
        index++;
    }
}

void init_char_stack(charStack *s) {
    s->base = (char *) malloc(STACK_INIT_SIZE * sizeof(char));
    if (!s->base) {
        printf("无法分配算术表达式栈存储空间\n");
        exit(0);
    }
    *(s->base) = '#';
    s->top = s->base;
    s->size = STACK_INIT_SIZE;
}

void pop_char(char *a, charStack *s) {
    if (char_stack_empty(*s)) {
        return;
    }
    *a = *(s->top);
    (s->top)--;
}

void top_char(char *a, charStack *s) {
    if (char_stack_empty(*s)) {
        return;
    }
    *a = *(s->top);
}

long char_stack_len(charStack s) {
    return s.top - s.base;
}

int char_stack_empty(charStack s) {
    return s.top == s.base;
}

void push_char(char c, charStack *s) {
    if (s->top - s->base == s->size) {
        s->size += STACK_INCREASE;
        s->base = (char *) realloc(s->base, s->size * sizeof(char));
        if (!s->base) {
            printf("无法分配算术表达式栈存储空间\n");
            exit(0);
        }
    }
    s->top++;
    *(s->top) = c;
}

void print_char_stack(charStack s) {
    do {
        printf("%c", *s.top);
        s.top--;
    } while (s.base < s.top);
}

void clean_char_stack(charStack *s) {
    s->top = s->base;
    free(s->base);
    s->size = 0;
}

/**
 * 逆波兰算法，中缀转后缀
 *
 * @param string
 * @param len
 */
char *infix_to_suffix(const char *string, int len, char *suffix) {
    charStack exp;
    init_char_stack(&exp);
    int index = 0;
    int suffix_index = 0;
    int suffix_len = len;
    int is_digit = 0;
    char ops[6] = {'(', '^', '*', '/', '+', '-'};
    char c;
    while (index < len) {
        c = *(string + index);

        if (suffix_index >= len - 2) {
            suffix_len *= 2;
            suffix = (char *) realloc(suffix, (suffix_len) * sizeof(char));
        }

        if (isdigit(c) || c == '.') {
            if (!is_digit) {
                is_digit = 1;
            }
            suffix[suffix_index++] = c;
            index++;

            if (index == len) {
                suffix[suffix_index++] = '$';
            }

            continue;
        } else {
            if (is_digit) {
                suffix[suffix_index++] = '$';
                is_digit = 0;
            }
            int is_op = 0;
            for (int i = 0; i < 6; i++) {
                if (ops[i] == c) {
                    is_op = 1;
                    break;
                }
            }
            if (is_op) {
                if (char_stack_empty(exp)) {
                    push_char(c, &exp);
                } else {
                    char s_top;
                    while (!char_stack_empty(exp)) {
                        top_char(&s_top, &exp);
                        if (s_top == '(' || higher_priority(c, s_top)) {
                            if (c == '(') {
                                if (index + 1 == len) {
                                    printf("输入表达式左右括号数量不匹配\n");
                                    exit(0);
                                }
                                char next = *(string + index + 1);
                                if (next == '-') {
                                    suffix[suffix_index++] = '0';
                                    suffix[suffix_index++] = '$';
                                }
                            }
                            push_char(c, &exp);
                            break;
                        } else {
                            pop_char(&s_top, &exp);
                            suffix[suffix_index++] = s_top;
                        }
                    }
                    if (char_stack_empty(exp)) {
                        push_char(c, &exp);
                    }
                }
                index++;
                continue;
            }
            if (c == ')') {
                char s_top;
                int valid = 0;
                while (!char_stack_empty(exp)) {
                    top_char(&s_top, &exp);
                    if (s_top == '(') {
                        pop_char(&s_top, &exp);
                        valid = 1;
                        break;
                    } else {
                        pop_char(&s_top, &exp);
                        suffix[suffix_index++] = s_top;
                    }
                }
                if (!valid) {
                    printf("输入表达式左右括号数量不匹配\n");
                    exit(0);
                }
                index++;
                continue;
            }
        }
        index++;
    }
    while (!char_stack_empty(exp)) {
        char s_top;
        pop_char(&s_top, &exp);
        if (s_top == '(') {
            printf("输入表达式左右括号数量不匹配\n");
        }
        suffix[suffix_index++] = s_top;
    }
    suffix[suffix_index] = '\0';
    clean_char_stack(&exp);
    puts(suffix);
    return suffix;
}

int higher_priority(char op1, char op2) {
    char op_list[4][2] = {{'(', ')'},
                          {'^', '\0'},
                          {'*', '/'},
                          {'+', '-'}};
    int index1 = -1, index2 = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            if (op_list[i][j] == op1) {
                index1 = i;
            }
            if (op_list[i][j] == op2) {
                index2 = i;
            }
            if (index1 != -1 && index2 != -1) {
                break;
            }
        }
    }
    return index1 < index2;
}