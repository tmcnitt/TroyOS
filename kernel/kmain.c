#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "mm.h"
#include "kb.h"



char test[] = "Boot complete. Welcome to TroyOS";


void kmain(void){
  fb_clear();

  //fb_status("Boot Info Checksum", magic);

 // unsigned long starting = (unsigned long)kernel_end;
 // fb_status("Load Memory Management", MM_init(starting));

  GDT_init();
  fb_status("Load GDT", 1);

  IDT_init();
  fb_status("Load IDT", 1);

  ISR_init();
  fb_status("Load ISR", 1);

  IRQ_init();
  fb_status("Load IRQ", 1);


  serial_config(SERIAL_COM1_BASE);
  fb_status("Configure Serial COM1", 1);

  KB_init();
  fb_status("Load keyboard", 1);

  fb_write("\n\n\n");

  fb_write(test);
  serial_write(SERIAL_COM1_BASE, test);

}
