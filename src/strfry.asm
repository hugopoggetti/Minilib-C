bits 64
section .text
global strfry
;extern rand

strfry:
    mov rax, rdi ; put address of rdi in rax to save it
    xor r9, r8   ; init count to 0

loop:
    cmp byte [rax + r9], 0x0      ; cmp s[i] to '\0' 
    je end
    ; call rdrand
    mov r10b, byte [rdi]           ; mov the result of rand in r9b
    mov byte [rax + r9], r9b
    inc r9
    jmp loop

end:
    ret
