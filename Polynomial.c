#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "BigNumOps.h"
#include "RealNumOps.h"

//#define DEBUG
char *Mul3(char *a, char *b, char *c)
{
	char *t1, *t2;
   	t1 = RealBigNumMul(a, b);
	t2 = RealBigNumMul(t1, c);
	free(t1);
	return t2;
}

int Cardano(char *a, char *b, char *c, char *d, char **p)
{
	char *n2, *m3, *n2pm3;
	char *n, *m;
	char *alpha, *beta;
	char *apb, *asb;
	char *bd3a;
	char *a3, *b3, *a2, *b2, *ac, *abc, *a2d;
	char *t1, *t2, *t3, *t4;
	char *y1, *y2, *y2_i, *y3, *y3_i;
	char *x1, *x2, *x3;
	char *sqrt3 = RealBigNumSqrt("3");
	char *cmpm3, *cmpn2;
	int judge = 0;

	a2 =RealBigNumPow(a, 2);
	b2 =RealBigNumPow(b, 2);
	a3 =RealBigNumMul(a2, a);
	b3 =RealBigNumMul(b2, b);
	ac = RealBigNumMul(a, c);
	abc = RealBigNumMul(ac, b);
	a2d = RealBigNumMul(a2, d);

	t1 = RealBigNumMul(a, "3");
	bd3a = RealBigNumDiv(b, t1);
	free(t1);

	t1 = RealBigNumMul(ac, "3");
	free(ac);

	t2 = RealBigNumSub(t1, b2);	 // t2 = 3ac - b2;
	free(t1);
	free(b2);
	cmpm3 = RealBigNumPow(t2, 3);

	t3 = RealBigNumMul(a2, "3");  // t3 = 3a2;
	free(a2);

	t1 = RealBigNumDiv(t2, t3);  // 3 * m = t2 / t3
	free(t2);
	free(t3);

	m = RealBigNumDiv(t1, "3");
	free(t1);

	t1 = RealBigNumMul(b3, "2");   // t1 = 2b3;
	free(b3);
	t2 = RealBigNumMul(abc, "9");  // t2 = 9abc
	free(abc);
	t3 = RealBigNumMul(a2d, "27"); // t3 = 27a2d
	free(a2d);
	t4 = RealBigNumSub(t1, t2);
	free(t1);
	free(t2);
	t1 = RealBigNumAdd(t3, t4);
	free(t3);
	free(t4);

	cmpn2 = RealBigNumPow(t1, 2);

	t2 = RealBigNumMul(a3, "27");
	free(a3);
	t3 = RealBigNumDiv(t1, t2);
	free(t1);
	free(t2);

	n = RealBigNumDiv(t3, "2");
	free(t3);

	n2 = RealBigNumPow(n, 2);
	m3 = RealBigNumPow(m, 3);
	n2pm3 = RealBigNumAdd(n2, m3);

	t1 = RealBigNumMul(cmpm3, "4");
	t2 = RealBigNumAdd(t1, cmpn2);
	judge = RealBigNumCmp(n2pm3, "0");
	free(t1);
	free(t2);
	free(cmpm3);
	free(cmpn2);
    if (judge >= 0) {
		t1 = RealBigNumSqrt(n2pm3);
		t2 = RealBigNumSub(t1, n);
		t3 = RealBigNumAdd(t1, n);
		t4 = RealBigNumSub("0", t3);
		free(t3);
		alpha  = RealBigNumRoot(t2, 3);
		beta  = RealBigNumRoot(t4, 3);
		free(t2);
		free(t4);
		y1 = RealBigNumAdd(alpha, beta);
		x1 = RealBigNumSub(y1, bd3a);
		y2 = RealBigNumDiv(y1, "-2");
		x2 = RealBigNumSub(y2, bd3a);
		x3 = RealBigNumSub(y2, bd3a);
		t1 = RealBigNumSub(alpha, beta);
		t2 = RealBigNumDiv(t1, "2");
		y2_i = RealBigNumMul(t2, sqrt3);
		y3_i = RealBigNumMul(y2_i, "-1");
		p[0] = x1;
		p[1] = x2;
		p[2] = y2_i;
		p[3] = x3;
		p[4] = y3_i;
		free(y1);
		free(y2);
		//free(y3);
		free(t2);
		free(alpha);
		free(beta);
	} else {
		char *u, *v, *tan, *ccos1, *ccos2, *ccos3;
		char *u2, *v2, *u2pv2, *r;
		double dtan, tan_pi, tan_d, cos_1, cos_2, cos_3;
		double pi = 3.141592653589793;
		t1 = RealBigNumMul(m3, "-1");
		t4 = RealBigNumMul(m, "-1");
		t2 = RealBigNumSqrt(t1);
		free(t1);
		t1 = RealBigNumMul(n, "-1");
		t3 = RealBigNumDiv(t1, t2);
		free(t1);
		free(t2);

		dtan = atof(t3);
		free(t3);
		tan_pi = acos(dtan);
		cos_1 = cos(tan_pi/3);
		cos_2 = cos((tan_pi - 2*pi)/3);
		cos_3 = cos((tan_pi + 2*pi)/3);
		ccos1 = malloc(16);
		ccos2 = malloc(16);
		ccos3 = malloc(16);
		sprintf(ccos1, "%.10lf", cos_1);
		sprintf(ccos2, "%.10lf", cos_2);
		sprintf(ccos3, "%.10lf", cos_3);
		t2 = RealBigNumSqrt(t4);
		//sqrt3 = RealBigNumSqrt("3");
		free(t4);
		y1 = Mul3("2", t2, ccos1);
		y2 = Mul3("2", t2, ccos2);
		y3 = Mul3("2", t2, ccos3);
		x1 = RealBigNumSub(y1, bd3a);
		x2 = RealBigNumSub(y2, bd3a);
		x3 = RealBigNumSub(y3, bd3a);
		y2_i = malloc(2);
		y2_i[0] = '0';
		y2_i[1] = 0;
		y3_i = malloc(2);
		y3_i[0] = '0';
		y3_i[1] = 0;
		p[0] = x1;
		p[1] = x2;
		p[2] = y2_i;
		p[3] = x3;
		p[4] = y3_i;
		free(y1);
		free(y2);
		free(y3);

		free(t2);
		//free(v);
		//free(u);
		free(ccos1);
		free(ccos2);
		free(ccos3);
	}
#ifdef DEBUG
	printf("x1 = %s\n", x1);
	printf("x2 = %s + %si\n",  x2, y2_i);
	printf("x3 = %s + %si\n",  x3, y3_i);
#endif
	free(sqrt3);
	free(n2pm3);
	free(bd3a);
	free(m);
	free(n);
	return judge;
}


