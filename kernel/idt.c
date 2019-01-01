#include "idt.h"
#include "io.h"

struct idt_entry {
   unsigned short handler_low; // offset bits 0..15
   unsigned short selector; // a code segment selector in GDT or LDT
   unsigned char zero;      // unused, set to 0
   unsigned char flags; // type and attributes, see below
   unsigned short handler_high; // offset bits 16..31
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;


struct idt_ptr {
    unsigned short limit;
    unsigned long base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;


/**
 * Setups the IDT table
 */
void IDT_init(){
  idt_ptr.limit = (sizeof(idt_entry_t)*256)-1;
  idt_ptr.base = (unsigned long)&idt_entries;

  // disable the legacy PIC
  outb(0xA1, 0xFF);
  outb(0x21, 0xFF);

  IDT_install((unsigned long)&idt_ptr);
}


/**
 * Creates a table in the IDT
 * @param num   The position for the entry
 * @param base  The base position of where the callback function is
 * @param sel   The selector of where the kernel is
 * @param flags The flags of the entry
 */
void IDT_create_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
  /* The interrupt routine's base address */
  idt_entries[num].handler_low = (base & 0xFFFF);
  idt_entries[num].handler_high = (base >> 16) & 0xFFFF;

  /* The segment or 'selector' that this IDT entry will use
  *  is set here, along with any access flags */
  idt_entries[num].selector = sel;
  idt_entries[num].zero = 0;
  idt_entries[num].flags = flags;
}
