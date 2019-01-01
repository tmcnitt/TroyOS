#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H


void IDT_init();
void IDT_install(unsigned long);
void IDT_create_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
#define CREATE_IDT_GATE(id, handler) IDT_create_entry(id, handler, 0x08, 0x8E)


#endif /* INCLUDE_IO_H */
