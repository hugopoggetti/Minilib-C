bits 64
section .text
global rindex

rindex:
    xor r8, r8                   ; initialise count to zero
    lea rax, 0x00                ; init rax to null

loop:
    MOVZX r9, byte [rdi + r8]    ; mov byte in r9 to compare later
    CMP r9, rsi                  ; compare s[count] == c
    JE add_to_rax                ; if we found the c mov the current address to rax
    JMP continue

add_to_rax:
    lea rax, [rdi + r8]          ; use of lea to mov an address  
    JMP continue

continue:
    CMP byte [rdi + r8], 0x00    ; if s[count] == '\0' return NULL
    JE end                       ; return last elem find or null if we didn't find any pattern
    INC r8                       ; increment register
    JMP loop                     ; loop again if we don't find anything

end:
    ret

