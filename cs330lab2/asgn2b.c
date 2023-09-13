#include <stdio.h>
#include <math.h>
#include "asgn2.h" 

int main() {
    // Declare variables
    int choice, n, attendance;
    float length, width, height, avg_exams, avg_hw;

    
    do {
        // For multiple problems I display a menu to the user and first ask for a choice.
        printf("Enter your choice:\n");
        printf("1. Cube of odd numbers\n");
        printf("2. Introduction to CS330\n");
        printf("3. Print HELLO\n");
        printf("4. Paint gallons\n");
        printf("5. Grader\n");
        printf("6. Exit\n");
        scanf("%d", &choice);

        // Use a switch statement to ask for user input for each problem.
        switch (choice) {
        case 1:
            
            printf("Enter a number: ");
            scanf("%d", &n);
            cubeOfOdd(n);
            break;

        case 2:
            printf("Enter a number: ");
            scanf("%d", &n);
            introToCS330(n);
            break;

        case 3:
            printf("Enter a number: ");
            scanf("%d", &n);
            printHELLO(n);
            break;

        case 4:
            printf("Enter the length, width, and height of the room (in feet) seperated by spaces: ");
            scanf("%f %f %f", &length, &width, &height);
            printf("You need %d gallon(s) of paint\n", paintGallons(length, width, height));
            break;

        case 5:
            printf("Enter the average exam score, average homework score, and attendance (separated by spaces): ");
            scanf("%f %f %d", &avg_exams, &avg_hw, &attendance);
            grader(avg_exams, avg_hw, attendance);
            break;

        case 6:
             // end of the loop
            printf("Goodbye!\n");
            break;

        default:
            // for choices that don't exist
            printf("Invalid choice\n");
        }
    } while (choice != 6); // Continue the loop until the user selects "6. Exit"

    return 0;
}
