project_textbut.elf: project_textbut.o libMyPeri.a
	arm-linux-gnueabi-gcc project_textbut.o -l MyPeri -L. -lpthread -o project_textbut.elf

project_textbut.o: project_textbut.c textlcd.h button.h fnd.h colorled.h
	arm-linux-gnueabi-gcc -c project_textbut.c -o project_textbut.o
		
libMyPeri.a : textlcd.o button.o fnd.o colorled.o 
	arm-linux-gnueabi-ar rc -c libMyPeri.a -o textlcd.o button.o fnd.o colorled.o 

colorled.o: colorled.c colorled.h
	arm-linux-gnueabi-gcc -g -c colorled.c -o colorled.o

fnd.o: fnd.c fnd.h
	arm-linux-gnueabi-gcc -g -c fnd.c -o fnd.o

button.o: button.c button.o
	arm-linux-gnueabi-gcc -g -c button.c -o button.o

textlcd.o: textlcd.h textlcd.c
	arm-linux-gnueabi-gcc -g -c textlcd.c -o textlcd.o


clean: 
	rm project_textbut.elf project_textbut.o 
