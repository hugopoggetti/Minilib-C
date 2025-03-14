bits 64
section .text
global memcpy

memcpy:
    MOV rax, rdi                 ; store the address of dest
    XOR rcx, rcx                 ; initialise rcx to zero

loop:
    CMP rcx, rdx                 ; compare if i < n
    je end                       ;  return rax
    MOVZX r8, byte [rsi + rcx]   ; load BYTE of src into dest
    MOV [rdi + rcx], r8b         ; copy the byte b of r8 into address rdi + rcx
    INC rcx                      ; increment rcx
    jmp loop                          ; loop again

end:
    ret
