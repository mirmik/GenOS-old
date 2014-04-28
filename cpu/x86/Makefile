

all:
	gcc -c  boot.S -o boot.o
	objcopy -O binary boot.o kernel.sys  
	objdump -D -b binary -mi386 kernel.sys > kkk
	
