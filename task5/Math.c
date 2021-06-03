#include "./Math.h"
#include <math.h>

#define TRIG_PRECISE "0.00000000000000000000000000000001"
#define PI "3.14159265358979323846264338327950288"
#define TRIG_ACCURACY_SIZE 20
#define ARC_TRIG_ACCU "0.0001"

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

char* convert_radian(char* radian) {
    char* angle;
    char* angle180 = RealBigNumMul(radian, "180");
    angle = RealBigNumDiv(angle180, PI);
    return angle;
}

char* convert_degree(char* degree) {
    char* radian;
    char* d_pi = RealBigNumMul(degree, PI);
    d_pi = make_prec(d_pi, 10);
    radian = RealBigNumDiv(d_pi, "180");
    return radian;
}

char *F2S(double d, char *str)
{
    char str1[100];
    int j = 0, k, i;
    i = (int)d;
    while(i > 0)
    {
        str1[j++] = i % 10 + '0';
        i = i / 10;
    }

    for(k = 0;k < j;k++)
    {
        str[k] = str1[j-1-k];
    }

    str[j++] = '.';

    d = d - (int)d;
    for(i = 0;i < 10;i++)
    {
        d = d*10;
        str[j++] = (int)d + '0';
        d = d - (int)d;
    }
    while(str[--j] == '0');
    str[++j] = '\0';
    return str;
}

// taylor_formula -> sin(x degree)
double sin_double(double x) {
    double ex = 0.000001;
    double temp, sin = 0.0, i = 0.0;
    temp = x;
    while(fabs(temp) > ex) {
        sin += temp;
        i += 2;
        temp = (-1) * temp * x * x / ((i + 1) * (i));
    }
    return sin;
}

char *RealBigNumSin(char *a)
{
    /* 这里，建议a作为参数表示度数 */
    char *f, *x, *c;
    char *ret, *t;
    int i;
    int len = strlen(a);
    int pi_size = 43;
    char *const_num;
    char *div_d = "360";
    char *pi = PI;
    char *prec = TRIG_PRECISE;
    int sign = 0;
    char *rem;

    sign = a[0] == '-' ? 1 : 0;

    rem = malloc(TRIG_ACCURACY_SIZE * sizeof(char));

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
    char *pi = PI;
    char *prec = TRIG_PRECISE;
    int sign = 0;
    char *rem;

    sign = a[0] == '-' ? 1 : 0;

    rem = malloc(TRIG_ACCURACY_SIZE * sizeof(char));

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
    char *prec = TRIG_PRECISE;

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

    return make_prec(f, 8);
}

double d_asin(double in) {
    double result = in,
            result_a = 1.0f,
            result_b = 1.0f,
            result_c = 1.0f;

    unsigned int i = 0, ii;
    double mid = result_b * result_c;

    while (fabs(mid) > 0.000001)
    {
        for(ii = 0; ii < (2 * i + 1); ii++)
        {
            result_a *= (2.0 * ii + 1.0) / (2.0 * ii + 2.0);
            result_b *= (in * in);
        }
        result_b *= in;
        result_c = result_a / (ii + 2.0);
        mid = result_c * result_b;
        result += mid;
        result_a = 1.0f; result_b = 1.0f;
        i++;
    }
    return result;
}

double d_acos(double in) {
    unsigned char i;
    double ans = in, t1 = 1, t2 = in;
    in *= in;
    double temp = 1.0;
    i = 3;
    while (temp > 0.000001) {
        t1 *= (double) (i-2) / (double) (i-1);
        t2 *= in;
        temp = (t1 * t2 / (double) i);
        ans += temp;
        i += 2;
    }
    ans = 1.570796 - ans;
    return ans;
}

double d_atan(double in) {
    unsigned char i;
    double ans = in, t1 = in, t2 = -1;
    in *= in;
    double temp = 1.0;
    i = 3;
    while (temp > 0.000001) {
        t1 *= in;
        temp = (t1 * t2 / (double) i);
        t2 *= (-1);
        ans += temp;
        i += 2;
    }
    return ans;
}

