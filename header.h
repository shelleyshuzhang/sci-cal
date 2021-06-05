#ifndef _ALL_HEADER_H_
#define _ALL_HEADER_H_

#include <unistd.h>

#include "task1/BigNumOps.h"
#include "task1/RealNumOps.h"
#include "task2/AlgeExp.h"
#include "task3/Quadratic.h"
#include "task4/Polynomial.h"
#include "task5/Math.h"
#include "task6/Conversion.h"
#include "task7/Algebra.h"

#define PAGE_SEP "**********************************************************************"

int normal_calculation();

int quadratic();

int cubic();

int trigonometry();

int simple_algebra();

char* get_user_input_string();

void flush_linux();

#endif
