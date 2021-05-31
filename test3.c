#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {

    char *a;
    char *b;
    char *c;
    a = (char*) malloc(sizeof(char) * 100);
    memset(a, '\0', 100);
    b = (char*) malloc(sizeof(char) * 100);
    memset(b, '\0', 100);
    c = (char*) malloc(sizeof(char) * 100);
    memset(c, '\0', 100);

    printf("请输入一元二次方程的系数：\n");

    printf("请输入a的值：\n");
    int index = 0;
    char ch;
    while ((ch = getchar()) != '\n' && index < 100) {
        a[index++] = ch;
    }
    while (ch != '\n' && index < 100) {
        ch = getchar();
    }

    printf("请输入b的值：\n");
    index = 0;
    while ((ch = getchar()) != '\n' && index < 100) {
        b[index++] = ch;
    }
    while (ch != '\n' && index < 100) {
        ch = getchar();
    }

    printf("请输入c的值：\n");
    index = 0;
    while ((ch = getchar()) != '\n' && index < 100) {
        c[index++] = ch;
    }
    while (ch != '\n' && index < 100) {
        ch = getchar();
    }

    quadratic_equ(a, b, c);

    free(a);
    free(b);
    free(c);

    return 0;
}