bits 64
section .text
global strcmp

strcmp:
    xor r11, r11

loop:
    MOV r9b, byte [rdi + r11]            ; mov byte in r9 to compare later
    MOV r10b, byte [rsi + r11]           ; mov byte in r10 to compare later
    CMP r9b, r10b                ; compare byte of r9 and r10
    jne return                     ; if r9 != r10  jump to not equal
    CMP r9b, 0x0                   ; if r9 == '\0'
    je return
    cmp r10b, 0x0
    je return                      ; jump tu return 0 beacause strings are equal
    inc r11
    jmp loop                       ; jump in loop to continue

return:
    SUB r9, r10                  ; diff = s1[counter] - s2[counter]
    MOV rax, r9                   ; rax = diff
    ret

