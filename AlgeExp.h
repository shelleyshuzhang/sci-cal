//
// Created by 张舒 on 5/29/21.
//

#ifndef CAL_ALGEEXP_H
#define CAL_ALGEEXP_H

typedef struct stack {
    // stack base
    char *base;
    // stack top
    char *top;
    // stack size
    int size;
} charStack;

char *infix_to_suffix(const char *, int, char *);

void init_char_stack(charStack *);

void pop_char(char *a, charStack *s);

void top_char(char *a, charStack *s);

long char_stack_len(charStack s);

int char_stack_empty(charStack s);

void push_char(char c, charStack *s);

void print_char_stack(charStack s);

void clean_char_stack(charStack *s);

int higher_priority(char, char);

char* pop_top_str(charStack *s, char* str, int len);

void push_top_str(charStack *s, const char* str, int len);

void cal_suffix(char* suffix, int len);

#endif //CAL_ALGEEXP_H
