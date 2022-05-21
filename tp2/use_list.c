#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
    /*Create a list*/
    list* l = list_new();

    /*populate a list*/
    for(int i = 1; i <= 10; i++)
        list_add_last(i, l);

    /*test add-first*/
    list_add_first(0, l);

    /*test get_first and get_last*/
    printf("First element: %d\nLast element: %d\n", 
        list_get_first(l), list_get_last(l));
    
    /*test remove*/
    list_print(l);
    list_remove_first(l);
    list_print(l);
    list_remove_last(l);
    list_print(l);

    return 0;
}