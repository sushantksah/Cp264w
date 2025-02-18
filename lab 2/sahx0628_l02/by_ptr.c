/**
 * -------------------------------------
 * @file  by_ptr.c
 * Lab 2 Pointer Functions Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "by_ptr.h"

/**
 * Populates values with consecutive integers in the range [1 to size].
 * Uses pointer arithmetic.
 *
 * @param values - array of int
 * @param size - size of values
 */
void fill_values_by_ptr(int *values, int size){
    for(int i = 0; i < size; i++){
        *(values + i) = i + 1;
    }
}

/**
 * Populates squares with the squares of the corresponding integers in values.
 * Uses pointer arithmetic.
 *
 * @param values - array of int
 * @param squares - array of int, each a square of corresponding int in values
 * @param size - size of values and squares
 */
void fill_squares_by_ptr(int *values, long int *squares, int size){
    int i;

    for(i = 0; i < size; i++){
        // * defrerences it and bc of pointer arthimatic the + i part 
        // iterates through the pointer so *(squares + i) is just 
        // squares[i]
        *(squares + i) = *(values + i) * *(values + i);
    }
}

/**
 * Prints the contents of values and squares in two columns.
 * Uses pointer arithmetic.
 *
 * @param values - array of int
 * @param squares - array of int, each a square of corresponding int in values
 * @param size - size of values and squares
 */
void print_by_ptr(int *values, long int *squares, int size){
    int i;

    printf("Value    Square\n");
    printf("-----  ----------\n");

    for(i = 0; i < size; i++){
        *(squares + i) = *(values + i) * *(values + i);
    }

    for(i = 0; i < size; i++){
        printf("%d\t%ld\n", *(values + i), *(squares + i));
    }
}