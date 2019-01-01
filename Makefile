ARCH = i386
SOURCES = $(shell find kernel/ -name "*.c" -o -name "*.s" -o  -name "*.h" -o -path kernel/arch -prune)
OBJECTS =  kernel/arch/$(ARCH)/loader.o $(filter-out kernel/arch, $(filter-out $(ARCH), $(filter-out %.h, $(patsubst %.c, %.o, $(patsubst %.s, %.o,$(SOURCES))))))


CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
				-nostartfiles -nodefaultlibs -Wall -Wextra  -c
LDFLAGS = -T  kernel/arch/$(ARCH)/link.ld  -m elf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	 ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	 cp kernel.elf iso/boot/kernel.elf
	 genisoimage -R                              \
							 -b boot/grub/stage2_eltorito    \
							 -no-emul-boot                   \
							 -boot-load-size 4               \
							 -A os                           \
							 -input-charset utf8             \
							 -boot-info-table                \
							 -o os.iso                       \
							 iso

run: os.iso
	 bochs -f bochsrc.txt -q


%.o: %.c
	 $(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	 $(AS) $(ASFLAGS) $< -o $@

clean:
	 rm -rf **/*.o kernel.elf os.iso kernel/$(ARCH)/loader.o **/*.gch iso/boot/kernel.elf