int Shengjin(char *a, char *b, char *c, char *d, char **p)
{
	char *A, *B, *C;
	char *K, *T;
	char *t1, *t2, *t3, *t4;
	char *the;
	char *x1, *x2, *x3;
	char *y1, *y2, *y2_i, *y3, *y3_i;
	char *y1_s3, *y2_s3;
	char *sqrt3 = RealBigNumSqrt("3");
	int judge = 0;

	t1 = RealBigNumPow(b, 2); // b2
	t2 = RealBigNumMul(a, c); // ac
	t3 = RealBigNumMul("3", t2); // 3ac;
	A = RealBigNumSub(t1, t3);
	free(t1);
	free(t2);
	free(t3);

	t1 = RealBigNumMul(b, c); // bc
	t2 = RealBigNumMul(a, d); // ad
	t3 = RealBigNumMul("9", t2); // 9ad;
	B = RealBigNumSub(t1, t3);
	free(t1);
	free(t2);
	free(t3);

	t1 = RealBigNumPow(c, 2); // c2
	t2 = RealBigNumMul(b, d); // bd
	t3 = RealBigNumMul("3", t2); // 3bd;
	C = RealBigNumSub(t1, t3);
	free(t1);
	free(t2);
	free(t3);

	t1 = RealBigNumPow(B, 2); // B2
	t2 = RealBigNumMul(A, C); // AC
	t3 = RealBigNumMul("4", t2); // 4AC;
	the = RealBigNumSub(t1, t3);
	free(t1);
	free(t2);
	free(t3);

	if (RealBigNumCmp(A, "0") == 0 && RealBigNumCmp(B, "0") == 0) {
		t1 = RealBigNumDiv(c, b);
		x1 = RealBigNumMul("-1", t1);
		x2 = RealBigNumMul("-1", t1);
		x3 = RealBigNumMul("-1", t1);
		y2_i = malloc(2);
		y2_i[0] = '0';
		y2_i[1] = 0;
		y3_i = malloc(2);
		y3_i[0] = '0';
		y3_i[1] = 0;
		p[0] = x1;
		p[1] = x2;
		p[2] = y2_i;
		p[3] = x3;
		p[4] = y3_i;
		free(t1);
	}

	judge = RealBigNumCmp(the, "0");
	if (judge > 0) {
		t1 = RealBigNumMul(A, b); // Ab
		t2 = RealBigNumSqrt(the);   // sqrt(the)
		t3 = RealBigNumSub(t2, B);  // sqrt(the) - B
		t4 = RealBigNumMul(a, t3);
		free(t3);
		t3 = RealBigNumMul(t4, "1.5");
		y1 = RealBigNumAdd(t1, t3);
		free(t3);
		free(t4);
		t3 = RealBigNumAdd(t2, B);  // sqrt(the) + B
		t4 = RealBigNumMul(a, t3);
		free(t3);
		t3 = RealBigNumMul(t4, "1.5");
		y2 = RealBigNumSub(t1, t3);
		free(t3);
		free(t4);
		free(t1);
		free(t2);
		
		y1_s3 = RealBigNumRoot(y1, 3);
		y2_s3 = RealBigNumRoot(y2, 3);


		free(y1);
		free(y2);

		t1 = RealBigNumAdd(y1_s3, y2_s3);
		t2 = RealBigNumSub(y1_s3, y2_s3);

		free(y1_s3);
		free(y2_s3);

		t3 = RealBigNumAdd(b, t1);
		t4 = RealBigNumMul("-1", t3);
		free(t3);
		t3 = RealBigNumDiv(t4, a);
		free(t4);
		x1 = RealBigNumDiv(t3, "3");
		free(t3);

		t3 = RealBigNumMul(b, "2");
		t4 = RealBigNumSub(t1, t3);
		free(t3);
		t3 = RealBigNumDiv(t4, a);
		free(t4);
		x2 = RealBigNumDiv(t3, "6");
		x3 = RealBigNumDiv(t3, "6");
		free(t3);
		free(t1);

		t1 = RealBigNumDiv(t2, a);
		free(t2);
		t3 = RealBigNumDiv(t1, "6");
		free(t1);
		y2_i = RealBigNumMul(t3, sqrt3);
		y3_i = RealBigNumMul(y2_i, "-1");
		free(t3);
		p[0] = x1;
		p[1] = x2;
		p[2] = y2_i;
		p[3] = x3;
		p[4] = y3_i;
	} else if (judge == 0) {
		K = RealBigNumDiv(B, A);
		t1 = RealBigNumDiv(b, a);
		x1 = RealBigNumSub(K, t1);
		free(t1);
		x2 = RealBigNumMul(K, "-0.5");
		x3 = RealBigNumMul(x2, "1");
		y2_i = malloc(2);
		y2_i[0] = '0';
		y2_i[1] = 0;
		y3_i = malloc(2);
		y3_i[0] = '0';
		y3_i[1] = 0;
		p[0] = x1;
		p[1] = x2;
		p[2] = y2_i;
		p[3] = x3;
		p[4] = y3_i;
		free(K);
	} else {
		double cosv, cos_pi, cos3v, sin3v, x_tmp1, x_tmp2, x_tmp3;
		char *xc1, *xc2, *xc3;
		char *sqrtA;
		t1 = Mul3("2", A, b);
		t2 = Mul3("3", a, B);
		t3 = RealBigNumSub(t1, t2);
		free(t1);
		free(t2);
		t1 = RealBigNumPow(A, 3);
		t2 = RealBigNumSqrt(t1);
		free(t1);
		t1 = RealBigNumDiv(t3, t2);	
		free(t3);
		free(t2);
		T = RealBigNumDiv(t1, "2");
		cosv = atof(T);
		cos_pi = acos(cosv);
		cos3v = cos(cos_pi / 3);
		sin3v = sin(cos_pi / 3);

		x_tmp1 = cos3v * 2;
		x_tmp2 = (cos3v + sqrt(3) * sin3v);
		x_tmp3 = (cos3v - sqrt(3) * sin3v);
		xc1 = malloc(16);
		xc2 = malloc(16);
		xc3 = malloc(16);
		sprintf(xc1, "%.10lf", x_tmp1);
		sprintf(xc2, "%.10lf", x_tmp2);
		sprintf(xc3, "%.10lf", x_tmp3);

		sqrtA = RealBigNumSqrt(A);
		t1 = RealBigNumMul(sqrtA, xc1); 
		t2 = RealBigNumAdd(t1, b);
		free(t1);
		t1 = RealBigNumMul(t2, "-1");
		free(t2);
		t2 = RealBigNumDiv(t1, a);
		free(t1);
		x1 = RealBigNumDiv(t2, "3");
		free(t2);

		t1 = RealBigNumMul(sqrtA, xc2); 
		t2 = RealBigNumSub(t1, b);
		free(t1);
		t1 = RealBigNumDiv(t2, a);
		free(t2);
		x2 = RealBigNumDiv(t1, "3");
		free(t1);

		t1 = RealBigNumMul(sqrtA, xc3); 
		t2 = RealBigNumSub(t1, b);
		free(t1);
		t1 = RealBigNumDiv(t2, a);
		free(t2);
		x3 = RealBigNumDiv(t1, "3");
		free(t1);

		y2_i = malloc(2);
		y2_i[0] = '0';
		y2_i[1] = 0;
		y3_i = malloc(2);
		y3_i[0] = '0';
		y3_i[1] = 0;
		p[0] = x1;
		p[1] = x2;
		p[2] = y2_i;
		p[3] = x3;
		p[4] = y3_i;


		free(T);
		free(xc3);
		free(xc2);
		free(xc1);
		free(sqrtA);
	}
#ifdef DEBUG
	printf("x1 = %s\n", x1);
	printf("x2 = %s + %si\n",  x2, y2_i);
	printf("x3 = %s + %si\n",  x3, y3_i);
#endif


	free(sqrt3);
	free(A);
	free(B);
	free(C);

	return judge;
}

int RelativeEq(char *a, char *b)
{
	char *c = RealBigNumSub(a, b);

	return RealBigNumAbsCmp(c, "0.00001") <= 0;
}

int AnswerMatch(char **c, char **s)
{
	int i, j;
	int cvisit[3] = {0, 0, 0}; 
	int svisit[3] = {0, 0, 0}; 
	int idx[3] = {0, 1, 3};

	if (!RelativeEq(c[2], s[2]) && !RelativeEq(c[2], s[4]))
		return -1;

	for (i = 0; i < 3; i++) {
		if (cvisit[i])
			continue;
		for(j = 0; j < 3; j++) {
			if (svisit[j])
				continue;
			if (RelativeEq(c[idx[i]], s[idx[j]])) {
				cvisit[i] = 1;
				svisit[j] = 1;
				break;
			}
		}
	}
	for (i = 0; i < 3; i++) {
		if (cvisit[i] == 0)
			return -1;
	}

	return 0;
}
