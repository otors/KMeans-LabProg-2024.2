#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Struct to store PGM image data
typedef struct {
    char format[3];             // Format "P2" or "P5"
    int width, height;          // Width and Height of the image
    unsigned char maxval;       // From 0 to 255 (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
    unsigned char *pixels;      // Pixel data (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
} PGMImage;

int readPGM(const char *filepath, PGMImage *image) {
    FILE *file;
    if ((file = fopen(filepath, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo");
        return -1;
    }

    if (fscanf(file, "%2s", image->format) != 1) {
        printf("Erro ao ler o tipo do PGM: %s\n", filepath);
        fclose(file);
        return -1;
    }

    if (strcmp(image->format, "P2") && strcmp(image->format, "P5")) {
        printf("Não é um arquivo PGM válido (Esperado P2 ou P5)\n");
        fclose(file);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int pixelIndex = 0;

    // Read the image dimensions and max pixel value
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Pula linhas de comnetários
        if (line[0] == '#') continue;

        // Lê 'width' e 'height' 
        if (sscanf(line, "%d %d", &image->width, &image->height) == 2) {
            break;
        } 
    }

    // Lê 'maxval'
    fgets(line, MAX_LINE_LENGTH, file);
    sscanf(line, "%hhd", &image->maxval);

    // Alocando a memória para a imagem
    if ((image->pixels = (unsigned char *) malloc((image->width)*(image->height) * sizeof(unsigned char))) == NULL) {
        printf("Memória insuficiente!\n");
        fclose(file);
        return -1;
    }

    if (!strcmp(image->format, "P5")) {
        fread(image->pixels, sizeof(unsigned char), (image->width)*(image->height), file);
    } else if (!strcmp(image->format, "P2")) {
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

void makePGM(const char *filename, const PGMImage *image) {
    FILE *file;
    if ((file = fopen(filename, "w+")) == NULL) {
        printf("Erro ao abrir/criar o arquivo");
        return;
    }

    fprintf(file, "%s\n", image->format);
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%hd\n", image->maxval);
    if (image->format[1] == '5') {
        fwrite(image->pixels, sizeof(unsigned char), (image->width)*(image->height), file);
    } else if (image->format[1] == '2') {
        for (int k = 0; k < (image->width)*(image->height); k++) {
            fprintf(file, "%hd", image->pixels[k]);
            if (!((k+1) % (image->width)) && k+1 != (image->width)*(image->height)) {
                fprintf(file, "\n");
            } else {
                fprintf(file, " ");
            }
        }
    }
    fclose(file);
}

/**
 * @brief Function to switch between PGMImage format field values, from P2 to P5, or from P5 to P2.
 * 
 * @param image Pointer to the PGMImage wanted to change
 */
void switchPGMType(PGMImage *image) {
    image->format[1] = (image->format[1] == '2') ? '5' : '2';
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

