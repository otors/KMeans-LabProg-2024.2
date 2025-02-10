/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/* Aluno: Oto Ribeiro Serafim                              ∗/
/∗ Matrícula: 2024.1045050189                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#ifndef _PGM_H
#define _PGM_H 1

typedef struct {
    char format[3];             // Format "P2" or "P5"
    int width, height;          // Width and Height of the image
    unsigned char maxval;       // From 0 to 255 (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
    unsigned char *pixels;      // Pixel data (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
} PGMImage;

int readPGM(const char *filepath, PGMImage *image);

int makePGM(const char *filename, PGMImage *image);

void switchPGMType(PGMImage *image);

void freePGM(PGMImage *image);

#endif