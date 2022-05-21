#include "vector.h"

vector* vector_new(double newX, double newY, double newZ){
    vector* toReturn = malloc(sizeof(vector));
    toReturn->x = newX;
    toReturn->y = newY;
    toReturn->z = newZ;
    return toReturn;
}

vector* vector_add(vector* v1, vector* v2){
    vector* toReturn = malloc(sizeof(vector));  
    toReturn->x = v1->x + v2->x;
    toReturn->y = v1->y + v2->y;
    toReturn->z = v1->z + v2->z;
    return toReturn;
}

vector* vector_sub(vector* v1, vector* v2){
    vector* toReturn = malloc(sizeof(vector));  
    toReturn->x = v1->x - v2->x;
    toReturn->y = v1->y - v2->y;
    toReturn->z = v1->z - v2->z;
    return toReturn;
}

vector* vector_scale(double a, vector* v){
    vector* toReturn = malloc(sizeof(vector));  
    toReturn->x = a * v->x;
    toReturn->y = a * v->y;
    toReturn->z = a * v->z;
    return toReturn;
}

vector* vector_vprod(vector*v1, vector* v2){
    vector* toReturn = malloc(sizeof(vector));
    toReturn->x = v1->y*v2->z - v1->z*v2->y;
    toReturn->y = v1->z*v2->x - v1->x*v2->z;
    toReturn->z = v1->x*v2->y - v1->y*v2->x;
    return toReturn;
}

double vector_sprod(vector* v1, vector* v2){
    return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

double vector_mod(vector* v){
    return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}