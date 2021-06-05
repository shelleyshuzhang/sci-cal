//
// Created by 张舒 on 6/4/21.
//

#include "./header.h"

#define MAX_STR_INPUT_SIZE 100
#define FINAL_ACCURACY 4

char *get_user_input_string() {
    char *file_path;
    file_path = (char *) malloc(MAX_STR_INPUT_SIZE * sizeof(char));
    memset(file_path, '\0', MAX_STR_INPUT_SIZE);
    char ch;
    int index = 0;
    unsigned long len = MAX_STR_INPUT_SIZE;
    while ((ch = getchar()) != '\n') {
        if (index > len - 3) {
            len *= 2;
            file_path = realloc(file_path, len * sizeof(char));
        }
        file_path[index] = ch;
        index++;
    }
    file_path[index] = '\0';
    return file_path;
}

void flush_linux() {
    char c = '\0';
    while (c != '\n') {
        c = getchar();
    }
}

int normal_calculation() {
    while (1) {
        int c;
        printf("\n%s\n", PAGE_SEP);
        printf("欢迎来到基本表达式计算界面\n");
        printf("\n#选择文件输入模式请输入 1\n"
               "#选择手动输入模式请输入 2\n");
        printf("请选择:");
        scanf("%d", &c);
        flush_linux();
        switch (c) {
            case 1:
                printf("\n%s\n", PAGE_SEP);
                printf("请输入需计算文件的路径\n");
                char *file_path = get_user_input_string();

                char *input_path;
                char *output_path;
                if (file_path[0] == '\0') {
                    char *buffer;
                    if ((buffer = getcwd(NULL, 0)) == NULL) {
                        printf("\n%s\n", PAGE_SEP);
                        printf("无法读取当前路径\n");
                        break;
                    } else {
                        strcat(buffer, "/default_exp.txt");
                    }
                    input_path = buffer;
                    free(file_path);

                } else {
                    input_path = file_path;
                }

                printf("\n请输入需计算结果应保存的路径\n");
                char *file_out_path = get_user_input_string();

                if (file_out_path[0] == '\0') {

                    char *output_buffer;
                    output_buffer = getcwd(NULL, 0);
                    strcat(output_buffer, "/default_exp_output.txt");
                    output_path = output_buffer;
                    free(file_out_path);

                } else {
                    output_path = file_out_path;
                }


                int exist = access(input_path, F_OK);
                int output_exist = access(output_path, F_OK);

                if (exist == 0) {
                    FILE *to_process = fopen(input_path, "r");
                    if (to_process == NULL) {
                        printf("\n%s\n", PAGE_SEP);
                        printf("无法打开输入文件，退出当前进程\n");
                        break;
                    } else {

                        FILE *output;
                        if (output_exist == 0) {
                            output = fopen(output_path, "a");
                        } else {
                            output = fopen(output_path, "w");
                        }

                        if (output == NULL) {
                            printf("\n%s\n", PAGE_SEP);
                            printf("无法打开输出文件，退出当前进程\n");
                            break;
                        } else {
                            while (!feof(to_process)) {
                                char *current_exp;
                                current_exp = read_exp(to_process);
                                if (current_exp[0] == '\0') {
                                    break;
                                }
                                printf("\n%s\n", PAGE_SEP);
                                printf("\n表达式: %s\n", current_exp);

                                char *cleaned_input;
                                cleaned_input = clean_exp(current_exp);

                                char *res = infix_to_suffix(cleaned_input,
                                                            (int) strlen(cleaned_input));
                                char *result;
                                result = cal_suffix(res, (int) strlen(res));
                                result = make_prec(result, FINAL_ACCURACY);

                                int result_case = -1;
                                printf("\n请输入想要保存的结果进制：\n"
                                       "二进制请输入 1\n"
                                       "八进制请输入 2\n"
                                       "十进制请输入 3\n"
                                       "十六进制请输入 4\n");
                                printf("请输入：");
                                scanf("%d", &result_case);
                                flush_linux();
                                char *c_encoded;

                                if (result_case == 1 ||
                                    result_case == 2 ||
                                    result_case == 4) {
                                    if (RealBigNumCmp(result, "0") < 0) {
                                        result = RealBigNumSub("0", result);
                                    }
                                    result = make_prec(result, -1);
                                }

                                switch (result_case) {
                                    case 1:
                                        c_encoded = dec_to_binary(result);
                                        break;
                                    case 2:
                                        c_encoded = dec_to_oct(result);
                                        break;
                                    case 3:
                                        c_encoded = result;
                                        break;
                                    case 4:
                                        c_encoded = dec_to_hex(result);
                                        break;
                                    default:
                                        printf("\n%s\n", PAGE_SEP);
                                        printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
                                        goto jump;
                                }

                                printf("\n结果：");
                                puts(c_encoded);

                                write_exp(output, current_exp, c_encoded);

                                free(res);
                                free(cleaned_input);
                                free(current_exp);
                                free(c_encoded);
                            }
                        }
                        fclose(output);
                    }
                    fclose(to_process);
                } else {
                    printf("\n%s\n", PAGE_SEP);
                    printf("没有已保存的文件供计算\n");
                    break;
                }

                free(input_path);
                free(output_path);

                break;
            case 2:
                printf("\n%s\n", PAGE_SEP);
                printf("请输入需计算的表达式，结尾无需'#'\n");
                char *input_exp;
                input_exp = get_user_input_string();

                char *cleaned_input;
                cleaned_input = clean_exp(input_exp);

                char *res = infix_to_suffix(cleaned_input,
                                            (int) strlen(cleaned_input));
                char *result;
                result = cal_suffix(res,
                                    (int) strlen(res));
                result = make_prec(result, FINAL_ACCURACY);

                int result_case;
                printf("\n请输入想要展示的结果进制：\n"
                       "二进制请输入 1\n"
                       "八进制请输入 2\n"
                       "十进制请输入 3\n"
                       "十六进制请输入 4\n");
                printf("请输入：");
                scanf("%d", &result_case);
                flush_linux();
                char *c_encoded;

                if (result_case == 1 ||
                    result_case == 2 ||
                    result_case == 4) {
                    if (RealBigNumCmp(result, "0") < 0) {
                        result = RealBigNumSub("0", result);
                    }
                    result = make_prec(result, -1);
                }

                switch (result_case) {
                    case 1:
                        c_encoded = dec_to_binary(result);
                        break;
                    case 2:
                        c_encoded = dec_to_oct(result);
                        break;
                    case 3:
                        c_encoded = result;
                        break;
                    case 4:
                        c_encoded = dec_to_hex(result);
                        break;
                    default:
                        printf("\n%s\n", PAGE_SEP);
                        printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
                        goto jump;
                }

                printf("结果：");

                puts(c_encoded);

                free(res);
                free(input_exp);
                free(cleaned_input);
                free(c_encoded);
                break;

            default:
                printf("\n%s\n", PAGE_SEP);
                printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
        }

        jump:
        printf("\n%s\n", PAGE_SEP);
        printf("继续使用本界面请输入 'again'.\n"
               "或者 退出本界面输入 'no'.\n请输入: ");
        char u[10];
        scanf("%s", u);
        flush_linux();
        if (strcmp(u, "again") == 0) continue;
        else if (strcmp(u, "no") == 0) break;
        else if ((strcmp(u, "again") != 0) || (strcmp(u, "no") == 0)) {
            printf("\n%s\n", PAGE_SEP);
            printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
            goto jump;
        }
    }
    return 0;
}

