global _main
extern _printf
default rel

; outputs 1 if parity is even, outputs 0 if parity is odd

section .text
_main:
mov al, [n]
mov rsi, 0
mov r9, 1
test al, al
cmovp rsi, r9
lea rdi, [format]
sub rsp, 8
call _printf
add rsp, 8
ret

section .data
n: db 0b01101001
format: db "%d", 0xA, 0