/**
 * -------------------------------------
 * @file  functions.c
 * Lab 2 Functions Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_three_integers(void) {
        char line[STRING_SMALL];
        int num1;
        int num2;
        int num3;
        int sum;

        printf("Enter three comma-seperated integers: ");
        while (fgets(line, sizeof(line), stdin)) {
            if (sscanf(line, "%d, %d, %d", &num1, &num2, &num3) == 3) {
                sum  = num1 + num2 + num3;
                break;
            }
            else {
                printf("The integers were not properly entered.\n");
                printf("Enter three comma-seperated integers:");
            }
        }
        return sum;


}