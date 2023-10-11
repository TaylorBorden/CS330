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



// Function to convert an integer to a string
char *itoa_cs330(int num)
{
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

    int sign = 1;
    if (num < 0)
    {
        sign = -1;
        len++;
    }

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

    return str;
}

// Function to convert a string to an integer
int atoi_cs330(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '\0')
    {
        return 0;
    }

    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[0] == '+')
    {
        i++;
    }

    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = result * 10 + (str[i] - '0');
        }
        else
        {
            return 0; // Error: Invalid character in the string
        }
        i++;
    }

    return sign * result;
}



// nothing below this line
#endif