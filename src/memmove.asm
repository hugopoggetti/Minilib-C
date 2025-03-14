bits 64
section .text
global memmove

; 1. create a temporary array of rdx byte size
; 2. copy src into tmp to not verlap 
; 3. copy tmp into dest

memmove:
    test rdi, rdi
    je null
    test rsi, rsi
    je ret_dest
    test rdx, rdx
    je ret_dest
    XOR rcx, rcx                 ; initialise counter to zero
    MOV rax, rdi                 ; mov adress ptdr of dest to rax
    CMP rdi, rsi                 ; check if memory area are overlap
    JL cpy_forward               ; if ptr dest < src
    DEC rdx                      ; do n - 1 to cpy backward because index src[n] does not exist
    JMP cpy_backward             ; else cpy backward
cpy_forward:
    MOVZX r8, byte [rsi + rcx]   ; put content of src[count] in 64-bits r8
    MOV [rdi + rcx], r8b         ; put 8-bits r8 in dest[count]
    INC rcx                      ; increment count
    CMP rcx, rdx                 ; compare count to n
    JL cpy_forward               ; if count < n loop here again
    ret
cpy_backward:
    MOVZX r8, byte [rsi + rdx]   ; put content of src[size - count] in to 64-bits r8
    MOV [rdi + rdx], r8b         ; put content if 8-bits r8 into dest[size - count]
    DEC rdx                      ; decrement size to continue the copy
    CMP rdx, 0                   ; cmp n to 0
    JGE cpy_backward             ; if n >= 0 loop here again
    ret

null:
    xor rax, rax
    ret

ret_dest:
    mov rax, rdi
    ret
