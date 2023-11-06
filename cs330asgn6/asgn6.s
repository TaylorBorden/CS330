.section .data
format_input: .string "%d %d"
format_output: .string "%ld\n"
prompt_A: .string "Enter value for A: "
prompt_B: .string "Enter value for B: "
A: .quad 0
B: .quad 0
rbp_save: .quad 0
rbx_save: .quad 0

.text
.global main


# Function to compute A * 5
multiply_by_5:
    pushq %rbp
    movq %rsp, %rbp
    push %rbx

    movq A(%rip), %rax   # Load A into rax
    movq $5, %rbx        # Load 5 into rbx
    imulq %rbx, %rax     # Multiply A by 5

    popq %rbx
    popq %rbp
    ret

# Function to compute (A + B) - (A/B)
subtract_and_divide:
    pushq %rbp
    movq %rsp, %rbp
    movq %rbp, rbp_save(%rip)
    movq %rbx, rbx_save(%rip)

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

    popq %rbx
    popq %rbp
    ret

# Function to compute (A - B) + (A * B)
add_and_multiply:
    pushq %rbp
    movq %rsp, %rbp
    movq %rbp, rbp_save(%rip)
    movq %rbx, rbx_save(%rip)

    movq A(%rip), %rax   # Load A into rax
    movq B(%rip), %rbx   # Load B into rbx

    subq %rbx, %rax      # A - B
    imulq %rbx, %rax     # Multiply (A - B) by B

    addq %rax, %rbx      # (A - B) + (A * B)

    popq %rbx
    popq %rbp
    ret

main:
    pushq %rbp
    movq %rsp, %rbp

    subq $16, %rsp  # Make room for A and B on the stack

    # Caller-saved registers
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx

    # Prompt for A and B
    mov $prompt_A, %rdi
    mov $A, %rsi
    mov $B, %rdx
    call scanf

    # Call the functions and store results
    call multiply_by_5
    movq %rax, A  # Update A with the result

    call subtract_and_divide
    movq %rbx, B  # Update B with the result

    call add_and_multiply
    movq %rax, A  # Update A with the result

    # Display results
    mov $format_output, %rdi

    # Result 1
    movq A(%rip), %rsi
    call printf

    # Result 2
    movq B(%rip), %rsi
    call printf

    # Caller-saved registers
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi

    leave
    ret

division_by_zero_error:
    # Display division by zero error and exit
    mov $1, %edi
    lea format_output(%rip), %rsi
    call printf

    leave
    ret
