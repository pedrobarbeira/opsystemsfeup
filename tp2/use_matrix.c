#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
    /*Create four matrices*/
    matrix* a = matrix_new_random(3, 2, -5.2, 5.7);
    matrix* b = matrix_new_random(2, 3, -3, 5.6);
    matrix* c = matrix_new_random(3, 3, -5, 5);
    matrix* d = matrix_new_random(3, 3, -5, 5);

    /*Test print*/
    printf("Matrix A:\n");
    matrix_print(a);
    printf("\nMatrix B:\n");
    matrix_print(b);
    printf("\nMatrix C:\n");
    matrix_print(c);
    printf("\nMatrix D:\n");
    matrix_print(d);

    /*Test API*/
    matrix* testSum = matrix_add(c, d);
    matrix* testSub = matrix_sub(c, d);
    matrix* testTranspose = matrix_trans(a);
    matrix* testMul = matrix_mul(a, b);

    printf("\nMatrix Sum:\n");
    matrix_print(testSum);
    printf("\nMatrix Sub:\n");
    matrix_print(testSub);
    printf("\nMatrix Mul:\n");
    matrix_print(testMul);
    printf("\nMatrix Trans:\n");
    matrix_print(testTranspose);

    return 0;   
}