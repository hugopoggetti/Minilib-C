bits 64
section .text
global strchr

strchr:
    xor r8, r8                   ; initialise count to zero

loop:
    MOVZX r9, byte [rdi + r8]    ; mov byte in r9 to compare later
    CMP r9, rsi                  ; compare s[count] == c
    JE return                    ; if we found the first c return
    CMP byte [rdi + r8], 0x00       ; if s[count] == '\0' return NULL
    JE return_null               ; NULL
    INC r8                       ; increment register
    JMP loop                     ; loop again if we don't find anything

return:
    lea rax, [rdi + r8]          ; use of lea to return an address
                                 ; lea return the begining of an address here -> string + count
    ret

return_null:
    xor rax, rax                ; rax = NULL
    ret
