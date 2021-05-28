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
    char *add, *sub, *mul, *div, *pow, *sqrt, *root; 
    int i;
	char *a, *b;
	//scanf("%s %s", a, b); //  We can select element from keyboard input;   
    for (i = 0 ; i < 10; i++) {
        printf("input %s %s\n", input[i][0], input[i][1]);
        a = input[i][0];
        b = input[i][1];
        add = RealBigNumAdd(a, b);
        sub = RealBigNumSub(a, b);
        mul = RealBigNumMul(a, b);
        div = RealBigNumDiv(a, b);
        pow = RealBigNumPow(a, 10);
        sqrt = RealBigNumSqrt(a);
		root = RealBigNumRoot(a, 3);

        printf("add %s\n", add);
        printf("sub %s\n", sub);
        printf("mul %s\n", mul);
        printf("div %s\n", div);
        printf("pow %s\n", pow);
        printf("sqrt %s\n", sqrt);
        printf("root %s\n", root);
        free(add);
        free(sub);
        free(mul);
        free(div);
        free(pow);
        free(sqrt);
        free(root);
    }
	return 0;
}
