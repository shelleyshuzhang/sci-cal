#include <stdlib.h>
#include <string.h>
#include "BigNumOps.h"


char *HextoDec(char *a)
{
	return NULL;
}

char *OcttoDev(char *a)
{
	return NULL;
}


char *BintoDec(char *a)
{
	return NULL;
}

char *BigNumReverse(char *a)
{
	int i, j;
	int len = strlen(a);
	char swap;
	i = 0, j = len - 1;
	while(i <= j) {
		swap = a[i];
		a[i] = a[j];
		a[j] = swap;
		i++;
		j--;
	}
	a[len] = 0;
	return a;
}


char *UnsignedBigNumAdd(char *a, char *b)
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	int len_max = len_a >= len_b ? len_a : len_b;
	char *c = malloc((len_max + 2) * sizeof(char));
	int i, j, k = 0;
	int inta, intb, intc, addc = 0;

	i = len_a - 1;
    j = len_b - 1;	
	k = 0;
	do {
		inta = a[i] - '0';
		intb = b[j] - '0';
		intc = (inta + intb + addc);
		addc = intc >= 10 ? 1 : 0;
		intc = intc >= 10 ? intc - 10 : intc;
		c[k] = intc + '0';
		i--;
		j--;
		k++;
	} while(i >= 0 && j >= 0);


	while (i >= 0) {
		inta = a[i] - '0';
		intc = inta + addc;
		addc = intc >= 10 ? 1 : 0;
		intc = intc >= 10 ? intc - 10 : intc;
		c[k] = intc + '0';
		i--;
		k++;
	}
	while (j >= 0) {
		intb = b[j] - '0';
		intc = intb + addc;
		addc = intc >= 10 ? 1 : 0;
		intc = intc >= 10 ? intc - 10 : intc;
		c[k] = intc + '0';
		j--;
		k++;
	}
	if (addc) {
		c[k] = addc + '0';
		k++;
	}

	c[k] = 0;

	return BigNumReverse(c);
}

int UnsignedBigNumCmp(char *a, char *b)
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	int i;

	if (len_a < len_b)
		return -1;

	if (len_a > len_b)
		return 1;

	for (i = 0; i < len_a; i++) {
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}
	return 0;
}

char *UnsignedBigNumSub(char *a, char *b)
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	int len_max = len_a >= len_b ? len_a : len_b;
	char *c = malloc((len_max + 2) * sizeof(char));
	char *suba, *subb;
	int i, j, k = 0;
	int inta, intb, intc, subc = 0;

	int judge = UnsignedBigNumCmp(a, b);
	if (judge > 0) {
		suba = a;
		subb = b;
		i = len_a - 1;
		j = len_b - 1;
	} else if (judge < 0) {
		suba = b;
		subb = a;
		i = len_b - 1;
		j = len_a - 1;
	} else {
		c[0] = '0';
		c[1] = 0;
		return c;
	}

	while(i >= 0 &&  j >= 0) {
		inta = suba[i] - '0';
		intb = subb[j] - '0';
		intc = (inta - intb - subc);
		subc = intc < 0 ? 1 : 0;
		intc = intc < 0 ? intc + 10 : intc;
		c[k] = intc + '0';
		i--, j--, k++;
	}

	while(i >= 0) {
		inta = suba[i] - '0';
		intc = inta - subc;
		subc = intc < 0 ? 1 : 0;
		intc = intc < 0 ? intc + 10 : intc;
		c[k] = intc + '0';
		i--, k++;
	}

	for (;k >=2; k--) {
		if (c[k-1] != '0') {
			break;
		}
	}

	if (judge < 0) {
		c[k] = '-';
		k++;
	}

	c[k] = 0;

	return BigNumReverse(c);
}

char *UnsignedBigNumMul(char *a, char *b)
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	char *c = malloc((len_a + len_b + 2) * sizeof(char));
	int i, j, k = 0;
	int inta, intb, intc, mulc = 0;
	int max_c = 0;

	for (i = 0; i < len_a + len_b + 2; i++) {
		c[i] = '0';
	}

	for (i = len_a - 1; i >= 0; i--) {
		inta = a[i] - '0';
		for (j = len_b - 1; j >= 0; j--) {
			intb = b[j] - '0';
			intc = c[k] - '0';
			intc = inta * intb + intc;
			c[k] = (intc % 10) + '0';
			c[k+1] += (intc / 10);
			k++;
		}
		k = k - (len_b - 1);
	}

	if (c[len_a + len_b - 1] != '0') {
		c[len_a + len_b] = 0;
	}
	if (c[len_a + len_b - 1] == '0') {
		c[len_a + len_b - 1] = 0;
	}

	return BigNumReverse(c);
}

