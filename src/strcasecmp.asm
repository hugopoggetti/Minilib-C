bits 64
section .text
global strcasecmp

strcasecmp:
    XOR r8, r8                     ; initialise counter to zero
    MOVZX r9, BYTE [rdi + r8]      ; convert character in 64 bits
    MOVZX r10, BYTE [rsi + r8]

loop:
    cmp r9, 0
    JE return
    cmp r10, 0
    je return
    CMP r9, 'A'                    ; if s1[i] >= 'A'
    JL continue_                   ; jump because i don't need to convert it
    CMP r9, 'Z'                    ; if s1[i] <= 'Z'
    JG continue_                   ; jump
    ADD r9, 32                     ; convert r9 to lowercase s1[i] - 32

continue_:
    CMP r10, 'A'                   ; if s2[i] >= 'A'
    JL continue__                  ; jump
    CMP r10, 'Z'                   ; if s2[i] <= 'Z'
    JG continue__
    ADD r10, 32                    ; convert r10 to lowercase  s2[i] - 32

continue__:
    CMP r9, r10                    ; compare r9 and r10
    JNE return                     ; if r9 != r10 -> s1[i] != s2[i]  return error value
    JMP loop_again                  ; check if it's the end of the string

loop_again:
    INC r8                         ; increment loop counter
    MOVZX r9, BYTE [rdi + r8]      ; convert character in 64 bits
    MOVZX r10, BYTE [rsi + r8]
    JMP loop                       ; loop

return:
    SUB r9, r10                   ; put in r9 the result of s[i] - s2[i]
    MOV rax, r9                   ; put the value of r11 in rax to return it
    ret

