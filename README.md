# A Scientific Calculator
This is a scientific calculator implemented in C and works best under linux environment. Some documentations and comments are written in Chinese.

## 代码说明：
编译命令见Makefile，在Linux环境下，进入本目录直接输入make，即可完成程序编译。

*代码使用详细内容参见 程序使用文档.pdf

## 代码测试说明:
1. test1.c 对应功能项1，大整数运算
2. test2.c 对应功能项2，表达式求值
3. test3.c 对应功能项3，一元二次方程求值
4. test4.c 对应功能项4，一元三次方程求值
5. test5.c 对应功能项5，三角函数，反三角函数，对数运算
6. test6.c 对应功能项6，进制转换
7. test7.c 对应功能项7，大整数求最大公约数和线性方程求解

## 后续开发类使用说明(仅开发类需阅读，使用无需阅读)：
1. 编写需要显示的引用header.h，header.h包含实现的所有函数功能。
2. gcc编译命令需要加-lm，需要使用math的数学库
3. 大整数（包括带小数的实数）运算方面，Unsigned开头的函数仅支持正整数，并且封装不够完全，本人利用这些函数实现RealNumOps.c中的函数，
建议他人能不直接使用就不使用，而是使用Real开头的函数，Real开头的函数字符串格式可以是整数可以是浮点数，支持整数，支持小数，
对应的实现在RealNumOps.c中。
4. 使用RealBigNumAdd这类接口返回的字符串会占用内存，如果只是用作临时变量，记得及时释放，如不及时释放可能产生内存溢出，例如：
add = RealBigNumAdd(a, b);
printf("add %s\n", add);
free(add);
5. 函数使用方法可以参考上面的test用例中的写法。
6. 输入合法性检查可能不够完善，需要进一步测试
7. 程序存在未知bug，后续开发类使用需进一步测试

*程序详细开发信息请阅读 程序开发文档.pdf
