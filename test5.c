#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

int main()
{
    char *sin, *cos, *sin2, *cos2, *one, *ln, *gcd;
    int i;
	char *a, *b;
	char m[200];
    for (i = 0 ; i < 10; i++) {
        printf("input %s %s\n", input[i][0], input[i][1]);
        a = input[i][0];
        b = input[i][1];
        sin = RealBigNumSin(a);
        cos = RealBigNumCos(a);
        sin2 = RealBigNumPow(sin, 2);
        cos2 = RealBigNumPow(cos, 2);
        one = RealBigNumAdd(sin2, cos2);
        ln = RealBigNumLn(a);

        printf("sin %s\n", sin);
        printf("cos %s\n", cos);
        printf("sin2 %s\n", sin2);
        printf("cos2 %s\n", cos2);
        printf("one %s\n", one);
        printf("ln %s\n", ln);
        free(sin);
        free(cos);
        free(sin2);
        free(cos2);
        free(one);
        free(ln);
    }
	printf("Please Input Number:");
	scanf("%s", m);
	sin = RealBigNumSin(m);
	cos = RealBigNumCos(m);
	sin2 = RealBigNumPow(sin, 2);
	cos2 = RealBigNumPow(cos, 2);
	one = RealBigNumAdd(sin2, cos2);
	ln = RealBigNumLn(m);

	printf("sin %s\n", sin);
	printf("cos %s\n", cos);
	printf("sin2 %s\n", sin2);
	printf("cos2 %s\n", cos2);
	printf("one %s\n", one);
	printf("ln %s\n", ln);
	free(sin);
	free(cos);
	free(sin2);
	free(cos2);
	free(one);
	free(ln);
	return 0;
}
