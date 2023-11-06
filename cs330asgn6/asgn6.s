.data
format_input: .string "%ld"           # Format string for input
format_output: .string "%ld\n"        # Format string for output with a newline
prompt_A: .string "Enter value for A: "  # Prompt for A input
prompt_B: .string "Enter value for B: "  # Prompt for B input
A: .quad 0                             # Variable A initialized with 0
B: .quad 0                             # Variable B initialized with 0

.text
.global main

# Function to compute A * 5
multiply_by_5:
    pushq %rbp
    movq %rsp, %rbp

    movq A(%rip), %rax   # Load A into rax
    movq $5, %rbx        # Load 5 into rbx
    imulq %rbx, %rax     # Multiply A by 5

    leave
    ret

# Function to compute (A + B) - (A/B)
subtract_and_divide:
    pushq %rbp
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

    leave
    ret

# Function to compute (A - B) + (A * B)
add_and_multiply:
    pushq %rbp
    movq %rsp, %rbp

    movq A(%rip), %rax   # Load A into rax
    movq B(%rip), %rbx   # Load B into rbx

    subq %rbx, %rax      # A - B
    imulq %rbx, %rax     # Multiply (A - B) by B

    addq %rax, %rbx      # (A - B) + (A * B)

    leave
    ret

main:
    pushq %rbp
    movq %rsp, %rbp

    # Prompt for A
    mov $0, %edi
    lea prompt_A(%rip), %rsi
    lea A(%rip), %rdi
    call scanf

    # Prompt for B
    mov $0, %edi
    lea prompt_B(%rip), %rsi
    lea B(%rip), %rdi
    call scanf

    # Call the functions and store results
    call multiply_by_5
    movq %rax, A(%rip)  # Update A with the result

    call subtract_and_divide
    movq %rbx, B(%rip)  # Update B with the result

    call add_and_multiply
    movq %rax, A(%rip)  # Update A with the result

    # Display results
    mov $0, %edi
    lea format_output(%rip), %rsi

    # Result 1
    movq A(%rip), %rdx
    call printf

    # Result 2
    movq B(%rip), %rdx
    call printf

    leave
    ret

division_by_zero_error:
    # Display division by zero error and exit
    mov $1, %edi
    lea format_output(%rip), %rsi
    mov $0, %rax  # Clear RAX
    call printf

    leave
    ret

    