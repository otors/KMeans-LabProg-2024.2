/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/* Aluno: Oto Ribeiro Serafim                              ∗/
/∗ Matrícula: 2024.1045050189                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/utils.h"

#define MAX_LINE_LENGTH 1024

// Struct to store PGM image data
typedef struct {
    char format[3];             // Format "P2" or "P5"
    int width, height;          // Width and Height of the image
    unsigned char maxval;       // From 0 to 255 (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
    unsigned char *pixels;      // Pixel data (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
} PGMImage;

/**
 * @brief Function to read a PGM file
 * 
 * @param filepath 
 * @param image 
 * @return int 
 */
int readPGM(const char *filepath, PGMImage *image) {
    FILE *file;
    if ((file = fopen(filepath, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo");
        return -1;
    }

    // Read the format (P2 or P5)
    if (fscanf(file, "%2s", image->format) != 1) {
        printf("Erro ao ler o tipo do PGM: %s\n", filepath);
        fclose(file);
        return -1;
    }

    // Validate the format
    if (strcmp(image->format, "P2") && strcmp(image->format, "P5")) {
        printf("Não é um arquivo PGM válido (Esperado P2 ou P5)\n");
        fclose(file);
        return -1;
    }

    // Read width, height, and maxval
    char line[MAX_LINE_LENGTH];
    int pixelIndex = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (line[0] == '#') continue; // Skip comments
        if (sscanf(line, "%d %d", &image->width, &image->height) == 2) break; // Read width and height
    }

    // Read maxval
    fgets(line, MAX_LINE_LENGTH, file);
    sscanf(line, "%hhd", &image->maxval);

    // Allocate memory for pixel data
    int size = image->width*image->height;
    if ((image->pixels = allocMemUC(size)) == NULL) {
        printf("Memória insuficiente!\n");
        fclose(file);
        return -1;
    }

    // Read pixel data
    if (!strcmp(image->format, "P5")) {
        // Binary format (P5)
        fread(image->pixels, sizeof(unsigned char), size, file);
    } else if (!strcmp(image->format, "P2")) {
        // ASCII format (P2)
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            char pixel[3];
            char ch;
            for (int k = 0, count = 0; ch != '\n'; k++) {
                ch = line[k];
                if (ch != ' ') {
                    pixel[count++] = ch;
                } else {
                    image->pixels[pixelIndex++] = (unsigned char) atoi(pixel);
                    count = 0;
                }
            }
        }
    }
    fclose(file);
    return 0;

}

/**
 * @brief Function to write a PGM file
 * 
 * @param filename 
 * @param image 
 * @return int 
 */
int makePGM(const char *filename, const PGMImage *image) {
    int size = image->width*image->height;
    FILE *file;
    if ((file = fopen(filename, "w+")) == NULL) {
        printf("Erro ao criar o arquivo");
        return 1;
    }

    fprintf(file, "%s\n", image->format);
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%hd\n", image->maxval);
    if (image->format[1] == '5') {
        fwrite(image->pixels, sizeof(unsigned char), size, file);
    } else if (image->format[1] == '2') {
        for (int k = 0; k < size; k++) {
            fprintf(file, "%hd", image->pixels[k]);
            if (!((k+1) % (image->width)) && k+1 != size) {
                fprintf(file, "\n");
            } else {
                fprintf(file, " ");
            }
        }
    }
    fclose(file);
    return 0;
}

/**
 * @brief Function to switch between PGM formats (P2 <-> P5)
 * 
 * @param image 
 */
void switchPGMType(PGMImage *image) {
    image->format[1] = (image->format[1] == '2') ? '5' : '2';
}

/**
 * @brief Returns an histogram of the image.
 * 
 * @param image 
 * @return int* 
 */
int *getHistogram(PGMImage image) {
    int *histogram = allocMemInt(image.maxval+1);
    for (int k = 0; k < image.height*image.width; k++) histogram[image.pixels[k]]++;
    return histogram;
}

/**
 * @brief Function to free memory allocated for PGMImage
 * 
 * @param image 
 */
void freePGM(PGMImage *image) {
    if (image->pixels != NULL) {
        free(image->pixels);
    }
}

