#include "idt.h"
#include "io.h"
#include "irq.h"
#include "fb.h"

handler_t handlers[16];

/**
 * Setups IRQ
 */
void IRQ_init(){
  //Disable the normal PIC controllers
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  CREATE_IDT_GATE(32, (unsigned long)irq0);
  CREATE_IDT_GATE(33, (unsigned long)irq1);
  CREATE_IDT_GATE(34, (unsigned long)irq2);
  CREATE_IDT_GATE(35, (unsigned long)irq3);
  CREATE_IDT_GATE(36, (unsigned long)irq4);
  CREATE_IDT_GATE(37, (unsigned long)irq5);
  CREATE_IDT_GATE(38, (unsigned long)irq6);
  CREATE_IDT_GATE(39, (unsigned long)irq7);
  CREATE_IDT_GATE(40, (unsigned long)irq8);
  CREATE_IDT_GATE(41, (unsigned long)irq9);
  CREATE_IDT_GATE(42, (unsigned long)irq10);
  CREATE_IDT_GATE(43, (unsigned long)irq11);
  CREATE_IDT_GATE(44, (unsigned long)irq12);
  CREATE_IDT_GATE(45, (unsigned long)irq13);
  CREATE_IDT_GATE(46, (unsigned long)irq14);
  CREATE_IDT_GATE(47, (unsigned long)irq15);

  __asm__ __volatile__ ("sti");

}

/**
 * Registers a handler for IRQ
 * @param handler The handler callback
 * @param code    The IRQ code (starting at 0)
 */
void IRQ_add_handler(handler_t handler, int code){
  if(code >= 0 && code < 17){
    handlers[code] = handler;
  }
}

void irq_handler(regs_t *r){
  if(handlers[r->int_no-32]){
    handlers[r->int_no-32](r);
  }

  outb(0x20, 0x20);
}
