final.elf : main.o 1.o 2.o 3.o
    gcc -o final.elf main.o 1.o 2.o 3.o

main.o : main.c myProject.h
    gcc main.c -c

1.o : 1.c myProject.h 
    gcc 1.c -c

2.o : 2.c myProject.h 
    gcc 2.c -c

3.o : 3.c myProject.h
    gcc 3.c -c