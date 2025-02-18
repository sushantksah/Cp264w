/*
--------------------------------------------------
Project: a2q3
File:    matrix.c
Author:  Sushant Sah
Version: 2025-01-17
--------------------------------------------------
*/
#include <stdio.h>
#include <math.h>

/*
 * Compute and return the norm of vector v, namely, the square root of the sum of
 * squares of elements of v. 
 * 
 * @param v - the address of first the vector array. 
 * @param n - the length of vector v.
 * @return - the norm of vector v. 
 * 
*/
float norm(float *v, int n){
    float count = 0; 
    float ans = 0;
    for(int i = 0; i < n; i++){
        count += (v[i] * v[i]);
    }
    ans = sqrt(count);

    return ans; 
}

/*
 * Compute and return the dot product of vectors v1[n] and v2[n], namely the sum of product of corresponding elements of v1 and v2. 
 *  
 * @param v1 - the address of the first vector array.
 * @param v2 - the address of the second vector array.
 * @param n - the length of vector v1 and v2.
 * @return -  the value of dot product of v1 and v2.
*/
float dot_product(float *v1, float *v2, int n){
    float count = 0;

    for(int i = 0; i < n; i++){
        count += v1[i] * v2[i];
    }
    return count; 
}

/*
 * Compute the multiplication of matrix and vector. 
 * @param m - the address of the first matrix array.
 * @param v - the address of the vector array.
 * @param vout - the address of the output vector array.
 * @param n - the length of vector v.
*/
void matrix_multiply_vector(float *m, float *v, float *vout, int n){
    int i, j; 

    for(i = 0; i < n; i++){
        vout[i] = 0;
        for(j = 0; j < n; j++){
            // the i * n + j part is done to access an element at row i 
            // column j.
            // each row has n elements, to reach the start of row i, 
            // you have to skip the first i rows, which is i * n.
            // then once at the row, to get to the column position and move 
            // j steps to the right to get to column j. 
            vout[i] += m[i * n + j] * v[j];
        }
    }
}

/*
 * Compute the multiplication of two n by matrices. 
 * @param m1 - the address of the first matrix array.
 * @param m2 - the address of the second matrix array.
 * @param m3 - the address of the output matrix array.
 * @param n - the row and colum size of m1 and m2.
*/
void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n){
    float s = 0;
    int i,j,k;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            s = 0;
            for(k = 0; k < n; k++){
                s += (m1[i * n + k] * m2[k * n + j]);
            }
            *(m3 + i * n + j) = s;
        }
    }
}