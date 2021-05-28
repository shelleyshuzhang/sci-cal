#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

int main(int argc, char* argv[])
{
#if 0
    int n           = 4;
    char *a[4 * 4] = { "1", "1", "0", "3",
                        "2", "1", "-1", "1",
                        "3", "-1", "-1", "3",
                        "-1", "2", "3", "-1" };
    char *b[4]     = { "4", "1", "-3", "4" };
    char *x[4]     = {};
#else
    int n           = 3;
    char *a[3 * 3] = { "2", "-1", "3",
                        "4", "2", "5",
                        "1", "2", "0", };
    char *b[3]     = { "1", "4", "7" };
    char *x[3]     = {};
#endif
	char *gcd = IntBigNumGcd("89370", "76372");
	printf("gcd(%s %s) = %s\n", "89370", "76372", gcd);

    printf("增广矩阵\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%s\t", a[i * n + j]);
        }
        printf("%s\n", b[i]);
    }
    printf("解向量\n");
    Gauss(a, b, x, n);
    for (int i = 0; i < n; i++)
        printf("%s\t", x[i]);
    printf("\n");

    return 0;
}