int quadratic() {

    while (1) {
        printf("\n%s\n", PAGE_SEP);
        printf("欢迎来到一元二次方程计算界面\n\n");
        char *a, *b, *c;
        printf("请输入一元二次方程的系数：\n");
        printf("请输入a的值 (ax^2)：\n");
        a = get_user_input_string();
        printf("请输入b的值 (bx^1)：\n");
        b = get_user_input_string();
        printf("请输入c的值 (cx^0)：\n");
        c = get_user_input_string();
        quadratic_equ(a, b, c);
        free(a);
        free(b);
        free(c);

        jump:
        printf("\n%s\n", PAGE_SEP);
        printf("继续使用本界面请输入 'again'.\n"
               "或者 退出本界面输入 'no'.\n请输入: ");
        char u[10];
        scanf("%s", u);
        flush_linux();
        if (strcmp(u, "again") == 0) continue;
        else if (strcmp(u, "no") == 0) break;
        else if ((strcmp(u, "again") != 0) || (strcmp(u, "no") == 0)) {
            printf("\n%s\n", PAGE_SEP);
            printf("对不起!\n你输入的命令错误，请重新输入.\n");
            goto jump;
        }
    }
    return 0;
}

int cubic() {
    while (1) {
        int cubic_case = -1;
        printf("\n%s\n", PAGE_SEP);
        printf("欢迎来到一元三次方程计算界面\n");
        printf("\n#选择解方程模式请输入 1\n"
               "#选择验证民科模式请输入 2\n");
        printf("请选择:");
        scanf("%d", &cubic_case);
        flush_linux();
        switch (cubic_case) {
            case 1:
                printf("\n%s\n", PAGE_SEP);
                printf("请输入一元三次方程的系数：\n");
                char *a, *b, *c, *d;
                printf("请输入a的值 (ax^3)：\n");
                a = get_user_input_string();
                printf("请输入b的值 (bx^2)：\n");
                b = get_user_input_string();
                printf("请输入c的值 (cx^1)：\n");
                c = get_user_input_string();
                printf("请输入d的值 (dx^0)：\n");
                d = get_user_input_string();
                char *res[5];
                Cardano(a, b, c, d, res);
                printf("\n方程 %sx^3 + %sx^2 + %sx + %s = 0 的解为：\n",
                       a, b, c, d);
                for (int i = 0; i < 5; i++) {
                    res[i] = make_prec(res[i], 4);
                }
                printf("x1 = %s + 0.0 i\n", res[0]);
                printf("x2 = %s + %s i\n", res[1], res[2]);
                printf("x3 = %s + %s i\n", res[3], res[4]);

                free(a);
                free(b);
                free(c);
                free(d);

                for (int i = 0; i < 5; i++) {
                    free(res[i]);
                }

                break;

            case 2:
                printf("\n%s\n", PAGE_SEP);

                int n;
                printf("请输入想要验证的方程个数:\n");
                scanf("%d", &n);
                flush_linux();

                printf("自动生成%d个方程验证盛金公式：\n", n);
                char input[4][50];
                char *cp[5], *sp[5];
                int i, j;
                srand(time(NULL));
                for (i = 0; i < n; i++) {
                    printf("\n%s\n", PAGE_SEP);
                    sprintf(input[0], "%ld", random() * ((random() % 2) ? 1 : -1));
                    sprintf(input[1], "%ld", random() * ((random() % 2) ? 1 : -1));
                    sprintf(input[2], "%ld", random() * ((random() % 2) ? 1 : -1));
                    sprintf(input[3], "%ld", random() * ((random() % 2) ? 1 : -1));

                    printf("\n第%d个方程 %sx^3 + %sx^2 + %sx + %s = 0\n",
                           i + 1, input[0], input[1], input[2], input[3]);

                    Cardano(input[0], input[1], input[2], input[3], cp);
                    Shengjin(input[0], input[1], input[2], input[3], sp);

                    if (AnswerMatch(cp, sp) < 0) {
                        printf("方程结果不一致\n");
                        printf("卡尔丹结果为：\n");
                        printf("x1 = %s + 0.0 i\n", cp[0]);
                        printf("x2 = %s + %s i\n", cp[1], cp[2]);
                        printf("x3 = %s + %s i\n", cp[3], cp[4]);
                        printf("盛金结果为：\n");
                        printf("x1 = %s + 0.0 i\n", sp[0]);
                        printf("x2 = %s + %s i\n", sp[1], sp[2]);
                        printf("x3 = %s + %s i\n", sp[3], sp[4]);
                    } else {
                        printf("方程结果在误差范围内一致\n");
                    }
                    for (j = 0; j < 5; j++) {
                        free(cp[j]);
                        free(sp[j]);
                    }
                }

                break;

            default:
                printf("\n%s\n", PAGE_SEP);
                printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
        }

        jump:
        printf("\n%s\n", PAGE_SEP);
        printf("\n继续使用本界面请输入 'again'.\n"
               "或者 退出本界面输入 'no'.\n请输入: ");
        char u[10];
        scanf("%s", u);
        flush_linux();
        if (strcmp(u, "again") == 0) continue;
        else if (strcmp(u, "no") == 0) break;
        else if ((strcmp(u, "again") != 0) || (strcmp(u, "no") == 0)) {
            printf("\n%s\n", PAGE_SEP);
            printf("对不起!\n你输入的命令错误，请重新输入.\n");
            goto jump;
        }
    }
    return 0;
}

