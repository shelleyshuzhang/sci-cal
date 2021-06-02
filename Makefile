all:
	gcc -c BigNumOps.c -g
	gcc -c RealNumOps.c -g
	gcc -c Math.c -g
	gcc -c Polynomial.c -g
	gcc -c Algebra.c -g
	gcc -c AlgeExp.c -g
	gcc -c Quadratic.c -g
	gcc -c Conversion.c -g
	gcc test1.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test1
	gcc test2.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test2
	gcc test3.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test3
	gcc test4.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test4
	gcc test5.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test5
	gcc test6.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test6
	gcc test7.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o AlgeExp.o Quadratic.o Conversion.o -lm -g -o test7