char *UnsignedBigNumDiv(char *a, char *b)
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	int len_max = len_a >= len_b ? len_a : len_b;
	char *bak_a = malloc((len_a + 1) * sizeof(char));
	char *bak_b = malloc((len_b + 1) * sizeof(char));
	char *c = malloc((len_max + 3) * sizeof(char));
	char **p = NULL;
	char **n = NULL;
	int size = 0;
	int counter = 0;
	char *t;
	char *po;
	int count;
	int i;

	c[0] = '0';
	c[1] = 0;

	if (b[0] == '0' && b[1] == 0) {
		c[0] = 'i';
		c[1] = 'n';
		c[2] = 'f';
		c[3] = 0;
		return c;
	}

	if (UnsignedBigNumCmp(a, b) < 0) {
		c[0] = '0';
		c[1] = 0;
		free(bak_a);
		free(bak_b);
		return c;
	}

	if (UnsignedBigNumCmp(a, b) == 0) {
		c[0] = '1';
		c[1] = 0;
		free(bak_a);
		free(bak_b);
		return c;
	}

	memcpy(bak_a, a, sizeof(char) * len_a);
	bak_a[len_a] = 0;
	memcpy(bak_b, b, sizeof(char) * len_b);
	bak_b[len_b] = 0;
	if (size ==  0) {
		size += 32;
		char *tmp = malloc(sizeof(char *) * size);
		memset(tmp, 0, sizeof(char *) * size);
		n = (char **)tmp;
		tmp = malloc(sizeof(char *) * size);
		memset(tmp, 0, sizeof(char *) * size);
		po = malloc((len_b + 1) * sizeof(char));
		p = (char **)tmp;
		memcpy(po, b, sizeof(char) * len_b);
		po[len_b] = 0;
		n[0] = po;
		po = malloc(2 * sizeof(char));
		p[0] = po;
		p[0][0] = '1';
		p[0][1] = 0;
	}

	count = 0;
	while(UnsignedBigNumCmp(bak_a, bak_b) >= 0) {
		while(UnsignedBigNumCmp(bak_a, n[count]) >= 0) {
			if (n[count + 1] == NULL)
				n[count + 1] = UnsignedBigNumAdd(n[count], n[count]);
			if (p[count + 1] == NULL)
				p[count + 1] = UnsignedBigNumAdd(p[count], p[count]);
			count++;
			if (count >= (size - 1)) {
				size += 32;
				char *tmp = malloc(sizeof(char *) * size);
				memset(tmp, 0, sizeof(char *) * size);
				if (n) {
					memcpy(tmp, n, sizeof(char *) * (size - 32));
					free(n);
				}
				n = (char **)tmp;
				tmp = malloc(sizeof(char *) * size);
				memset(tmp, 0, sizeof(char *) * size);
				if (p) {
					memcpy(tmp, p, sizeof(char *) * (size - 32));
					free(p);
				}
				p = (char **)tmp;
			}
		}
		t = UnsignedBigNumSub(bak_a, n[count - 1]);
		free(bak_a);
		bak_a = t;
		t = UnsignedBigNumAdd(c, p[count - 1]);
		free(c);		
		c = t;
		count = 0;
	}

	for (i = 0; i < size; i++) {
		if (p[i]) {
			free(p[i]);
		}
		if (n[i])
			free(n[i]);
	}

	free(p);
	free(n);
	free(bak_a);
	free(bak_b);

	return c;
}

char *UnsignedBigNumDiv_Rem(char *a, char *b, char *rem)
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	int len_max = len_a >= len_b ? len_a : len_b;
	char *bak_a = malloc((len_a + 1) * sizeof(char));
	char *bak_b = malloc((len_b + 1) * sizeof(char));
	char *c = malloc((len_max + 3) * sizeof(char));
	char **p = NULL;
	char **n = NULL;
	int size = 0;
	int counter = 0;
	char *t;
	char *po;
	int count;
	int i;

	c[0] = '0';
	c[1] = 0;

	if (b[0] == '0' && b[1] == 0) {
		c[0] = 'i';
		c[1] = 'n';
		c[2] = 'f';
		c[3] = 0;
		rem[0] = 0;
		return c;
	}

	if (UnsignedBigNumCmp(a, b) < 0) {
		c[0] = '0';
		c[1] = 0;
		memcpy(rem, a, len_a);
		rem[len_a] = 0;
		free(bak_a);
		free(bak_b);
		return c;
	}

	if (UnsignedBigNumCmp(a, b) == 0) {
		c[0] = '1';
		c[1] = 0;
		rem[0] = '0';
		rem[1] = 0;
		free(bak_a);
		free(bak_b);
		return c;
	}

	memcpy(bak_a, a, sizeof(char) * len_a);
	bak_a[len_a] = 0;
	memcpy(bak_b, b, sizeof(char) * len_b);
	bak_b[len_b] = 0;
	if (size ==  0) {
		size += 32;
		char *tmp = malloc(sizeof(char *) * size);
		memset(tmp, 0, sizeof(char *) * size);
		n = (char **)tmp;
		tmp = malloc(sizeof(char *) * size);
		memset(tmp, 0, sizeof(char *) * size);
		po = malloc((len_b + 1) * sizeof(char));
		p = (char **)tmp;
		memcpy(po, b, sizeof(char) * len_b);
		po[len_b] = 0;
		n[0] = po;
		po = malloc(2 * sizeof(char));
		p[0] = po;
		p[0][0] = '1';
		p[0][1] = 0;
	}

	count = 0;
	while(UnsignedBigNumCmp(bak_a, bak_b) >= 0) {
		while(UnsignedBigNumCmp(bak_a, n[count]) >= 0) {
			if (n[count + 1] == NULL)
				n[count + 1] = UnsignedBigNumAdd(n[count], n[count]);
			if (p[count + 1] == NULL)
				p[count + 1] = UnsignedBigNumAdd(p[count], p[count]);
			count++;
			if (count >= (size - 1)) {
				size += 32;
				char *tmp = malloc(sizeof(char *) * size);
				memset(tmp, 0, sizeof(char *) * size);
				if (n) {
					memcpy(tmp, n, sizeof(char *) * (size - 32));
					free(n);
				}
				n = (char **)tmp;
				tmp = malloc(sizeof(char *) * size);
				memset(tmp, 0, sizeof(char *) * size);
				if (p) {
					memcpy(tmp, p, sizeof(char *) * (size - 32));
					free(p);
				}
				p = (char **)tmp;
			}
		}
		t = UnsignedBigNumSub(bak_a, n[count - 1]);
		free(bak_a);
		bak_a = t;
		t = UnsignedBigNumAdd(c, p[count - 1]);
		free(c);		
		c = t;
		count = 0;
	}

	memcpy(rem, bak_a, sizeof(char) * strlen(bak_a));
	rem[strlen(bak_a)] = 0;

	for (i = 0; i < size; i++) {
		if (p[i]) {
			free(p[i]);
		}
		if (n[i])
			free(n[i]);
	}

	free(p);
	free(n);
	free(bak_a);
	free(bak_b);

	return c;
}

