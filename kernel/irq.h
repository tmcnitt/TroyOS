
#ifndef INCLUDE_IRQ_H
#define INCLUDE_IRQ_H

  #include "isr.h"


  extern void irq0();
  extern void irq1();
  extern void irq2();
  extern void irq3();
  extern void irq4();
  extern void irq5();
  extern void irq6();
  extern void irq7();
  extern void irq8();
  extern void irq9();
  extern void irq10();
  extern void irq11();
  extern void irq12();
  extern void irq13();
  extern void irq14();
  extern void irq15();

  typedef void (*handler_t)(regs_t *reg);

  void IRQ_add_handler(handler_t handler, int code);
  void IRQ_init();
#endif
