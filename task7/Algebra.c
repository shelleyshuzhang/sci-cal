#include "Algebra.h"

void print_matrix(char **a, int n) {
    for (int i = 0; i < n * n; i++) {
        printf("%s  ", a[i]);
        if (i == n - 1) {
            printf("\n");
        }
    }
}

char *IntBigNumGcd(char *a, char *b) {
    char *point_a, *point_b, *point_c;
    char *c;
    int lena = strlen(a);
    int lenb = strlen(b);
    char *rem;

    point_a = fill_zero(a, lena, lena);
    point_b = fill_zero(b, lenb, lenb);

    while (1) {
        if (UnsignedBigNumCmp(point_a, point_b) > 0) {
            rem = malloc(lenb + 1);
            c = RealBigNumDiv_Rem(point_a, point_b, rem);
            free(c);
            free(point_a);
            point_a = rem;
            point_c = point_b;
        } else {
            rem = malloc(lena + 1);
            c = RealBigNumDiv_Rem(point_b, point_a, rem);
            free(c);
            free(point_b);
            point_b = rem;
            point_c = point_a;
        }
        if (rem[0] == '0' && rem[1] == 0) {
            free(rem);
            break;
        }
    }

    return format_real(point_c, 0, 0);
}


char **g_dupstrs(char **a, int n) {
    char **b = malloc(sizeof(char *) * n);
    int i;
    for (i = 0; i < n; i++) {
        b[i] = malloc(sizeof(char) * strlen(a[i]));
        strcpy(b[i], a[i]);
    }
    return b;
}

void Gauss(char **aa, char **ab, char **x, int n) {
    int i, j, k, exchange_line, exchange_flag = 0;
    char *temp, *max;
    char *t1, *t2;

    char **a = g_dupstrs(aa, n * n);
    char **b = g_dupstrs(ab, n);

    for (k = 0; k < n - 1; k++) { //k迭代次数
        max = a[k * n + k];
        for (i = k + 1; i < n; i++) { //寻找主元，i行号
            //if (fabs(max) < fabs(a[n * i + k]))
            if (RealBigNumAbsCmp(max, a[n * i + k]) < 0) {
                max = a[n * i + k];
                exchange_flag = 1;     //交换标志
                exchange_line = n * i; //记录需要交换的行号
            }
        }

        if (RealBigNumAbsCmp(max, "0") > 0) {

            if (exchange_flag) { //换行，j列号
                for (j = 0; j < n; j++) {
                    temp = a[exchange_line + j]; //对系数矩阵操作
                    a[exchange_line + j] = a[k * n + j];
                    a[k * n + j] = temp;
                }
                temp = b[exchange_line / n]; //对结果向量操作
                b[exchange_line / n] = b[k];
                b[k] = temp;
                exchange_flag = 0; //清除交换标志
            }

            for (i = k + 1; i < n; i++) { //消元
                //temp = a[i * n + k] / a[k * n + k];

                temp = RealBigNumDiv(a[i * n + k], a[k * n + k]);

                //  b[i] = b[i] - b[k] * temp;
                // 对结果向量操作
                t1 = RealBigNumMul(b[k], temp);
                t2 = RealBigNumSub(b[i], t1);
                free(t1);
                free(b[i]);
                b[i] = t2;

                for (j = k; j < n; j++) {
                    // a[i * n + j] = a[i * n + j] - a[k * n + j] * temp;
                    // 对系数矩阵操作
                    t1 = RealBigNumMul(a[k * n + j], temp);
                    t2 = RealBigNumSub(a[i * n + j], t1);
                    free(t1);
                    free(a[i * n + j]);
                    a[i * n + j] = t2;
                }
                free(temp);
            }
        }

    }
    for (i = n - 1; i > -1; i--) { //回代
        temp = b[i];
        for (j = n - 1; j > i; j--) {
            //temp = temp - a[n * i + j] * x[j];
            t1 = RealBigNumMul(a[n * i + j], x[j]);
            t2 = RealBigNumSub(temp, t1);
            free(temp);
            free(t1);
            temp = t2;
        }

        x[i] = RealBigNumDiv(temp, a[i * n + i]);
    }

    for (i = 0; i < n * n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
}
