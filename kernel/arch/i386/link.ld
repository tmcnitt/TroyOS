ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
   /* The kernel will live at 3GB + 1MB in the virtual
      address space, which will be mapped to 1MB in the
      physical address space. */
   . = 0xC0100000;
    _KERNEL_START = .;
   .text : AT(ADDR(.text) - 0xC0000000) {
       *(.text)
       *(.rodata*)
   }

   .data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000) {
       *(.data)
   }

   .bss : AT(ADDR(.bss) - 0xC0000000) {
       _sbss = .;
       *(COMMON)
       *(.bss)
       _ebss = .;
   }

    _KERNEL_END = .;
    _KERNEL_SIZE = _KERNEL_END - _KERNEL_START;
}
ASSERT(_KERNEL_SIZE < 0x100000, "Kernel exceeds the 1 MB limit. asm/loader.s must be updated to work with a >1MB kernel");
