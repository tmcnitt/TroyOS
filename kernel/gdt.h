#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H




#define GDT_ENTRIES 3
#define SEGMENT_BASE    0
#define SEGMENT_LIMIT   0xFFFFF


void GDT_init();
void GDT_install(unsigned long);
void GDT_create_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);



#endif /* INCLUDE_IO_H */
