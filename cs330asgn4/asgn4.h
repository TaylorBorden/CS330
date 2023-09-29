#ifndef __asgn4__
#define __asgn4__
/* the two lines above check to ensure
we haven't already included this header*/

/* any needed include statements can go here */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>         /* for malloc() */


/* some helper define statements */
#define NUMBER_OF_BITS 16          /* since we're using 16 bit binary numbers */
#define NUMBER_OF_HEX_DIGITS 4     /* 16 bit numbers are 2 bytes, or 4 hex digits */


/* helper function, prints a 16 bit binary number in a reasonably nice format
Takes an integer array, where each element represents one binary bit
Returns nothing, but as a side-effect it prints the number
*/
void printMyBinaryNum(int *myNumArray){
    /* loop through the number, one element (bit) at a time */
    for(int i = 0; i < NUMBER_OF_BITS; i++){
        /* lets print a space before every 4th digit (except the first, i==0), for readability */
        if(i % 4 == 0 && i != 0) {
            /* retrieve this element and print it */            
            printf(" %d", *(myNumArray + i));
        } else {          
            /* else, this is not a 4th digit, just print it with no space */ 
            printf("%d", *(myNumArray + i));
        }
    }  // end for-i loop
    printf("\n");      /* and a newline when we're done, because it's kind to the reader */
}  // end printMyBinaryNum()



/* helper function, prints a 4 bit hex number 
Takes an integer array, where each element represents one hex digit
Returns nothing, but as a side-effect it prints the number
*/
void printMyHexNum(int *myNumArray){
    /* start by printing a sign to inform the reader that what follows is a hex number */
    printf("0x");
    /* loop through the number, one element (digit) at a time */
    for(int i = 0; i < NUMBER_OF_HEX_DIGITS; i++){
        /* print it out, %X is the conversion specifier for hex, in captital letters */
        printf("%X", *(myNumArray + i));
    }
    printf("\n");       /* and a newline when we're done, again because it's kind
    to poor TAs who have to look at thousands of lines of code, and too many
    output lines to count
    // end soap-box
    */
}  // end printMyHexNum()



/* Helper function to reverse an array 
Takes two arguments:
    an int size:  the size of the array, or number of elements
    an int pointer: the array
Returns a int pointer to the reverse array
Note: the return array is malloc'd and it is expected the user will free() the memory
    when no longer required
*/
int* reverseMyArrayPlease(int size, int *myArray){
    /* allocate memory, one int for each element, size*4 bytes */
    int *reversedArray = malloc( size * sizeof(int));
    /* loop through the array, extract one element, place it in the new array */  
    for(int i = 0; i < size; i++){
        /* -1 since the end of the array is at (size-1),
         -i since we want to reverse the array */
        *(reversedArray + (size - 1) - i) = *(myArray + i);
    }
    return reversedArray;
}  // end reverseMyArrayPlease()




/* ========================================================================= */
/* ~~~~~~~~~~~~~~~~~~~~~ your functions go here ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Note: main() goes in the asgn4.c file                                     */


char* convertDecToBin(int decimal) {
    char* binary_array = (char*)malloc(NUMBER_OF_BITS + 1); // +1 for null terminator
    if (binary_array == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = NUMBER_OF_BITS - 1; i >= 0; i--) {
        binary_array[i] = (decimal & 1) ? '1' : '0';
        decimal >>= 1;
    }

    binary_array[NUMBER_OF_BITS] = '\0';
    return binary_array;
}

int* convertBinToDec(const char* binary) {
    int* decimal_array = (int*)malloc(sizeof(int));
    if (decimal_array == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    *decimal_array = 0;
    for (int i = 0; i < NUMBER_OF_BITS; i++) {
        *decimal_array <<= 1;
        *decimal_array |= (binary[i] == '1') ? 1 : 0;
    }

    return decimal_array;
}

char* convertDecToHex(int decimal) {
    char* hex_array = (char*)malloc(NUMBER_OF_HEX_DIGITS + 1); // +1 for null terminator
    if (hex_array == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    snprintf(hex_array, NUMBER_OF_HEX_DIGITS + 1, "%04X", decimal);
    return hex_array;
}

int* convertHexToDec(const char* hex) {
    int* decimal_array = (int*)malloc(sizeof(int));
    if (decimal_array == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    sscanf(hex, "%X", decimal_array);
    return decimal_array;
}













#endif