int trigonometry() {
    while (1) {
        int trig_case = -1;
        printf("\n%s\n", PAGE_SEP);
        printf("欢迎来到三角函数计算界面\n\n");
        printf("#选择三角函数模式请输入 1\n"
               "#选择反三角函数模式请输入 2\n"
               "#选择对数模式请输入 3\n");
        printf("请选择:");
        scanf("%d", &trig_case);
        flush_linux();
        switch (trig_case) {
            case 1:
                printf("\n%s\n", PAGE_SEP);
                printf("请输入想要进行的三角函数计算：\n\n");

                int result_case = -1;
                printf("#sin请输入 1\n"
                       "#cos请输入 2\n"
                       "#tan请输入 3\n");
                printf("请输入：\n");
                scanf("%d", &result_case);
                flush_linux();

                int is_degree = -1;
                printf("\n%s\n", PAGE_SEP);
                printf("请选择输入角度或弧度：\n"
                       "#角度请输入 1\n"
                       "#弧度请输入 2\n");
                printf("请输入：\n");
                scanf("%d", &is_degree);
                flush_linux();
                char *tri_input;
                printf("\n%s\n", PAGE_SEP);
                printf("请输入需计算的值：\n");

                switch (is_degree) {
                    case 1:
                        tri_input = get_user_input_string();
                        break;
                    case 2:
                        tri_input = get_user_input_string();
                        tri_input = convert_radian(tri_input);
                        break;
                    default:
                        printf("\n%s\n", PAGE_SEP);
                        printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
                        goto jump;
                }

                char *tri_res;
                switch (result_case) {
                    case 1:
                        tri_res = RealBigNumSin(tri_input);
                        break;
                    case 2:
                        tri_res = RealBigNumCos(tri_input);
                        break;
                    case 3:
                        tri_res = RealBigNumTan(tri_input);
                        break;
                    default:
                        printf("\n%s\n", PAGE_SEP);
                        printf("对不起!\n你输入的三角函数计算"
                               "选择命令错误，请重新输入.\n\n");
                        goto jump;
                }

                tri_res = make_prec(tri_res, 4);
                printf("\n计算结果为：%s\n", tri_res);

                free(tri_input);
                free(tri_res);

                break;
            case 2:

                printf("\n%s\n", PAGE_SEP);
                printf("请输入想要进行的反三角函数计算：\n");

                int r_case = -1;
                printf("#arc sin请输入 1\n"
                       "#arc cos请输入 2\n"
                       "#arc tan请输入 3\n");
                printf("请输入：\n");
                scanf("%d", &r_case);
                flush_linux();

                char *t_input;
                printf("\n%s\n", PAGE_SEP);
                printf("请输入需计算的值：\n");
                t_input = get_user_input_string();

                char *t_res;
                switch (r_case) {
                    case 1:
                        if (RealBigNumAbsCmp(t_input, "1") > 0) {
                            printf("数值绝对值大于1，不存在反三角函数值\n");
                            goto jump;
                        }
                        t_res = RealBigArcSin(t_input);
                        break;
                    case 2:
                        if (RealBigNumAbsCmp(t_input, "1") > 0) {
                            printf("数值绝对值大于1，不存在反三角函数值\n");
                            goto jump;
                        }
                        t_res = RealBigArcCos(t_input);
                        break;
                    case 3:
                        t_res = RealBigArcTan(t_input);
                        break;
                    default:
                        printf("\n%s\n", PAGE_SEP);
                        printf("对不起!\n你输入的三角函数计算"
                               "选择命令错误，请重新输入.\n\n");
                        goto jump;
                }

                int degree = -1;
                printf("\n%s\n", PAGE_SEP);
                printf("请选择输入角度或弧度：\n"
                       "#角度请输入 1\n"
                       "#弧度请输入 2\n");
                printf("请输入：\n");
                scanf("%d", &degree);
                flush_linux();

                switch (degree) {
                    case 1:
                        break;
                    case 2:
                        t_res = convert_degree(t_res);
                        break;
                    default:
                        printf("\n%s\n", PAGE_SEP);
                        printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
                        goto jump;
                }

                t_res = make_prec(t_res, 4);
                printf("\n计算结果为：%s\n", t_res);

                free(t_input);
                free(t_res);

                break;

            case 3:

                printf("\n%s\n", PAGE_SEP);
                printf("请输入进行ln()计算的值：\n");
                char *m = get_user_input_string();
                if (RealBigNumCmp(m, "0") == 0) {
                    printf("计算结果为：ln(%s) = -infinity\n", m);
                    free(m);
                    break;
                } else if (RealBigNumCmp(m, "0") < 0) {
                    printf("负数不存在 ln() 值\n");
                    free(m);
                    break;
                }
                char *ln_res = RealBigNumLn(m);
                ln_res = make_prec(ln_res, 4);
                printf("计算结果为：ln(%s) = %s\n", m, ln_res);

                free(m);
                free(ln_res);

                break;

            default:
                printf("\n%s\n", PAGE_SEP);
                printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
        }

        jump:
        printf("\n%s\n", PAGE_SEP);
        printf("继续使用本界面请输入 'again'.\n"
               "或者 退出本界面输入 'no'.\n请输入: ");
        char u[10];
        scanf("%s", u);
        if (strcmp(u, "again") == 0) continue;
        else if (strcmp(u, "no") == 0) break;
        else if ((strcmp(u, "again") != 0) || (strcmp(u, "no") == 0)) {
            printf("\n%s\n", PAGE_SEP);
            printf("对不起!\n你输入的命令错误，请重新输入.\n");
            goto jump;
        }
    }
    return 0;
}

