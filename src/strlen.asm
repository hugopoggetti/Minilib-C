bits 64
section .text
global strlen

strlen:
    xor rax, rax               ; init rax to 0 

loop:
    cmp byte [rdi + rax], 0x00 ; continue loop if str[i] != '\0'
    je end                     ; return counter if it's '\0'
    inc rax                    ; increment counter
    jmp loop                   ; jmp to loop again

end:
    ret
