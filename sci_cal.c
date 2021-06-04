//
// Created by 张舒 on 6/4/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void user_manual();

int start_the_program();

int main() {
    while (1)
    {
        printf("\n");

        printf("用户你好，欢迎来到本产品的菜单界面:\n\n");
        printf("1.开始使用产品功能请按 'enter'\n");
        printf("2.阅读用户说明请按(初次使用强烈建议) 'help'\n");
        printf("3.退出产品请按 'exit'\n");

        printf("请输入:");
        char start[10], e[] = "enter", h[] = "help", end[] = "exit";
        memset(start, '\0', sizeof(start));
        char c;
        int index = 0;
        while ((c = getchar()) != '\n' && index < 10) {
            start[index] = c;
            index++;
        }
        if (strcmp(start, e) == 0) {
            start_the_program();
        } else if (strcmp(start, h) == 0) {
            user_manual();
        } else if ((strcmp(start, e) != 0) && (strcmp(start, h) != 0) && (strcmp(start, end) != 0)) {
            printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
            continue;
        } else if (strcmp(start, end) == 0) {
            break;
        }
    }
    return 0;
}

int start_the_program() {

    printf("\n欢迎使用本科学计算器产品：\n");
    while (1) {

        char e1[20], type[] = "yes", anti_type[] = "no";
        printf("\n继续使用请输入 'yes'\n或者\n退出请输入 'no'\n");
        printf("请输入:");
        scanf("%s", e1);
        if (strcmp(e1, type) == 0) {
            printf("\n请阅读并选择需要进行的计算操作类型\n请输入对应的编号（如：3）:\n");
            printf("#基本代数表达式求值 (具体包括大数，进制无符号数，混合的四则运算，乘方，开方) 请输入编号1\n");
            printf("#实数系一元二次方程求解 请输入编号2\n");
            printf("#实数系一元三次方程求解 请输入编号3\n");
            printf("#三角函数求解 (包括三角函数，反三角函数，和对数) 请输入编号4\n");
            printf("#简单代数运算 (包括求大整数最大公约数，和解基本线性方程组) 请输入编号5\n");
            int calculator;
            printf("请选择:");
            scanf("%d", &calculator);
            flush_linux();
            switch (calculator)
            {
                case 1:
                    normal_calculation();
                    break;
                case 2:
                    quadratic();
                    break;
                case 3:
                    cubic();
                    break;
                case 4:
                    trigonometry();
                    break;
                case 5:
                    simple_algebra();
                    break;
                default:
                    printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
            }
        }
        else if (strcmp(e1, anti_type) == 0)
        {
            break;
        } else if ((strcmp(e1, type) != 0) &&
                   (strcmp(e1, anti_type) != 0))
        {
            printf("对不起!\n你输入的命令错误，请重新输入.\n\n");
            continue;
        }
    }
    return 0;
}

void user_manual() {
    while (1) {
        printf("\n欢迎来到使用说明界面\n");
        printf("\n请按照以下提示使用本计算器\n\n");
        printf("计算器申明:\n\n1.本计算器支持以下7项基本功能：\n");
        printf("\n  a.大数运算：包括整数，负数，和浮点数的四则运算，乘方，和开方\n");
        printf("\n  b.基本代数表达式求值：包括四则运算，乘方，开方和括号，适用于大数"
               "和二，八，十，十六进制，支持文件读入和保存\n");
        printf("\n  c.一元二次方程求解：支持大数，包括负数和浮点数，系数必须为实数，"
               "求解支持复数域\n");
        printf("\n  d.一元三次方程求解（使用卡尔丹公式法）：包括解一元三次方程和验证"
               "民科法，民科法为盛金公式，正规求解则一律使用\n  卡尔丹公式支持大数，包括负"
               "数和浮点数，系数必须为实数，求解支持复数域\n");
        printf("\n  e.三角函数求解：包括三角函数，反三角函数，和对数，支持角度和度数，支持"
               "负数和浮点数\n");
        printf("\n  f.进制转换：支持二进制，八进制，十进制，十六进制无符号数和无符号"
               "大数的相互转换，同时与功能b结合，可以计算基本\n  表达式，包括四则运算，乘方，"
               "开方和括号, 但需注意有符号数和浮点数会被强制转换为无符号数\n");
        printf("\n  g.简单代数运算：包括求大整数最大公约数和解基本线性方程组\n\n");
        printf("2.计算表达式时，输入乘方 n 用 ^n 表示，开方 n 用 ^(1/n) 表示，"
               "负数必须添加括号，如 (-n)\n\n");
        printf("3.计算表达式文件输入模式提供默认读入和保存路径，文件中每个表达式必须以'#'结尾\n\n");
        printf("4.小数一般默认保存到小数点后4位\n\n");
        printf("5.进制默认使用前缀'0b'，'0o'，和'0x'分别代表二进制，八进制，和十六进制，大小"
               "写均可，如'0b10010'，如无前缀默认\n为十进制\n");
        printf("\n作者/联系人邮箱: 张舒 zhang.shu4@northeastern.edu\n\n");
        printf("输入 'home' 回到主界面.\n请输入:");
        char* cm;
        cm = get_user_input_string();
        if (strcmp(cm, "home") == 0) break;
        else if (strcmp(cm, "home") != 0) {
            printf("很抱歉!\n你输入的命令错误，请重新输入.\n\n");
            continue;
        }
    }
}
