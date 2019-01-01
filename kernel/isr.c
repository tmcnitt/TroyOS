#include "idt.h"
#include "io.h"
#include "serial.h"
#include "fb.h"
#include "isr.h"

/**
 * Setups the ISR
 */
void ISR_init(){
  CREATE_IDT_GATE(0, (unsigned int)isr0);
  CREATE_IDT_GATE(1, (unsigned int)isr1);
  CREATE_IDT_GATE(2, (unsigned int)isr2);
  CREATE_IDT_GATE(3, (unsigned int)isr3);
  CREATE_IDT_GATE(4, (unsigned int)isr4);
  CREATE_IDT_GATE(5, (unsigned int)isr5);
  CREATE_IDT_GATE(6, (unsigned int)isr6);
  CREATE_IDT_GATE(7, (unsigned int)isr7);
  CREATE_IDT_GATE(8, (unsigned int)isr8);
  CREATE_IDT_GATE(9, (unsigned int)isr9);
  CREATE_IDT_GATE(10, (unsigned int)isr10);
  CREATE_IDT_GATE(11, (unsigned int)isr11);
  CREATE_IDT_GATE(12, (unsigned int)isr12);
  CREATE_IDT_GATE(13, (unsigned int)isr13);
  CREATE_IDT_GATE(14, (unsigned int)isr14);
  CREATE_IDT_GATE(15, (unsigned int)isr15);
  CREATE_IDT_GATE(16, (unsigned int)isr16);
  CREATE_IDT_GATE(17, (unsigned int)isr17);
  CREATE_IDT_GATE(18, (unsigned int)isr18);
  CREATE_IDT_GATE(19, (unsigned int)isr19);
  CREATE_IDT_GATE(20, (unsigned int)isr20);
  CREATE_IDT_GATE(21, (unsigned int)isr21);
  CREATE_IDT_GATE(22, (unsigned int)isr22);
  CREATE_IDT_GATE(23, (unsigned int)isr23);
  CREATE_IDT_GATE(24, (unsigned int)isr24);
  CREATE_IDT_GATE(25, (unsigned int)isr25);
  CREATE_IDT_GATE(26, (unsigned int)isr26);
  CREATE_IDT_GATE(27, (unsigned int)isr27);
  CREATE_IDT_GATE(28, (unsigned int)isr28);
  CREATE_IDT_GATE(29, (unsigned int)isr29);
  CREATE_IDT_GATE(30, (unsigned int)isr30);
  CREATE_IDT_GATE(31, (unsigned int)isr31);
}




char exception_messages[19][50] = {
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt Exception",
  "Breakpoint Exception",
  "Into Detected Overflow Exception",
  "Out of Bounds Exception",
  "Invalid OpCode Exception",
  "No Coprocessor Exception",
  "Double Fault Exception",
  "Coprocessor Segment Overrun Exception",
  "Bad TSS Exception",
  "Segment Not Present Exception",
  "Stack Fault Exception",
  "General Protection Fault Exception",
  "Page Fault Exception",
  "Unknown Interrupt Exception",
  "Coprocessor Fault Exception",
  "Reserved",
  "Reserved",
};


void fault_handler(struct regs *r){
  if(r->int_no < 31){
    fb_write("");
    fb_write(exception_messages[r->int_no]);
    fb_write(" Error has occured. System halting");
    for(;;);
  }
}
