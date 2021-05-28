#include <stdlib.h>
#include <string.h>
#include "RealNumOps.h"
#include "BigNumOps.h"

#define ACCURITY 10

int point_locate(char *a)
{
	int len = strlen(a);
	int i;
	for (i = len -1; i >=0; i--) {
		if (a[i] == '.') {
			return len - 1 - i;
		}
	}
	return 0;
}

char *fill_zero(char *a, int osize ,int nsize)
{
	char *n = malloc((nsize + 1));
	int i, j = 0;
	for (i = 0; i < osize; i++) {
		if ((a[i] != '-') && a[i] != '+' && a[i] != '.' && a[i] != '0') {
			break;
		}
	}
	if (i == osize) {
		n[j] = '0';
		j++;
		goto done;
	}
	for (; i < osize; i++) {
		if ((a[i] != '-') && a[i] != '+' && a[i] != '.') {
			n[j] = a[i];
			j++;
		}
	}
	for (i = 0; i < nsize - osize; i++) {
		n[j] = '0';
		j++;
	}
done:
	n[j] = 0;
	return n;
}

char *remove_zero(char *a)
{
	int i = 0, j;
	int zero = 0;
	int len = strlen(a);

	if (a[0] == '-' || a[0] == '+')
		i++;
	for (; i < len; i++) {
		if (a[i] != '0') {
			break;
		}
		zero++;
	}
	if (i == len) {
		i--;
		zero--;
	}
	if (a[i] == '.') {
		i--;
		zero--;
	}
	for (j = i - zero; j + zero < len; j++) {
		a[j] = a[j + zero];
	}
	a[j] = 0;
	return a;
}

char *format_real(char *a, int sign, int point)
{
	int i, j = 0;
	int len = strlen(a);
	int size = len >= point ? len : point;
	char *c;
	if (sign)
		size += 1;
	if (point)
		size += 1;

	c = malloc((size + 3) * sizeof(char));

	if (sign) {
		c[0] = '-';
		j++;
	}

	if (point >= len) {
		c[j] = '0';
		j++;
		c[j] = '.';
		j++;
		for (i = 0; i < point - len; i++) {
			c[j] = '0';
			j++;
		}
		for (i = 0; i < len; i++) {
			c[j] = a[i];
			j++;
		}
	} else {
		for (i = 0; i < len; i++) {
			if ((point !=0) && ((i + point) == (len))) {
				c[j] = '.';
				j++;
			}
			c[j] = a[i];
			j++;
		}
	}
	c[j] = 0;
	if (point != 0) {
		for (i = j - 1; i >= 1; i--) {
			if (c[i] == '0')
				c[i] = 0;
			else
				break;
		}
		if (c[i] == '.')
			c[i] = 0;
	}

	free(a);
	return remove_zero(c);
}

char *make_prec(char *a, int prec)
{
	int i, j;
	int len = strlen(a);

	for (i = 0 ; i < len; i++) {
		if (a[i] == '.') {
			if ((i + prec + 1) < len)
				a[i + prec + 1] = 0;
		}
	}
	return a;
}

int RealBigNumCmp(char *a, char *b)
{
	int i;
	char *point_a, *point_b;
	char *c;
	int lena = strlen(a);
	int lenb = strlen(b);
	int judge;
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	if (asign ^ bsign) {
		if (bsign)
			return 1;
		if (asign)
			return -1;
	}

	point_a = fill_zero(a, lena, lena + mpoint - apoint);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	judge = (asign > 0 ? -1 : 1) * UnsignedBigNumCmp(point_a, point_b);

	free(point_a);
	free(point_b);
	return judge;
}

int RealBigNumAbsCmp(char *a, char *b)
{
	int i;
	char *point_a, *point_b;
	char *c;
	int lena = strlen(a);
	int lenb = strlen(b);
	int judge;
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	judge = UnsignedBigNumCmp(point_a, point_b);

	free(point_a);
	free(point_b);
	return judge;
}

char *RealBigNumAdd(char *a, char *b)
{
	int i;
	char *point_a, *point_b;
	char *c;
	int lena = strlen(a);
	int lenb = strlen(b);
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	if (asign ^ bsign) {
		if (bsign)
			c = UnsignedBigNumSub(point_a, point_b);
		if (asign)
			c = UnsignedBigNumSub(point_b, point_a);
		if (c[0] == '-') {
			asign = 1;
			c[0] = '0';
		} else
			asign = 0;
	} else {
		c = UnsignedBigNumAdd(point_a, point_b);	
	}

	free(point_a);
	free(point_b);

	return format_real(c, asign, mpoint);
}

