CROSS=arm-none-eabi-

QEMU=qemu-system-arm

CC=$(CROSS)gcc
OBJC=$(CROSS)objcopy

CFLAGS=-fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra

CPUTYPE= -mcpu=arm1176jzf-s

OBJS= \
boot.o \
kernel.o

LINK_LIST= \
$(OBJS)

all: colonel.bin

colonel.elf: $(OBJS)
	$(CC) -T linker.ld -ffreestanding -O2 -nostdlib -o $@ $(LINK_LIST)

colonel.bin: colonel.elf
	 $(OBJC) $< -O binary $@

.c.o:
	$(CC) $(CPUTYPE) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CPUTYPE) -fpic -ffreestanding -c $< -o $@

clean:
	rm -f colonel.bin
	rm -f colonel.elf
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

qemu: colonel.elf
	$(QEMU) -m 256 -M raspi2 -serial stdio -kernel $<

-include $(OBJS:.o=.d)
