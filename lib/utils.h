#ifndef UTILS_H
#define UTILS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char *allocMemUC(unsigned int qtd);

void printArrayUnsignedChar(unsigned char *arr, int size);

void printMatrixUnsignedChar(unsigned char *pm, int rows, int cols);

#endif