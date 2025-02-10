/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/* Aluno: Henrique Santos Dumont Saraiva                   ∗/
/∗ Matrícula: 2024.1045050154                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#include <stdio.h>
#include <stdlib.h>

unsigned char *allocMemUC(unsigned int qtd) {
    unsigned char *p = NULL;
    if (!(p = (unsigned char *) malloc(qtd * sizeof(unsigned char)))){
        puts("Memória insuficiente");
        exit(1);
    }
    return p;
}

float *allocMemFloat(unsigned int qtd) {
    float *p = NULL;
    if (!(p = (float *) malloc(qtd * sizeof(float)))){
        puts("Memória insuficiente");
        exit(1);
    }
    return p;
}

int checkDiffOnThreshold(float *v1, float *v2, int size, float threshold) {
    for (int i = 0; i < size; i++) {
        if (abs(v1[i]-v2[i]) > threshold) return 0; 
    }
    return 1;
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