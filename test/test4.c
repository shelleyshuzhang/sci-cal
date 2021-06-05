#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../header.h"

#define COMPARE_TOLERANT "0.000000000001"

int main()
{
	char input[4][50];
	char *cp[5], *sp[5];
	int i, j;
#if 1
	srand(time(NULL));
	for (i = 0; i < 1000; i++) {
		printf("i = %d ", i);
		sprintf(input[0], "%ld", random() * ((random()%2) ? 1 : -1));
		sprintf(input[1], "%ld", random() * ((random()%2) ? 1 : -1));
		sprintf(input[2], "%ld", random() * ((random()%2) ? 1 : -1));
		sprintf(input[3], "%ld", random() * ((random()%2) ? 1 : -1));
		printf("%s %s %s %s\n", input[0], input[1], input[2], input[3]);
		Cardano(input[0], input[1], input[2], input[3], cp);
		Shengjin(input[0], input[1], input[2], input[3], sp);
		if (AnswerMatch(cp, sp, COMPARE_TOLERANT) < 0) {
			printf("%d %sx^3 + %sx^2 + %sx + %s = 0\n", i, input[0], input[1], input[2], input[3]);
			for (j = 0; j < 5; j++) {
				printf("%s %s\n", cp[j], sp[j]);
			}
		}
		for (j = 0; j < 5; j++) {
			free(cp[j]);
			free(sp[j]);
		}
	}
#else
    int cj, sj;
	cj = Cardano("1", "-6", "-234", "-8", cp);
	sj = Shengjin("1", "-6", "-234", "-8", sp);
	printf("%d\n", AnswerMatch(cp, sp));
    if (AnswerMatch(cp, sp) < 0) {
        for (j = 0; j < 5; j++) {
            printf("%s %s\n", cp[j], sp[j]);
        }
    }
	cj = Cardano("-70", "0", "-6", "-4", cp);
	sj = Shengjin("-70", "0", "-6", "-4", sp);
	printf("%d\n", AnswerMatch(cp, sp));
	if (AnswerMatch(cp, sp) < 0) {
			for (j = 0; j < 5; j++) {
				printf("%s %s\n", cp[j], sp[j]);
			}
	}
	cj = Cardano("1", "0", "-12", "16", cp);
	sj = Shengjin("1", "0", "-12", "16", sp);
	printf("%d\n", AnswerMatch(cp, sp));
	Cardano("722308542", "1820388464", "933110197", "6939507", cp);
	Shengjin("722308542", "1820388464", "933110197", "6939507", sp);
	if (AnswerMatch(cp, sp) < 0) {
			for (j = 0; j < 5; j++) {
				printf("%s %s\n", cp[j], sp[j]);
			}
	}
	//printf("%d\n", Cardano("1396918184", "376696776", "-2060975266", "-242588954", cp));
	Cardano("139691818402343422343243242",
         "3766",
         "-2060975266432423432423",
         "-24258895443242342432432", cp);
	Shengjin("139691818402343422343243242",
          "3766",
             "-2060975266432423432423",
             "-24258895443242342432432", sp);
	if (AnswerMatch(cp, sp) < 0) {
			for (j = 0; j < 5; j++) {
				printf("%s %s\n", cp[j], sp[j]);
			}
	}
#endif
	return 0;
}
