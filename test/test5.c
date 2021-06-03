#include <stdio.h>
#include <stdlib.h>
#include "../header.h"

char input[10][2][200] = {
        {"10000000000000000000000", "1776623460607489027640429549"},
        {"9018820267632691720887653113", "7479189517215109415136809078"},
        {"6122774001502686413768917378", "6122774001502686413768917378"},
        {"3650660146617897393436962804", "1030038554381063999741191295"},
        {"305392825537888532157758836", "6985431895113165704410012395"},
        {"0.3780502137502417", "0.7624961732183541"},
        {"-0.422502202901744", "0.014735203028707566"},
        {"0.43147969564671995", "0.6453613480130918"},
        {"-0.9438615681131504", "-0.1399529955883273"},
        {"305392825537888532.3480130918", "98543189511.7624961732183541"},
};

int main() {

//    char m[200];
//    printf("Please Input Number:\n");
//    scanf("%s", m);
//
//    char* result = RealBigArcSin(m);
//    printf("sin = %s\n", result);
//    char* res_cos = RealBigArcCos(m);
//    printf("cos = %s\n", res_cos);
//    char* res_t = RealBigNumTan(m);
//    char* res_tan = RealBigArcTan(res_t);
//    printf("tan = %s\n", res_t);
//    printf("arc tan = %s\n", res_tan);
//
//    printf("Please input Number:\n");
//    double f;
//    scanf("%lf", &f);
//    double res = d_asin(f);
//    printf("%lf\n", res);
//    double cos_v2 = d_acos(f);
//    printf("%lf\n", cos_v2);
//    double tan_v2 = d_atan(f);
//    printf("%lf\n", tan_v2);
//
//    printf("%lf\n", asin(f));
//    printf("%lf\n", acos(f));
//    printf("%lf", atan(f));

    char *sin, *cos, *sin2, *cos2, *one, *ln, *tan, *arc_sin, *arc_cos, *arc_tan;
    int i;
    char *a, *b;
    char m[200];
    for (i = 0 ; i < 10; i++) {
        printf("input %s %s\n", input[i][0], input[i][1]);
        a = input[i][0];
        b = input[i][1];

        sin = RealBigNumSin(a);
        printf("sin %s\n", sin);

        cos = RealBigNumCos(a);
        printf("cos %s\n", cos);

        tan = RealBigNumTan(a);
        printf("tan %s\n", tan);

        sin2 = RealBigNumPow(sin, 2);
        printf("sin2 %s\n", sin2);

        cos2 = RealBigNumPow(cos, 2);
        printf("cos2 %s\n", cos2);

        one = RealBigNumAdd(sin2, cos2);
        printf("one %s\n", one);

        ln = RealBigNumLn(a);
        printf("ln %s\n", ln);

        arc_sin = RealBigArcSin(sin);
        arc_sin = convert_radian(arc_sin);
        printf("arc sin %s\n", arc_sin);

        arc_cos = RealBigArcCos(cos);
        arc_cos = convert_radian(arc_cos);
        printf("arc cos %s\n", arc_cos);

        arc_tan = RealBigArcTan(tan);
        arc_tan = convert_radian(arc_tan);
        printf("arc tan %s\n", arc_tan);

        free(sin);
        free(cos);
        free(tan);
        free(arc_sin);
        free(arc_cos);
        free(arc_tan);
        free(ln);
    }
    printf("Please Input Number:");
    scanf("%s", m);

    sin = RealBigNumSin(m);
    printf("sin %s\n", sin);

    cos = RealBigNumCos(m);
    printf("cos %s\n", cos);

    tan = RealBigNumTan(m);
    printf("tan %s\n", tan);

    sin2 = RealBigNumPow(sin, 2);
    printf("sin2 %s\n", sin2);

    cos2 = RealBigNumPow(cos, 2);
    printf("cos2 %s\n", cos2);

    one = RealBigNumAdd(sin2, cos2);
    printf("one %s\n", one);

    arc_sin = RealBigArcSin(sin);
    arc_sin = convert_radian(arc_sin);
    printf("arc sin %s\n", arc_sin);

    arc_cos = RealBigArcCos(cos);
    arc_cos = convert_radian(arc_cos);
    printf("arc cos %s\n", arc_cos);

    arc_tan = RealBigArcTan(tan);
    arc_tan = convert_radian(arc_tan);
    printf("arc tan %s\n", arc_tan);

    ln = RealBigNumLn(m);
    printf("ln %s\n", ln);

    free(sin);
    free(cos);
    free(tan);
    free(arc_sin);
    free(arc_cos);
    free(arc_tan);
    free(ln);

    return 0;

}