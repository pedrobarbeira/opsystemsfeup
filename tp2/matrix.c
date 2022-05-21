#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* implementation of the matrix API */
matrix* matrix_new(int n, int m) {
    matrix* u = (matrix*) malloc(sizeof(matrix));
    u->n = n;
    u->m = m;
    u->vals = (double*) malloc ((u->n * u->m) * sizeof(double));
return u;
}

matrix* matrix_new_random(int n, int m, double min, double max) {
    matrix* u = (matrix*) malloc(sizeof(matrix));
    u->n = n;
    u->m = m;
    u->vals = (double*) malloc ((u->n * u->m) * sizeof(double));
    
    int i, j;
    double range = max - min;
    double div = RAND_MAX / range;
    
    for(i = 0; i < u->n; i++)
        for(j = 0; j < u->m; j++)
            matrix_set(i, j, min + (rand() / div), u);
    return u;
}

void matrix_print(matrix* u) {
    for(int i = 0; i < u->n * u->m; i++){
        if(i > 0 && (i % u->n) == 0) printf("\n");
        printf("%f ", u->vals[i]);
    }
    printf("\n");
}

double matrix_get(int i, int j, matrix* u){
    return *(u->vals + i * u->m + j);
}

void matrix_set(int i, int j, double val, matrix* u){
    u->vals[i*] = val;
}

matrix* matrix_add(matrix* u, matrix* v){
    int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) + matrix_get(i, j, v), w);
    return w;
}

matrix* matrix_sub(matrix* u, matrix* v){
        int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) - matrix_get(i, j, v), w);
    return w;
}

matrix* matrix_mul(matrix* u, matrix* v){
    matrix* ret = matrix_new(u->m, v->n);
    double newVal = 0;
    for(int retRow = 0; retRow < ret->n; retRow++){
        for(int retCol=0; retCol<ret->m; retCol++){
            for(int i = 0; i < ret->n; i++){
                newVal += matrix_get(retRow, i, u) * matrix_get(i, retCol, v);
            }
            matrix_set(retRow, retCol, newVal, ret);
            newVal = 0;
        }
    }
    return ret;
}

matrix* matrix_trans(matrix* u){
    matrix* ret = matrix_new(u->m, u->n);
    for(int i = 0; i < ret->n; i++){
        for(int j = 0; j < ret->m; j++){
            ret->vals[i*j] = u->vals[j*i];
        }
    }
    return ret;
}