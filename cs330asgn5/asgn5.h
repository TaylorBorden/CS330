#ifndef __asgn2__
#define __asgn2__

/* the two lines above check to ensure
we haven't already included this header*/



/* Counts the number of characters in a string array
      Does not count the null character at the end
   Takes a pointer to an array of chars as input
      Assumes the string is properly formatted with a null char at the end
   returns the size (an int)
*/
int sizeOfString(char *arr){
    int numOfChars = 0;             /* variable to hold number of chars in this string */
    int index = 0;                  /* not necessary, could just use numOfChars, but just making it obvious */
    while(*(arr+index) != '\0'){    /* loop through the array until null char */
        numOfChars++;               /* increase the count by 1 */
        index++;                    /* increment index to get ready for the next loop */
    }
    return numOfChars;
}

/* ========================================================================= */
/* your functions go here */
// Note: main() goes in the asgn2.c file








// integer to string function
char *itoa_cs330(int num)
{
    // If input is 0 print a " "
    if (num == 0)
    {
        char *str = (char *)malloc(1);
        str[0] = '\0';
        return str;
    }

    int len = 0;
    int temp = num;
    while (temp != 0) 

    {
        len++;
        temp /= 10;
    }

    // Check for a negative sign
    int sign = 1;
    if (num < 0)
    {
        sign = -1;
        len++;
    }
    
    // Allocate memory for the string based on the length of the number and +1 for the '/0'
    char *str = (char *)malloc(len + 1);
    str[len] = '\0';

    for (int i = len - 1; i >= 0; i--)
    {
         
        if (i == 0 && sign == -1)
        {
            str[0] = '-';
        }
        else
        {
            
            str[i] = abs(num % 10) + '0';
            num /= 10;
        }
    }
    // Return our output now as a string
    return str;
}

// String to Integer function
int atoi_cs330(char *str)
{
    int result = 0; // Intitialize resut to 0
    int sign = 1; // Initialize sign to positive 
    int i = 0; // Initialize our index variable

    // if the string is empty return a '0'
    if (str[0] == '\0')
    {
        return 0;
    }
    // Check for a negative sign
    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    
    else if (str[0] == '+')
    {
        i++;
    }
    // Create a loop through the string str characters and convert them to an integer
    while (str[i] != '\0')
    {
        // Check the range from 0 to 9
        if (str[i] >= '0' && str[i] <= '9')
        {
            // Convert the character to an integer and add it to the result
            result = result * 10 + (str[i] - '0');
        }
        else
        {
            return 0; // Error: If invalid character in string return 0
        }
        i++;
    }

    return sign * result; // Return the result with the appropriate sign
}



// nothing below this line
#endif