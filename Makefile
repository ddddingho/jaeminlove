spitesttest: spitest.o libMyPeri.a
	arm-linux-gnueabi-gcc spitest.o -l MyPeri -L. -o spitesttest

spitest.o: spitest.c spi.h
	arm-linux-gnueabi-gcc -g -c spitest.c -o spitest.o

libMyPeri.a: spi.o
	arm-linux-gnueabi-ar rc libMyPeri.a spi.o

spi.o: spi.c spi.h
	arm-linux-gnueabi-gcc -g -c spi.c -o spi.o

clean:
	rm spitesttest spi.o libMyPeri.a spitest.o
