//
// Created by 张舒 on 5/28/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../header.h"

#define FINAL_ACCURACY 10

int main() {
    // 用户输入模式
//    char *input;
//    input = (char *) malloc(100 * sizeof(char));
//
//    char c;
//    int index = 0;
//
//    while ((c = getchar()) != '\n' && index < 100) {
//        input[index] = c;
//        index++;
//    }
//
//    char *res = infix_to_suffix(input, index, suffix);
//
//    puts(res);
//
//    cal_suffix(res, (int)strlen(res));
//
//    free(input);
//    free(res);

    // 文件自动读取模式
    char* buffer;
    if((buffer = getcwd(NULL, 0)) == NULL) {
        // TODO: 修改之前的 error message，记住改成不要退出，
        // 而是汇报error，尝试再次执行，free 所有 pointer
        perror("无法读取当前路径\n");
        exit(0);
    } else {
        strcat(buffer, "/default_exp.txt");
        printf("%s\n", buffer);
    }
    char *input_path = buffer;

    char* output_buffer;
    output_buffer = getcwd(NULL, 0);
    strcat(output_buffer, "/default_exp_output.txt");
    char *output_path = output_buffer;

    int exist = access(input_path, F_OK);
    int output_exist = access(output_path, F_OK);

    if (exist == 0) {
        FILE *to_process = fopen(input_path, "r");
        if (to_process == NULL) {
            perror("无法打开默认输入文件\n");
            exit(0);
        } else {

            FILE *output;
            if (output_exist == 0) {
                output = fopen(output_path, "a");
            } else {
                output = fopen(output_path, "w");
            }

            if (output == NULL) {
                perror("无法打开默认输出文件\n");
                exit(0);
            } else {
                while (!feof(to_process)) {
                    char *current_exp;
                    current_exp = read_exp(to_process);
                    if (current_exp[0] == '\0') {
                        break;
                    }
                    printf("This is %s\n", current_exp);
                    char *res = infix_to_suffix(current_exp,
                                                (int) strlen(current_exp));
                    char *result;
                    result = cal_suffix(res, (int) strlen(res));
                    result = make_prec(result, FINAL_ACCURACY);
                    puts(result);

                    write_exp(output, current_exp, result);

                    free(result);
                    free(res);
                    free(current_exp);
                }
            }
        }
        fclose(to_process);
    } else {
        perror("没有已保存的文件供计算\n");
    }

    free(input_path);
    free(output_path);

    // 输入文件路径读取模式
//    printf("请输入需计算文件的路径\n");
//    char *file_path;
//    file_path = (char *) malloc(100 * sizeof(char));
//
//    char c;
//    int index = 0;
//
//    while ((c = getchar()) != '\n' && index < 100) {
//        file_path[index] = c;
//        index++;
//    }
//
//    file_path[index] = '\0';



    return 0;
}