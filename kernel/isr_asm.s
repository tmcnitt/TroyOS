  %macro no_error_code_interrupt_handler 1
  global isr%1
  isr%1:
      cli
      push    byte 0                     ; push 0 as error code;
      push    byte %1                    ; push the interrupt number;
      jmp     isr_common_stub    ; jump to the common handler
  %endmacro

  %macro error_code_interrupt_handler 1
  global isr%1
  isr%1:
      cli
      push    byte %1                    ; push the interrupt number
      jmp     isr_common_stub    ; jump to the common handler
  %endmacro



extern fault_handler
section text:
  ; This is our common ISR stub. It saves the processor state, sets
  ; up for kernel mode segments, calls the C-level fault handler,
  ; and finally restores the stack frame.
  isr_common_stub:
      pusha
      push ds
      push es
      push fs
      push gs
      mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
      mov ds, ax
      mov es, ax
      mov fs, ax
      mov gs, ax
      mov eax, esp   ; Push us the stack
      push eax
      mov eax, fault_handler
      call eax       ; A special call, preserves the 'eip' register
      pop eax
      pop gs
      pop fs
      pop es
      pop ds
      popa
      add esp, 8     ; Cleans up the pushed error code and pushed ISR number
      iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!


no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
error_code_interrupt_handler 7
error_code_interrupt_handler 8
error_code_interrupt_handler 9
error_code_interrupt_handler 10
error_code_interrupt_handler 11
error_code_interrupt_handler 12
error_code_interrupt_handler 13
error_code_interrupt_handler 14
error_code_interrupt_handler 15
error_code_interrupt_handler 16
error_code_interrupt_handler 17
error_code_interrupt_handler 18
error_code_interrupt_handler 19
error_code_interrupt_handler 20
error_code_interrupt_handler 21
error_code_interrupt_handler 22
error_code_interrupt_handler 23
error_code_interrupt_handler 24
error_code_interrupt_handler 25
error_code_interrupt_handler 26
error_code_interrupt_handler 27
error_code_interrupt_handler 28
error_code_interrupt_handler 29
error_code_interrupt_handler 30
error_code_interrupt_handler 31
