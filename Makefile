#
# MAKEFILE FOR POULPY-OS
#

# Set source dirs
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c bin/*.c) 
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h bin/*.h)
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

#Set compiler
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
CFLAGS = -g -std=c99 

#Build rules 
poulpyOS.bin: boot/bootMain.bin kernel.bin
	cat $^ > $@

kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary


#Debug build rules
debug: poulpyOS.bin kernel.elf
	qemu-system-i386 -s -fda poulpyOS.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ 

run: poulpyOS.bin
	qemu-system-x86_64 -fda poulpyOS.bin

iso: poulpyOS.bin grub.cfg
	@mkdir -p boot/grub
	@cp poulpyOS.bin boot/
	@cp grub.cfg boot/grub
	@grub-mkrescue -o poulpyOS.iso ./

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.o poulpyOS.bin
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o