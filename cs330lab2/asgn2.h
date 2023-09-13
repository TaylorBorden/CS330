#ifndef __asgn2__
#define __asgn2__

/* The two lines above check to ensure
   we haven't already included this header */

/* Declare function prototypes for user-defined functions */
void cubeOfOdd(int n);
void introToCS330(int n);
void printHELLO(int n);
int paintGallons(float length, float width, float height);
void grader(float avg_exams, float avg_hw, int attendance);

/* Note: main() goes in the asgn2.c file */




/* Function to print the cube of all odd integers less than n */
void cubeOfOdd(int n)
{
    int i;
    for (i = 1; i < n; i += 2)
    {
        printf("%d^3 = %d\n", i, i * i * i);
    }
}

/* Function to print a string depending on which number the user inputs */
void introToCS330(int n)
{
    if (n % 3 == 0 && n % 7 == 0)
    {
        printf("UAB CS 330\n");
    }
    else if (n % 3 == 0)
    {
        printf("CS\n");
    }
    else if (n % 7 == 0)
    {
        printf("UAB\n");
    }
    else if (n > 7 && n % 2 != 0)
    {
        int i, prime = 1;
        for (i = 3; i <= sqrt(n); i += 2)
        {
            if (n % i == 0)
            {
                prime = 0;
                break;
            }
        }
        if (prime)
        {
            printf("Go Blazers\n");
            return;
        }
    }
    printf("%d^3 = %d\n", n, n * n * n);
}





/* Function to print integers 0 through n, but the powers of 2 are replaced by the word "HELLO" */
void printHELLO(int n)
{
    int i;
    for (i = 0; i <= n; i++)
    {
        if ((i & (i - 1)) == 0 && i != 0)
        {
            printf("HELLO ");
        }
        else
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}




/* Function to calculate the amount of paint needed to cover a room and round up to the nearest gallon */
int paintGallons(float length, float width, float height)
{
    float area = (2 * length * height) + (2 * width * height) + (length * width);
    int gallons = ceil(area / 400);
    return gallons;
}






/* Function to determine if a student passes or fails based on their grades, homework, and attendance */
void grader(float avg_exams, float avg_hw, int attendance)
{
    if (attendance > 20 && avg_exams > 70 && avg_hw > 70 && (avg_exams > 85 || avg_hw > 85))
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
}

#endif