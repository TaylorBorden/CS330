#include <stdio.h>
#include <stdlib.h>
#include "asgn5.h"


// the main function
int main() {
    int num;
    char str[100];
    // enter a number
    printf("Enter an integer: ");
    scanf("%d", &num);
    // Convert the interger to a string
    char* str_num = itoa_cs330(num);
    printf("The string value is: %s\n", str_num);
    free(str_num); // Free the dynamically allocated memory
    // enter a string
    printf("Enter a string: ");
    scanf("%s", str);
    // Convert the string to an integer 
    int int_num = atoi_cs330(str);
    printf("The integer value is: %d\n", int_num);

    return 0;
}



