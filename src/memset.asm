bits 64
section .text
global memset

memset:
    mov rax, rdi    ; mov address of rdi into rax
    xor rcx, rcx    ; init counter to 0

loop:
    cmp rcx, rdx
    je end
    mov byte [rdi + rcx], sil   ; mov value of int c into *rdi sil 8-bits rsi
    inc rcx
    jmp loop                     ; continue if count < n 

end:
    ret

