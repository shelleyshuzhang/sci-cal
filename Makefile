all:
	gcc -c task1/BigNumOps.c -g -o output/BigNumOps.o
	gcc -c task1/RealNumOps.c -g -o output/RealNumOps.o
	gcc -c task5/Math.c -g -o output/Math.o
	gcc -c task4/Polynomial.c -g -o output/Polynomial.o
	gcc -c task7/Algebra.c -g -o output/Algebra.o
	gcc -c task2/AlgeExp.c -g -o output/AlgeExp.o
	gcc -c task3/Quadratic.c -g -o output/Quadratic.o
	gcc -c task6/Conversion.c -g -o output/Conversion.o
	gcc test/test1.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test1
	gcc test/test2.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test2
	gcc test/test3.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test3
	gcc test/test4.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test4
	gcc test/test5.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test5
	gcc test/test6.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test6
	gcc test/test7.c  output/BigNumOps.o  output/RealNumOps.o output/Math.o output/Polynomial.o output/Algebra.o output/AlgeExp.o output/Quadratic.o output/Conversion.o -lm -g -o test7