char *RealBigNumSub(char *a, char *b)
{
	int i;
	char *point_a, *point_b;
	char *c;
	int lena = strlen(a);
	int lenb = strlen(b);
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	if (asign ^ bsign) {
		c = UnsignedBigNumAdd(point_a, point_b);
	} else {
		c = UnsignedBigNumSub(point_a, point_b);	
		if (c[0] == '-') {
			asign ^= 1;
			c[0] = '0';
		}
	}

	free(point_a);
	free(point_b);

	return format_real(c, asign, mpoint);
	return NULL;
}

char *RealBigNumMul(char *a, char *b)
{
	int i;
	char *point_a, *point_b;
	char *c;
	int lena = strlen(a);
	int lenb = strlen(b);
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	if (asign ^ bsign) {
		asign = 1;
	} else {
		asign = 0;
	}
	c = UnsignedBigNumMul(point_a, point_b);

	free(point_a);
	free(point_b);

	return format_real(c, asign, mpoint + mpoint);
}

char *RealBigNumDiv(char *a, char *b)
{
	int i;
	char *point_a, *point_b;
	char *c;
	int lena = strlen(a);
	int lenb = strlen(b);
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

#if 0
	int aint = lena - apoint;
	int bint = lenb - bpoint;
	int mint = aint > bint ? aint : bint;
#endif

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint + ACCURITY);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	if (asign ^ bsign) {
		asign = 1;
	} else {
		asign = 0;
	}

	c = UnsignedBigNumDiv(point_a, point_b);

	free(point_a);
	free(point_b);

	if (strcmp(c, "inf") == 0)
		return c;

	return format_real(c, asign, ACCURITY);
}

char *RealBigNumDiv_Rem(char *a, char *b, char *rem)
{
	int i;
	char *point_a, *point_b;
	char *c, *t;
	int lena = strlen(a);
	int lenb = strlen(b);
	
	int apoint = point_locate(a);
	int bpoint = point_locate(b);
	int mpoint = apoint > bpoint ? apoint : bpoint;

#if 0
	int aint = lena - apoint;
	int bint = lenb - bpoint;
	int mint = aint > bint ? aint : bint;
#endif

	int asign = a[0] == '-' ? 1 : 0;
	int bsign = b[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint);
	point_b = fill_zero(b, lenb, lenb + mpoint - bpoint);

	if (asign ^ bsign) {
		asign = 1;
	} else {
		asign = 0;
	}

	t = malloc(sizeof(char) * (lenb + 3));
	c = UnsignedBigNumDiv_Rem(point_a, point_b, t);

	if (rem) {
		t = format_real(t, 0, mpoint);
		memcpy(rem, t, strlen(t));
		rem[strlen(t)] = 0;
	}
	free(t);

	free(point_a);
	free(point_b);

	if (strcmp(c, "inf") == 0)
		return c;

	return format_real(c, asign, 0);
}

char *RealBigNumPow(char *a, int num)
{
	int i;
	char *point_a;
	char *c;
	int lena = strlen(a);
	
	int apoint = point_locate(a);
	int mpoint = apoint;

	int asign = a[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint);

	c = UnsignedBigNumPow(point_a, num);

	if ((num % 2) == 0)
		asign = 0;

	free(point_a);

	return format_real(c, asign, mpoint * num);
}

char *RealBigNumSqrt(char *a)
{
	int i;
	char *point_a;
	char *c;
	int lena = strlen(a);
	
	int apoint = point_locate(a);
	int mpoint = (apoint % 2) + apoint;

	int asign = a[0] == '-' ? 1 : 0;

	if (asign < -1) {
        c = malloc(sizeof(char) * 4);
        memcpy(c, "inf", 3);
        c[3] = 0;
		return c;
    }

	point_a = fill_zero(a, lena, lena + mpoint - apoint + ACCURITY * 2 );

	c = UnsignedBigNumSqrt(point_a);

	free(point_a);

	return format_real(c, asign, (mpoint / 2) + ACCURITY);
}

char *RealBigNumRoot(char *a, int num)
{
	int i;
	char *point_a;
	char *c;
	int lena = strlen(a);
	
	int apoint = point_locate(a);
	int mpoint = (num - (apoint % num)) + apoint;

	int asign = a[0] == '-' ? 1 : 0;

	point_a = fill_zero(a, lena, lena + mpoint - apoint + ACCURITY * num );

	c = UnsignedBigNumRoot(point_a, num);

	free(point_a);

	return format_real(c, asign, (mpoint / num) + ACCURITY);
}

