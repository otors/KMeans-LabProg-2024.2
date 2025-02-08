#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char *allocMemUC(unsigned int qtd) {
    unsigned char *p = NULL;
    if (!(p = (unsigned char *) malloc(qtd * sizeof(unsigned char)))){
        puts("Memória insuficiente");
        exit(1);
    }
    return p;
}

void printArrayUnsignedChar(unsigned char *arr, int size) {
    for (int k = 0; k < size; k++) {
        printf("[");
        (k = size-1) ? printf("%d]\n", *(arr+k)): printf("%d, ", *(arr+k));
    }
}

void printMatrixUnsignedChar(unsigned char *pm, int rows, int cols) {
    for (int k = 0; k < (rows*cols); k++) {
        if (!(k%cols)) printf("[");
        !((k+1)%cols) ? printf("%hd]\n", *(pm+k)): printf("%hd, ", *(pm+k));
    }
}