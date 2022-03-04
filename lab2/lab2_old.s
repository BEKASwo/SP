.data

print_format:
    .string "Count: %d\n"

array:
    .byte 238, 42, 138, 168, 4, 85, 219, 137, 182, 15, 65, 99
array_end:



.text
.global main
.type main, function


main:
    movb $0x22, %dl         /* маска */

    movl $0, %ecx           /* счетчик значений */
    movl $array, %ebx       /* адрес текущего элемента массива */
    movb (%ebx), %al       /* значение текущего элемента массива */
    
    jmp ch_bound


/* проверка маски */
loop_start:    
    not %al
    and %dl, %al
    cmpb %dl, %al
    jne less

    inc %ecx

/* переход к след. эл. массива */
less:
    addl $1, %ebx
    movb (%ebx), %al

ch_bound:
    cmpl $array_end, %ebx
    jne loop_start

    push %ecx
    push $print_format
    call printf
    addl $8, %esp


    
    movl $1, %eax
    movl $0, %ebx
    int $0x80
    


