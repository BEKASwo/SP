.data

print_format:
    .string "Count: "
    .set len_print_format, . - print_format - 1

text_out:
    .space 10, 0
text_out_len:
    .byte 0


array:

    .byte 238, 42, 138, 168, 4, 85, 219, 137, 182, 15, 65, 99
    /*
    .byte 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133, 133
    */
array_end:


.text
.globl _start

/* Вывод строки */
/* ecx - источник строки */
/* edx - длинна */
print_string:
    pushl %eax
    pushl %ebx

    movl $4, %eax
    movl $1, %ebx
    int $0x80

    popl %ebx
    popl %eax

    ret


/* Перевод числа в строку */
/* eax - число */
/* ebx - строка*/
/* return:*/
/* ecx - длинна */
num_to_str:
    pushl %esi
    pushl %ebx
    pushl %eax

    movl %ebx, %esi

    xorl %ecx, %ecx
    movl $10, %ebx

    /* Размещение по одному десятичному числу в стэк */
    loop_div:
        xorl %edx, %edx
        divl %ebx
        pushl %edx
        incl %ecx

        cmpl $0, %eax
        jne loop_div

    movl %ecx, %eax

    /* Вытаскивание из стека по одному и преобразование в символ */
    p_n:
        popl %edx
        addb $'0', %dl
        movb %dl, (%esi)

        addl $1, %esi

        loop p_n

    movb $'\n', (%esi)
    addl $1, %eax

    movl %eax, %ecx

    popl %eax
    popl %ebx
    popl %esi

    ret



_start:
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

    pushl %ecx

    movl $len_print_format, %edx
    movl $print_format, %ecx
    call print_string

    popl %ecx
    movl %ecx, %eax
    movl $text_out, %ebx
    call num_to_str

    movl %ecx, %edx
    movl $text_out, %ecx
    call print_string
    
    movl $1, %eax
    movl $0, %ebx
    int $0x80
    






