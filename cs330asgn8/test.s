.data
    input_prompt:   .asciz "Enter the number of Fibonacci digits (0-40): "
    output_format:  .asciz "%lu\n"
    invalid_msg:    .asciz "Invalid input. Please enter a number between 0 and 40.\n"

.section .bss
    input_buffer:   .space  3           # buffer for user input (assuming a 3-digit input)

.text
    .globl main
main:
    # Print input prompt
    mov $1, %rax        # syscall: write
    mov $1, %rdi        # file descriptor: STDOUT
    mov $input_prompt, %rsi   # pointer to the input prompt
    mov $48, %rdx       # length of the input prompt
    syscall

    # Read user input
    mov $0, %rax        # syscall: read
    mov $0, %rdi        # file descriptor: STDIN
    lea input_buffer, %rsi  # pointer to the input buffer
    mov $3, %rdx        # length of the input buffer (assuming a 3-digit input)
    syscall

    # Convert the input to an integer
    mov $0, %rax        # clear RAX register
    mov $10, %rbx       # set base 10
convert_loop:
    movb (%rsi), %cl   # load the next byte of input
    cmp $0xA, %cl       # check if it is a newline character
    je  convert_done    # if yes, jump to the end
    sub $'0', %cl       # convert ASCII to integer
    imul %rbx, %rax     # multiply current result by 10
    add %rcx, %rax      # add the new digit
    inc %rsi            # move to the next character
    jmp convert_loop    # repeat the process
convert_done:

    # Check if the input is within the valid range
    cmp $40, %rax
    ja  invalid_input

    # Calculate and print Fibonacci sequence
    mov $0, %rdi        # fib(i-1)
    mov $1, %rsi        # fib(i)
    mov %rax, %rdx      # n (user input)
fibonacci_loop:
    mov %rsi, %rdi      # update fib(i-1)
    mov %rdx, %rsi      # fib(i) -> fib(i-1)
    add %rdi, %rsi      # fib(i) + fib(i-1) -> fib(i)

    # Print the current Fibonacci number
    mov $1, %rax        # syscall: write
    mov $1, %rdi        # file descriptor: STDOUT
    mov %rsi, %rdx      # fib(i) as the argument for syscall
    mov $output_format, %rsi  # pointer to the output format
    mov $20, %rdx       # maximum length of the output (adjust as needed)
    syscall

    cmp %rax, %rdx      # compare with the user input
    jl  fibonacci_loop  # if less, repeat the loop

    # Exit the program
    mov $60, %rax       # syscall: exit
    xor %rdi, %rdi      # exit code 0
    syscall

invalid_input:
    # Print an error message for invalid input
    mov $1, %rax        # syscall: write
    mov $1, %rdi        # file descriptor: STDOUT
    mov $invalid_msg, %rsi   # pointer to the invalid input message
    mov $40, %rdx       # maximum length of the message
    syscall

    # Exit the program
    mov $60, %rax       # syscall: exit
    mov $1, %rdi        # exit code 1
    syscall
