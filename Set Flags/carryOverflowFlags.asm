global _main
extern _printf
extern _scanf
default rel

section .text
_main:
sub rsp, 8

lea rdi, [request]
call _printf

lea rdi, [format]
lea rsi, [num1]
call _scanf

lea rdi, [request]
call _printf

lea rdi, [format]
lea rsi, [num2]
call _scanf

mov r9w, [num1]
mov r10w, [num2]

add r9w, r10w
jc carrySet

cont:
xor r9, r9
xor r10, r10

mov r9w, [num1]
mov r10w, [num2]

add r9w, r10w
jno end

lea rdi, [overflow]
call _printf
jmp end

carrySet:
lea rdi, [carry]
call _printf
jmp cont

end:
add rsp, 8
ret


section .bss
num1: resb 8
num2: resb 8

section .data
request: db "enter a number ", 0
format: db "%x", 0
carry: db "carry flag set", 0xa, 0
overflow: db "overflow flag set", 0xa, 0