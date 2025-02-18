/**
 * -------------------------------------
 * @file  by_index.c
 * Lab 2 Index Functions Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "by_index.h"


/**
 * Populates values with consecutive integers in the range [1 to size].
 * Uses array indexing.
 *
 * @param values - array of int
 * @param size - size of values
 */
void fill_values_by_index(int values[], int size){
    for(int i = 0; i < size; i++){
        values[i] = i + 1;
    }
}

/**
 * Populates squares with the squares of the corresponding integers in values.
 * Uses array indexing.
 *
 * @param values - array of int
 * @param squares - array of int, each a square of corresponding int in values
 * @param size - size of values and squares
 */
void fill_squares_by_index(int values[], long int squares[], int size){
    int i;

    for(i = 0; i < size; i++){
        squares[i] = values[i] * values[i];
    }
}

/**
 * Prints the contents of values and squares in two columns.
 * Uses array indexing.
 *
 * @param values - array of int
 * @param squares - array of int, each a square of corresponding int in values
 * @param size - size of values
 */
void print_by_index(int values[], long int squares[], int size){
    int i,j;
    printf("Value   Square\n");
    printf("----    ----------\n");
    
    for(i = 0; i < size; i++){
        squares[i] = values[i] * values[i];
    }

    for(j = 0; j < size; j++){
        // %d - tells printf that it expects an integer argument and to return decimal
        // \t - adds a horizontal tab space between two valus printed by printf
        // %ld - format specifies for printing a long int value 
        // \n - new line
        printf("%d\t%ld\n", values[j],squares[j]);
    }
}

