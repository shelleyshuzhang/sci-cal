#include "Quadratic.h"

void quadratic_equ(char *a, char *b, char *c) {

    if (RealBigNumCmp(a, "0") != 0) { // if a != 0

        char *b_sqr, *ac, *ac_4, *two_a, *b_neg;

        b_sqr = RealBigNumPow(b, 2); // b ^ 2
        ac = RealBigNumMul(a, c); // ac
        ac_4 = RealBigNumMul(ac, "4"); // 4ac
        char *delta = RealBigNumSub(b_sqr, ac_4); // b^2 - 4ac

        two_a = RealBigNumMul(a, "2"); // 2a
        b_neg = RealBigNumSub("0", b); // -b

        int comp = RealBigNumCmp(delta, "0");

        if (comp != 0) {

            char *sqrt_delta;
            char *neg_delta;
            if (comp > 0) {
                // delta > 0
                // (delta)^(1/2)
                sqrt_delta = RealBigNumSqrt(delta);

            } else {
                // delta < 0
                // (-delta)^(1/2)
                neg_delta = delta;
                delta = RealBigNumSub("0", neg_delta);
                sqrt_delta = RealBigNumSqrt(delta);

            }

            char *delta_a2, *b_a2;

            // (-b) / 2a
            b_a2 = RealBigNumDiv(b_neg, two_a);
            // (delta)^(1/2) / 2a
            delta_a2 = RealBigNumDiv(sqrt_delta, two_a);

            if (comp > 0) {
                char *x1, *x2;

                // (-b + (delta)^(1/2)) / 2a
                x1 = RealBigNumAdd(b_a2, delta_a2);
                // (-b - (delta)^(1/2)) / 2a
                x2 = RealBigNumSub(b_a2, delta_a2);

                printf("实数系一元二次方程 %sx^2 + %sx + %s "
                       "有两个实数解：\n",
                       a, b, c);
                x1 = make_prec(x1, QUA_ACCU);
                x2 = make_prec(x2, QUA_ACCU);
                printf("x1 = %s\n", x1);
                printf("x2 = %s\n", x2);

                free(x1);
                free(x2);
            } else {
                printf("实数系一元二次方程 %sx^2 + %sx + %s "
                       "有两个虚数解：\n",
                       a, b, c);
                b_a2 = make_prec(b_a2, QUA_ACCU);
                delta_a2 = make_prec(delta_a2, QUA_ACCU);
                printf("x1 = %s + %si\n", b_a2, delta_a2);
                printf("x2 = %s - %si\n", b_a2, delta_a2);
            }

            free(sqrt_delta);
            free(delta_a2);
            free(b_a2);

        } else { // delta == 0

            // x1 = x2 = (-b) / 2a
            char *x;
            x = RealBigNumDiv(b_neg, two_a);

            printf("实数系一元二次方程 %sx^2 + %sx + %s "
                   "有两个相等实数解：\n",
                   a, b, c);
            x = make_prec(x, QUA_ACCU);
            printf("x1 = x2 = %s\n", x);

            free(x);

        }

        free(b_sqr);
        free(ac);
        free(ac_4);
        free(two_a);
        free(b_neg);
        free(delta);

    } else { // a == 0
        // x = -c/b
        char *c_neg = RealBigNumSub("0", c);
        char *x = RealBigNumDiv(c_neg, b);
        printf("实数系一元一次方程 %sx^2 + %sx + %s "
               "有一个实数解：\n",
               a, b, c);
        x = make_prec(x, QUA_ACCU);
        printf("x = %s\n", x);

        free(c_neg);
        free(x);
    }

}
