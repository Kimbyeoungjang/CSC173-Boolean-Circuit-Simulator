gcc -c -o Boolean.o Boolean.c

gcc -c -o Circuit.o Circuit.c

gcc -c -o Gates.o Gates.c

gcc -c -o main.o main.c

gcc -o build Boolean.o Circuit.o Gates.o main.o

build.exe

pause