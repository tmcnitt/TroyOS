#include "gdt.h"
#include "fb.h"
#include "serial.h"

struct gdt_ptr {
  unsigned short limit; //The size of the GDT table
  unsigned long base; //The location of the first entry
} __attribute__((__packed__));

typedef struct gdt_ptr gdt_ptr_t;


struct gdt_entry {
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
} __attribute__((__packed__));

typedef struct gdt_entry gdt_entry_t;

gdt_entry_t gdt_entries[GDT_ENTRIES];

/**
 * GDT_init setups up the GDT
 */
void GDT_init(){
  gdt_ptr_t gd;

  //The location of the first GDT entry
  gd.base = (unsigned long)&gdt_entries;
  //The size of the GDT table
  gd.limit = sizeof(gdt_entry_t)*GDT_ENTRIES;

  /* Our NULL descriptor */
  GDT_create_entry(0, 0, 0, 0, 0);

  /* The second entry is our Code Segment. The base address
  *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
  *  uses 32-bit opcodes, and is a Code Segment descriptor.
  *  Please check the table above in the tutorial in order
  *  to see exactly what each value means */
  GDT_create_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  /* The third entry is our Data Segment. It's EXACTLY the
  *  same as our code segment, but the descriptor type in
  *  this entry's access byte says it's a Data Segment */
  GDT_create_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);


  GDT_install((unsigned long)&gd);

  return;
}

/**
 * Creates an GDT entry
 * @param num    The position of the entry
 * @param base   The base of table
 * @param limit  The limit size of the table
 * @param access The access level
 * @param gran   The granularity of the entry
 */
void GDT_create_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt_entries[num].granularity |= (gran & 0xF0);
    gdt_entries[num].access = access;
}
