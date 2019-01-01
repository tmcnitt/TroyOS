#ifndef INCLUDE_MM_H
#define INCLUDE_MM_H

  int MM_init(unsigned long starting_address);

  //Taken from: http://www.gnu.org/software/grub/manual/multiboot/html_node/multiboot.h.html
  //And http://wiki.osdev.org/Detecting_Memory_(x86)#Detecting_Low_Memory
  typedef struct multiboot_info
  {
    unsigned long flags;
    unsigned long mem_lower;
    unsigned long mem_upper;
    unsigned long boot_device;
    unsigned long cmdline;
    unsigned long mods_count;
    unsigned long mods_addr;
    unsigned long mmap_length;
    unsigned long mmap_addr;
  } multiboot_info_t;


#endif