char *UnsignedBigNumPow(char *a, int num)
{
	int len_a = strlen(a);
	char *bak_a = malloc((len_a + 2) * sizeof(char));
	char *c;
	char **n = NULL;
	int p = 1;
	int size = 0;
	int counter = 0;
	char *t;
	char *po;
	int count;
	int i;

	c = malloc(sizeof(char) * 2);
	c[0] = '1';
	c[1] = 0;
	if (num == 0) {
		return c;
	}

	
	if (size ==  0) {
		size += 32;
		char *tmp = malloc(sizeof(char *) * size);
		memset(tmp, 0, sizeof(char *) * size);
		n = (char **)tmp;
		po = malloc((len_a + 1) * sizeof(char));
		memcpy(po, a, sizeof(char) * len_a);
		po[len_a] = 0;
		n[0] = po;
	}

	count = 0;
	while(num > 0) {
		while(num >= (p << 1)) {
			if (n[count + 1] == NULL)
				n[count + 1] = UnsignedBigNumMul(n[count], n[count]);
			p <<= 1;
			count++;
			if (count >= (size - 1)) {
				size += 32;
				char *tmp = malloc(sizeof(char *) * size);
				memset(tmp, 0, sizeof(char *) * size);
				if (n) {
					memcpy(tmp, n, sizeof(char *) * (size - 32));
					free(n);
				}
				n = (char **)tmp;
			}
		}
		num -= p;
		t = UnsignedBigNumMul(c, n[count]);
		free(c);
		c = t;
		count = 0;
		p = 1;
	}

	for (i = 0; i < size; i++) {
		if (n[i])
			free(n[i]);
	}

	free(n);

	return c;
}

char *UnsignedBigNumRoot(char *a, int num)
{
	char *low, *high, *mid, *mid1, *tmp, *tmp1;
	char div[2] = { '2', 0 };
	char one[2] = { '1', 0 };
	int judge, judge1;
	int len = strlen(a);
	
	low = malloc(sizeof(char) * 2);
	low[0] = '1';
	low[1] = 0;

	high = malloc((len + 1) * sizeof(char)); 
	memcpy(high, a, sizeof(char) * (len + 1));
	high[len] = 0;

	while(UnsignedBigNumCmp(low, high) <= 0) {
		mid = UnsignedBigNumAdd(low, high);
		tmp = UnsignedBigNumDiv(mid, div);
		free(mid);
		mid = tmp;
		tmp = UnsignedBigNumPow(mid, num);
		mid1 = UnsignedBigNumAdd(mid, one);
		tmp1 = UnsignedBigNumPow(mid1, num);
		judge = UnsignedBigNumCmp(tmp, a);
		judge1 = UnsignedBigNumCmp(tmp1, a);
		if (judge < 0 && judge1 > 0) {
			free(high);
			free(low);
			free(tmp);
			free(tmp1);
			free(mid1);
			return mid;
		} else if (judge == 0) {
			free(high);
			free(low);
			free(tmp);
			free(tmp1);
			free(mid1);
			return mid;
		} else if (judge1 == 0) {
			free(high);
			free(low);
			free(tmp);
			free(tmp1);
			free(mid);
			return mid1;
		} else if (judge > 0) {
			free(high);
			free(tmp);
			free(tmp1);
			free(mid1);
			high = mid;
		} else if (judge1 < 0) {
			free(low);
			free(tmp);
			free(tmp1);
			free(mid);
			low = mid1;
		}
	}

	return high;
}

char *UnsignedBigNumSqrt(char *a)
{
	return UnsignedBigNumRoot(a, 2);
}
