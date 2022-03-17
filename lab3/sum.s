.text
    .global sum
    .type sum, @function

sum:
    push %rbx
    push %rcx
    xorq %rbx, %rbx
    movq %rsi, %rcx

sum_loop:
    movl (%rdi), %eax
    mull %eax
    addl %eax, %ebx

    addq $4, %rdi

    loop sum_loop

    movq %rbx, %rax
    pop %rcx
    pop %rbx

    ret


