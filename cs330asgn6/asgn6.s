.data
    promptA: .string "Enter value for A: "
    promptB: .string "Enter value for B: "
    result1: .string "Result 1: %d\n"
    result2: .string "Result 2: %d\n"
    result3: .string "Result 3: %d\n"

.text
.global main

# Function to compute A * 5
multiply_by_5:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    movl 8(%ebp), %eax   # Load A into eax
    movl $5, %ebx        # Load 5 into ebx
    imull %ebx, %eax     # Multiply A by 5

    popl %ebx
    popl %ebp
    ret

# Function to compute (A + B) - (A / B)
subtract_and_divide:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax   # Load A into eax
    movl 12(%ebp), %ebx  # Load B into ebx
    addl %ebx, %eax      # A + B
    xorl %edx, %edx      # Clear edx for division
    idivl %ebx            # Divide eax by B

    subl %eax, %ebx       # (A + B) - (A / B)

    popl %edi
    popl %esi
    popl %ebx
    popl %ebp
    ret

# Function to compute (A - B) + (A * B)
add_and_multiply:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax   # Load A into eax
    movl 12(%ebp), %ebx  # Load B into ebx
    subl %ebx, %eax      # A - B
    imull %ebx, %eax     # Multiply (A - B) by B

    addl %eax, %ebx       # (A - B) + (A * B)

    popl %edi
    popl %esi
    popl %ebx
    popl %ebp
    ret

main:
    pushl %ebp
    movl %esp, %ebp

    pushl $promptA
    call printf
    addl $4, %esp

    pushl $0    # Placeholder for scanf result
    pushl $a    # Address of A
    pushl $format
    call scanf
    addl $12, %esp

    pushl $promptB
    call printf
    addl $4, %esp

    pushl $0    # Placeholder for scanf result
    pushl $b    # Address of B
    pushl $format
    call scanf
    addl $12, %esp

    pushl b
    pushl a
    call multiply_by_5
    addl $8, %esp
    movl %eax, resultA

    pushl b
    pushl a
    call subtract_and_divide
    addl $8, %esp
    movl %eax, resultB

    pushl b
    pushl a
    call add_and_multiply
    addl $8, %esp
    movl %eax, resultC

    pushl resultC
    pushl $result3
    call printf
    addl $8, %esp

    pushl resultB
    pushl $result2
    call printf
    addl $8, %esp

    pushl resultA
    pushl $result1
    call printf
    addl $8, %esp

    movl $0, %eax   # Exit with status 0
    leave
    ret

.section .bss
a: .lcomm 4
b: .lcomm 4
format: .string "%d"
resultA: .int 0
resultB: .int 0
resultC: .int 0

