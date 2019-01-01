
global GDT_install

section .text:

GDT_install:
  mov     eax, [esp+4]        ; fetch gdt_ptr from parameter stack
  lgdt    [eax]               ; load gdt table
  ; load cs segment by doing a far jump
  jmp     0x8:.reload_segments

.reload_segments:
  mov     ax, 0x10
  mov     ds, ax
  mov     ss, ax
  mov     es, ax
  mov     gs, ax
  mov     fs, ax
  ret
