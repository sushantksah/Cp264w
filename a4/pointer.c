#include <stdio.h>
// Memory Address of the Array will always point to the first 
// value of the array

int main(){ 
    int numbers[5] = {1,3,5,7,9};

    for(int i = 0; i < 5; i++){
        printf("%d = %p\n", numbers[i], &numbers[i]);
    }

    printf("Array Address: %p", numbers + 1);
}