char* RealBigArcTan(char* in) {
    char* ans = RealBigNumAdd("0", in);
    char* t1 = RealBigNumAdd("0", in);
    char* t2 = RealBigNumSub("0", "1");
    in = RealBigNumMul(in, in);
    char* in_short = make_prec(in, 10);
    char* temp = RealBigNumAdd("0", "0");
    char* temp_before = RealBigNumAdd("0", "-100");
    char* temp_diff = RealBigNumAdd(temp, temp_before);
    char* i = RealBigNumAdd("0", "3");
    while (RealBigNumAbsCmp(temp_diff, "0.000001") < 0) {
        t1 = RealBigNumMul(t1, in_short);
        t1 = make_prec(t1, 10);
        char* t1t2 = RealBigNumMul(t1, t2);
        temp_before = RealBigNumAdd(temp, "0");
        temp = RealBigNumDiv(t1t2, i);
        t2 = RealBigNumMul(t2, "-1");
        ans = RealBigNumAdd(ans, temp);
        i = RealBigNumAdd(i, "2");
        temp_diff = RealBigNumAdd(temp, temp_before);
        free(t1t2);
    }
    free(t1);
    free(t2);
    free(in_short);
    free(temp);
    free(i);
    free(temp_before);
    free(temp_diff);
    return ans;
}

char* RealBigArcSin(char* in) {
    char* a = RealBigNumAdd("1", "0");
    char* b = RealBigNumAdd("1", "0");
    char* c = RealBigNumAdd("1", "0");
    char* temp = RealBigNumAdd(in, "0");
    char* cb = RealBigNumMul(c, b);

    char* i = RealBigNumAdd("0", "0");
    char* j;

    while (RealBigNumAbsCmp(cb, ARC_TRIG_ACCU) < 0) {
        char* i2 = RealBigNumMul(i, "2");
        char* i2_1 = RealBigNumAdd(i2, "1");
        j = RealBigNumAdd("0", "0");
        while (RealBigNumCmp(j, i2_1) < 0) {
            char* j2 = RealBigNumMul(j, "2");
            j2 = make_prec(j2, 10);
            char* j2_1 = RealBigNumAdd(j2, "1");
            char* j2_2 = RealBigNumAdd(j2, "2");
            char* s = RealBigNumDiv(j2_1, j2_2);
            a = RealBigNumMul(a, s);
            char* temp_in = RealBigNumMul(in, in);
            temp_in = make_prec(temp_in, 10);
            b = RealBigNumMul(b, temp_in);
            b = make_prec(b, 10);
            j = RealBigNumAdd(j, "1");
            free(s);
            free(temp_in);
            free(j2);
            free(j2_1);
            free(j2_2);
        }
        b = RealBigNumMul(b, in);
        b = make_prec(b, 10);
        char* j_2 = RealBigNumAdd(j, "2");
        c = RealBigNumDiv(a, j_2);
        cb = RealBigNumMul(c, b);
        cb = make_prec(cb, 10);
        temp = RealBigNumAdd(cb, temp);
        free(a);
        free(b);
        free(j_2);
        free(i2);
        free(i2_1);
        a = RealBigNumAdd("1", "0");
        b = RealBigNumAdd("1", "0");
        i++;
    }
    free(a);
    free(b);
    free(c);
    free(cb);
    return temp;
}

char* RealBigArcCos(char* in) {
    char* res = RealBigNumAdd(in, "0");
    char* a = RealBigNumAdd("0", "1");
    char* b = RealBigNumAdd(in, "0");
    in = RealBigNumMul(in, in);
    char* in_short = make_prec(in, 10);
    char* i = RealBigNumAdd("0", "3");
    char* temp = RealBigNumAdd("0", "1");
    while (RealBigNumAbsCmp(temp, ARC_TRIG_ACCU) > 0) {
        char* i_1 = RealBigNumSub(i, "1");
        char* i_2 = RealBigNumSub(i, "2");
        char* div = RealBigNumDiv(i_2, i_1);
        a = RealBigNumMul(a, div);
        b = RealBigNumMul(b, in_short);
        char* ab = RealBigNumMul(a, b);
        ab = make_prec(ab, 10);
        temp = RealBigNumDiv(ab, i);
        res = RealBigNumAdd(temp, res);
        free(i_1);
        free(i_2);
        free(div);
        free(ab);
    }
    char* pi_2 = RealBigNumDiv(PI, "2");
    char* ans = RealBigNumSub(pi_2, res);
    ans = make_prec(ans, 10);
    free(res);
    free(a);
    free(b);
    free(in_short);
    free(i);
    free(temp);
    free(pi_2);
    return ans;
}

char *RealBigNumTan(char *a) {
    char* a_sin = RealBigNumSin(a);
    char* a_cos = RealBigNumCos(a);
    char* a_tan = RealBigNumDiv(a_sin, a_cos);
    char* a_tan_s = make_prec(a_tan, 10);
    free(a_tan);
    return a_tan_s;
}
