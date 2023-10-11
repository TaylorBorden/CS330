#include <stdio.h>
#include <stdlib.h>
#include "asgn5.h"



int main() {
    int num;
    char str[100];

    printf("Enter an integer: ");
    scanf("%d", &num);

    char* str_num = itoa_cs330(num);
    printf("The string value is: %s\n", str_num);
    free(str_num);

    printf("Enter a string: ");
    scanf("%s", str);

    int int_num = atoi_cs330(str);
    printf("The integer value is: %d\n", int_num);

    return 0;
}



