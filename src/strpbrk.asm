bits 64
section .text
global strpbrk

strpbrk:
    xor rcx, rcx                  ; initialise rcx to 0

loop_i:
    CMP BYTE [rdi + rcx], 0       ; check if s1[i] == '\0'
    JE return_null                ; return null if no character has been find
    JMP initialise_loop_j         ; run loop on the second string

increment_loop_i:
    INC rcx                       ; increment_loop_i
    JMP loop_i                    ; loop_i again

initialise_loop_j:
    xor r8, r8                    ; initialise r8 to zero
    JMP loop_j                    ; run loop in second string

loop_j:
    CMP BYTE [rsi + r8], 0        ; check if s2[i] == '\0'
    JE increment_loop_i           ; if its the end of s2 go to s[i + 1]
    MOVZX r9, BYTE [rdi + rcx]    ; put the value of s1[i] in r9
    MOVZX r10, BYTE [rsi + r8]    ; put the value of s2[count] in r10
    CMP r9, r10                   ; compare s1[i] == s2[count]
    JE return_ptr                 ; first occurrence in the string is find return ptr
    INC r8                        ; increment count
    JMP loop_j                    ; loop s2 again

return_ptr:
    LEA rax, [rdi + rcx]          ; put the address of s1 + i in rax
    ret

return_null:
    XOR rax, rax                 ; put NULL in rax
    ret
