#include "./Math.h"

char *inttostr(int num)
{
	char *p = malloc(sizeof(char) * 100);
	int i;
	for(i = 0; num != 0; i++) {
		p[i] = '0' + (num % 10);
		num /= 10;
	}
	p[i] = 0;
	p = BigNumReverse(p);

	return p;
}

char *RealBigNumSin(char *a)
{
    /* 这里，建议a作为参数表示度数 */
	char *f, *x, *c;
	char *ret, *t;
	int i;
	int len =strlen(a);
	int pi_size = 43;
	char *const_num;
    char *div_d = "360";
	char *pi = "3.141592653589793";
	char *prec = "0.00000000001";
	int sign = 0;
	char *rem;

    sign = a[0] == '-' ? 1 : 0;

	rem = malloc(5 * sizeof(char));

	t = RealBigNumDiv_Rem(a, div_d, rem);

	free(t);

    t = RealBigNumMul(rem, pi); 
    free(rem);
    rem = RealBigNumDiv(t, "180");
    free(t);

	len = strlen(rem);
	x = malloc(len * sizeof(char));
	memcpy(x, rem, sizeof(char) * len);
	x[len] = 0;
	c = malloc(len * sizeof(char));
	memcpy(c, rem, sizeof(char) * len);
	c[len] = 0;

	f = malloc(2 * sizeof(char));
	f[0] = '1';
	f[1] = 0;

	i = 2;

	while(1) {
		const_num = inttostr(i);
		t = RealBigNumMul(f, const_num); 
		free(const_num);
		free(f);
		f = t;
		t = RealBigNumMul(x, rem);
		free(x);
		x = t;
		if (i % 2 == 1) { 
			t = RealBigNumDiv(x, f);
			if (RealBigNumAbsCmp(t, prec) < 0) {
				free(t);
				break;
			}
			if ((i / 2) % 2) {
				ret = RealBigNumSub(c, t);
			} else {
				ret = RealBigNumAdd(c, t);
			}
			free(c);
			free(t);
			c = ret;
		}
		i++;
		if (i < 0)
			break;
	}

    if (sign) {
        ret = RealBigNumSub("0", c);
        free(c);
        c = ret;
    }

	free(rem);
	free(x);
	free(f);
	return make_prec(c, 8);
}

char *RealBigNumCos(char *a)
{
    /* 这里，建议a作为参数表示度数 */
	char *f, *x, *c;
	char *ret, *t;
	int i;
	int len =strlen(a);
	char *const_num;
    char *div_d = "360";
	char *pi = "3.141592653589793";
	char *prec = "0.00000000001";
	int sign = 0;
	char *rem;

    sign = a[0] == '-' ? 1 : 0;

	rem = malloc(5 * sizeof(char));

	t = RealBigNumDiv_Rem(a, div_d, rem);

	free(t);

    t = RealBigNumMul(rem, pi); 
    free(rem);
    rem = RealBigNumDiv(t, "180");
    free(t);

	x = malloc(2 * sizeof(char));
    x[0] = '1';
	x[1] = 0;
	c = malloc(2 * sizeof(char));
    c[0] = '1';
	c[1] = 0;

	f = malloc(2 * sizeof(char));
	f[0] = '1';
	f[1] = 0;

	i = 1;

	while(1) {
		const_num = inttostr(i);
		t = RealBigNumMul(f, const_num); 
		free(const_num);
		free(f);
		f = t;
		t = RealBigNumMul(x, rem);
		free(x);
		x = t;
		if (i % 2 == 0) { 
			t = RealBigNumDiv(x, f);
			if (RealBigNumAbsCmp(t, prec) < 0) {
				free(t);
				break;
			}
			if ((i / 2) % 2) {
				ret = RealBigNumSub(c, t);
			} else {
				ret = RealBigNumAdd(c, t);
			}
			free(c);
			free(t);
			c = ret;
		}
		i++;
		if (i < 0)
			break;
	}

	free(rem);
	free(x);
	free(f);
	return make_prec(c, 8);
}

char *RealBigNumLn(char *a)
{
	char *f, *f1, *f2;
	char *ret, *t;
	char *m, *n;
	int i;
	int len =strlen(a);
	char const_num[3];
	int size = 0;
	int sign = 0;
	int mul = 1;
	char *one = "1";
	char *tmp;
	char *prec = "0.00000000001";

    if (a[0] == '-') {
        tmp = malloc(sizeof(char) * 4);
        memcpy(tmp, "inf", 3);
        tmp[3] = 0;
        return tmp;
    }

	t = RealBigNumSqrt(a);

	if (strcmp(t, "inf") == 0)
		return t;
	if (t[0] == '1' && t[1] == 0) {
		free(t);
		t = a;
		goto do_log;
	}

	mul = 2;

	for (i = 0; i < 4; i++) {
		ret = RealBigNumSqrt(t);
		if (ret[0] == '1' && ret[1] == 0) {
			free(ret);
			goto do_log;
		}
		free(t);
		t = ret;
		mul *= 2;
	}

do_log:
	m = RealBigNumSub(t, one);
	n = RealBigNumAdd(t, one);
	f = RealBigNumDiv(m, n);
	free(m);
	free(n);


	
	len = strlen(f);
	ret = malloc(len + 2);
	memcpy(ret, f, len + 1);
	ret[len] = 0;
	f1 = malloc(len + 2);
	memcpy(f1, f, len + 1);
	f1[len] = 0;
	i = 2;
	while(1) {
		f2 = RealBigNumMul(f1, f);
		free(f1);
		if (i % 2) {
			tmp = inttostr(i);
			f1 = RealBigNumDiv(f2, tmp);
			free(tmp);
			if (RealBigNumAbsCmp(f1, prec) < 0) {
				free(f1);
				break;
			}
			tmp = RealBigNumAdd(f1, ret); 
			free(ret);
			free(f1);
			ret = tmp;
		}
		f1 = f2;
		i++;
	}

	free(f2);
	free(f);

	tmp = inttostr(2 * mul);
	f = RealBigNumMul(ret, tmp);
	free(ret);
	free(tmp);

	return make_prec(f, 7);
}
