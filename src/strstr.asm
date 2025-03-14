bits 64
section .text
global strstr

; TODO: not return null with 2 "" "" 
strstr:
    XOR r8, r8                    ; initialise counter_i to 0
    XOR r9, r9                    ; initialise counter_j to 0

loop_i:
    CMP BYTE [rdi + r8], 0        ; check if its the end of the string
    JE return_null                ; return NULL
    MOVZX r10, BYTE [rdi + r8]    ; mov s1[i] to R10
    MOVZX r11, BYTE [rsi]         ; mov s2[0] to R11
    CMP r10, r11,                 ; if s1[i] == s1[0]
    JE initialise_loop_j          ; start loop_j
    CMP r11, 0                    ; check if s2[0] == '\0'
    JE return_ptr                 ; return all the string if s2 NULL
    INC r8                        ; icrement counter_i
    JMP loop_i                    ; continue execution

initialise_loop_j:
    XOR r9, r9                    ; make sure j = 0 befome adding i + j
    MOV r9, r8                    ; so j = i to compare the second string
    XOR r12, r12                  ; create a counter for this loop to count s2[r12]
    JMP loop_j                    ; go to the loop

loop_j:
    CMP BYTE [rsi + r12], 0       ; if s2[count] == '\0' return
    JE return_ptr                 ; end of the function
    MOVZX r13, BYTE [rdi + r9]
    MOVZX r14, BYTE [rsi + r12]
    CMP r13, r14                  ; compare s1[i + j] and s2[count]
    JNE initialise_loop_i         ; icrement r8 and continue execution
    INC r12
    INC r9
    JMP loop_j                    ; continue the loop

initialise_loop_i:                ; this is to increment r8 counter if loop_i Jump to loop_j
    INC r8
    JMP loop_i

return_null:
    cmp byte [rsi], 0x0
    je return_ptr 
    XOR rax, rax                  ; set rax to NULL
    ret

return_ptr:
    LEA rax, [rdi + r8]           ; return the address of s1 + i
    ret
