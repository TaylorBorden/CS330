# Define data section
.section .data
format_input: .string "%ld %ld"   # Input format string for scanf
format_output: .string "Results:\n1. A * 5 = %ld\n2. (A + B) - (A/B) = %ld\n3. (A - B) + (A * B) = %ld\n"   # Output format string for printf
A: .quad 0     # Storage for integer A
B: .quad 0     # Storage for integer B

# Define text section
.section .text
.globl main

# Function to compute A * 5
multiply_by_5:
    pushq %rbp        # Function prologue
    movq %rsp, %rbp

    movq A(%rip), %rax   # Load A into rax
    movq $5, %rbx        # Load 5 into rbx
    imulq %rbx, %rax     # Multiply A by 5

    popq %rbp        # Function epilogue
    ret

# Function to compute (A + B) - (A/B)
subtract_and_divide:
    pushq %rbp        # Function prologue
    movq %rsp, %rbp

    movq A(%rip), %rax   # Load A into rax
    movq B(%rip), %rbx   # Load B into rbx

    # Check if B is zero
    cmpq $0, %rbx
    je division_by_zero_error

    addq %rbx, %rax      # A + B
    xorq %rdx, %rdx      # Clear rdx for division
    cqto                 # Sign-extend rax into rdx:rax
    idivq %rbx           # Divide rdx:rax by B

    subq %rax, %rbx      # (A + B) - (A / B)

    popq %rbp        # Function epilogue
    ret

# Function to compute (A - B) + (A * B)
add_and_multiply:
    pushq %rbp        # Function prologue
    movq %rsp, %rbp

    movq A(%rip), %rax   # Load A into rax
    movq B(%rip), %rbx   # Load B into rbx

    subq %rbx, %rax      # A - B
    imulq %rbx, %rax     # Multiply (A - B) by B

    addq %rax, %rbx      # (A - B) + (A * B)

    popq %rbp        # Function epilogue
    ret

main:
    pushq %rbp        # Function prologue
    movq %rsp, %rbp

    # Prompt for A and B
    mov $format_input, %rdi   # Set format_input as the format string
    lea A(%rip), %rsi         # Load the address of A
    lea B(%rip), %rdx         # Load the address of B
    call scanf

    # Call the functions and store results
    call multiply_by_5
    movq %rax, A  # Update A with the result

    call subtract_and_divide
    movq %rbx, B  # Update B with the result

    call add_and_multiply
    movq %rax, A  # Update A with the result

    # Display results
    mov $format_output, %rdi   # Set format_output as the format string

    # Result 1
    movq A(%rip), %rsi
    call printf

    # Result 2
    movq B(%rip), %rsi
    call printf

    leave
    ret

division_by_zero_error:
    # Display division by zero error and exit
    mov $1, %edi
    lea format_output(%rip), %rsi
    call printf

    leave
    ret
