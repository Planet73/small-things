/* This is an implementation of 2d arrays using dynamic memory allocation and pointers only
   Just a personal idea*/

#include <stdio.h>
#include <stdlib.h>
int main() {
    int r, c;
    printf("Enter rows and columns: "); scanf("%d %d", &r, &c);
    int **rptr = malloc(r * sizeof(int *));
    for(int i = 0; i < r; ++i) *(rptr + i) = malloc(c * sizeof(int));
    printf("Enter the elements of the matrix: ");
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) scanf("%d", *(rptr + i) + j);
    }
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) printf("%d ", *(*(rptr + i) + j));
        printf("\n");
    }
    for(int i = 0; i < r; ++i) free(*(rptr + i));
    free(rptr);
    return 0;
}