int simple_algebra() {
    while (1) {
        int alg_case = -1;
        printf("\n%s\n", PAGE_SEP);
        printf("欢迎来到简单代数运算计算界面\n");
        printf("\n#选择大整数最大公约数模式请输入 1\n"
               "#选择线性方程组求解模式请输入 2\n");
        printf("请选择:");
        scanf("%d", &alg_case);
        flush_linux();
        switch (alg_case) {
            case 1:
                printf("\n%s\n", PAGE_SEP);
                printf("注意：输入小数自动取整\n");
                printf("请输入第一个大整数\n");
                char *n1;
                char *n2;
                n1 = get_user_input_string();
                printf("请输入第二个大整数\n");
                n2 = get_user_input_string();
                n1 = make_prec(n1, -1);
                n2 = make_prec(n2, -1);
                char *gcd = IntBigNumGcd(n1, n2);
                printf("%s 和 %s 的最大公约数是 %s\n", n1, n2, gcd);

                free(n1);
                free(n2);
                free(gcd);

                break;

            case 2:

                printf("\n%s\n", PAGE_SEP);
                printf("求解线性方程组 Ax = B\n");

                printf("请输入A矩阵的长宽n (矩阵大小应为n*n) \n");
                printf("请输入n:");
                int n;
                scanf("%d", &n);
                flush_linux();

                printf("\n%s\n", PAGE_SEP);
                printf("A: 请依次输入 %d*%d 的整系数矩阵，每次仅输入"
                       "一个整型数，先行后列\n", n, n);
                int size = n * n;
                char **orig_matrix = (char **) malloc(sizeof(char *) * size);
                for (int i = 0; i < size; i++) {
                    int row = i / n + 1;
                    int col = i % n + 1;
                    printf("请输入 a(%d, %d):", row, col);
                    char *m_input = get_user_input_string();
                    orig_matrix[i] = m_input;
                }

                printf("\n%s\n", PAGE_SEP);
                printf("B: 请依次输入 %d*1 的整系数矩阵，每次仅输入"
                       "一个整型数，先行后列\n", n);
                char **orig_b = (char **) malloc(sizeof(char *) * n);
                for (int i = 0; i < n; i++) {
                    printf("请输入 a(%d, 1):", i + 1);
                    char *mb_input = get_user_input_string();
                    orig_b[i] = mb_input;
                }

                char **x;
                x = (char **) malloc(sizeof(char *) * n);
                for (int i = 0; i < n; i++) {
                    x[i] = (char *) malloc(sizeof(char) * n);
                    memset(x[i], '\0', n);
                }

                printf("\n%s\n", PAGE_SEP);
                printf("\n增广矩阵\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        printf("%s\t", orig_matrix[i * n + j]);
                    }
                    printf("%s\n", orig_b[i]);
                }

                printf("解向量为：\n");
                Gauss(orig_matrix, orig_b, x, n);
                for (int i = 0; i < n; i++)
                    printf("%s\t", make_prec(x[i], 4));
                printf("\n");

                for (int i = 0; i < size; i++) {
                    free(orig_matrix[i]);
                }

                free(orig_matrix);

                break;

            default:
                printf("\n%s\n", PAGE_SEP);
                printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
        }

        jump:
        printf("\n%s\n", PAGE_SEP);
        printf("\n继续使用本界面请输入 'again'.\n"
               "或者 退出本界面输入 'no'.\n请输入: ");
        char u[10];
        scanf("%s", u);
        if (strcmp(u, "again") == 0) continue;
        else if (strcmp(u, "no") == 0) break;
        else if ((strcmp(u, "again") != 0) || (strcmp(u, "no") == 0)) {
            printf("\n%s\n", PAGE_SEP);
            printf("对不起!\n你输入的命令错误，请重新输入.\n");
            goto jump;
        }
    }
    return 0;
}
