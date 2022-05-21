#include <stdio.h>
int* get_int() {
	int i = 2;
	return &i;
}

int main() {
	int* p = get_int();
	printf("integer = %d\n", *p);
	return 0;
}

//In this case running the problem generates a segfault error. This means
//there was a memory access violation - the memory was corrupted or
//incorrectly accessed. This usually happens when a variable tries to access
//a memory segments that's outside of  the segment where it resides

//The error occurs in the print function. The program attempts to print a 
//reference to a local variable that, by the time the print request is sent,
//is no longer defined in the system. In good pointer we allocate memory
//to this variable, making it valid even after function termination