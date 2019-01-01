global IDT_install

section text:
  IDT_install:
    mov eax, [esp+4]    ; move ldt_ptr to eax
    lidt [eax]
    ret
