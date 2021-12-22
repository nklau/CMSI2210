global _main
extern _scanf
extern _printf
default rel

section .text
_main:
lea rdi, [input_format]
lea rsi, [num1]
push rdi ; -16
call _scanf

pop rdi ; -8
push rdx ; -16
lea rsi, [num2]
call _scanf

mov rdi, [num1]
mov rsi, [num2]

call _gcd
pop rdx ; -8
ret

_gcd:
loop:

mov rdx, 0
cmp rsi, rdx
je end
mov rax, rdi
mov r11, rsi
div r11
mov rdi, rsi
mov rsi, rdx
jmp loop

end:
mov rsi, rdi
lea rdi, [output_format]
push rsi
call _printf
pop rax
ret

section .bss
num1: resb 8
num2: resb 8

section .data
input_format: db "%d", 0
output_format: db "%d", 0xA, 0