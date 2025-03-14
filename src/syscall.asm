bits 64
section .text
global syscall

syscall:
    syscall
    ret

