all:
	gcc -c BigNumOps.c -g
	gcc -c RealNumOps.c -g
	gcc -c Math.c -g
	gcc -c Polynomial.c -g
	gcc -c Algebra.c -g
	gcc test1.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o -lm -g -o test1
	gcc test4.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o -lm -g -o test4
	gcc test5.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o -lm -g -o test5
	gcc test7.c  BigNumOps.o  RealNumOps.o Math.o Polynomial.o Algebra.o -lm -g -o test7
