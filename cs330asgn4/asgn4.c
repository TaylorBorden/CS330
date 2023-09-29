#include <stdio.h>
#include <stdlib.h>
#include "asgn4.h"


int main() {
    int choice, decimal;
    char* result;

    // Display the menu for conversion choices
    printf("Choose conversion:\n");
    printf("1. Decimal to Binary\n");
    printf("2. Binary to Decimal\n");
    printf("3. Decimal to Hexadecimal\n");
    printf("4. Hexadecimal to Decimal\n");
    printf("Enter your choice: ");

    // Read the user's choice
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // If the user chose Decimal to Binary conversion
            printf("Enter a decimal number: ");
            scanf("%d", &decimal);

            // Convert decimal to binary and store the result in 'result'
            result = convertDecToBin(decimal);

            // Display the binary result
            printf("Binary: %s\n", result);

            // Free the memory allocated for the binary result
            free(result);
            break;

        case 2:
            // If the user chose Binary to Decimal conversion
            printf("Enter a binary number (16 bits): ");
            char binaryInput[NUMBER_OF_BITS + 1];

            // Read the binary input as a string
            scanf("%16s", binaryInput);

            // Convert binary to decimal and store the result in 'decimal_array'
            int* decimal_array = convertBinToDec(binaryInput);

            // Display the decimal result
            printf("Decimal: %d\n", *decimal_array);

            // Free the memory allocated for the decimal result
            free(decimal_array);
            break;

        case 3:
            // If the user chose Decimal to Hexadecimal conversion
            printf("Enter a decimal number: ");
            scanf("%d", &decimal);

            // Convert decimal to hexadecimal and store the result in 'result'
            result = convertDecToHex(decimal);

            // Display the hexadecimal result
            printf("Hexadecimal: %s\n", result);

            // Free the memory allocated for the hexadecimal result
            free(result);
            break;

        case 4:
            // If the user chose Hexadecimal to Decimal conversion
            printf("Enter a hexadecimal number (up to 4 characters): ");
            char hexInput[NUMBER_OF_HEX_DIGITS + 1];

            // Read the hexadecimal input as a string
            scanf("%4s", hexInput);

            // Convert hexadecimal to decimal and store the result in 'decimal_array'
            int* decimal_array_hex = convertHexToDec(hexInput);

            // Display the decimal result
            printf("Decimal: %d\n", *decimal_array_hex);

            // Free the memory allocated for the decimal result
            free(decimal_array_hex);
            break;

        default:
            // If the user entered an invalid choice
            printf("Invalid choice.\n");
    }

    return 0;
}