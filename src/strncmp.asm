bits 64
section .text
global strncmp

; TODO: test 2 empty string
strncmp:
    xor r8, r8                   ; set counter to zero
loop:
    cmp r8, rdx
    je return 
    MOVZX r9, byte [rdi + r8]    ; mov byte in r9 to compare later
    MOVZX r10, byte [rsi + r8]   ; mov byte in r10 to compare later
    CMP r9, r10                  ; compare byte of r9 and r10
    JNE return         ; if r9 != r10  jump to not equal
    cmp r9, 0x0
    je return
    cmp r10, 0x0
    je return
    INC r8                       ; increment counter r8
    JMP loop                     ; jump in loop to continue

return:
    SUB r9, r10                  ; diff = s1[counter] - s2[counter]
    MOV rax, r9                  ; rax = diff
    ret

