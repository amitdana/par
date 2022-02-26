par: par.o
        gcc -g -ansi -Wall -pedantic par.o -o par

par.o: par.c
        gcc -c -ansi -pedantic -Wall par.c -o par.o


