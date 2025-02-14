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

// Estrutura para guardar as informações de uma imagem PGM
typedef struct {
    char format[3];             // Formato da imagem: "P2" (ASCII) ou "P5" (binário)
    int width, height;          // Largura e altura da imagem
    unsigned char maxval;       // Valor máximo de intensidade dos pixels de 0 a 255 (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
    unsigned char *pixels;      // Array que armazena os valores dos pixels (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
} PGMImage;

/**
 * @brief Lê um arquivo PGM e carrega os dados na estrutura PGMImage.
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

    // Lê o formato da imagem (P2 ou P5)
    if (fscanf(file, "%2s", image->format) != 1) {
        printf("Erro ao ler o tipo do PGM: %s\n", filepath);
        fclose(file);
        return -1;
    }

    // Verifica se o formato é válido (deve ser P2 ou P5)
    if (strcmp(image->format, "P2") && strcmp(image->format, "P5")) {
        printf("Não é um arquivo PGM válido (Esperado P2 ou P5)\n");
        fclose(file);
        return -1;
    }

    // Lê a largura, altura e valor máximo de intensidade (maxval)
    char line[MAX_LINE_LENGTH];
    int pixelIndex = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (line[0] == '#') continue; // Ignora linhas de comentário
        if (sscanf(line, "%d %d", &image->width, &image->height) == 2) break; // Lê largura e altura
    }

    // Lê o valor máximo de intensidade (maxval)
    fgets(line, MAX_LINE_LENGTH, file);
    sscanf(line, "%hhd", &image->maxval);

    // Aloca memória para armazenar os pixels da imagem
    int size = image->width * image->height;
    if ((image->pixels = allocMemUC(size)) == NULL) {
        printf("Memória insuficiente!\n");
        fclose(file);
        return -1;
    }

    // Lê os dados dos pixels, dependendo do formato (P2 ou P5)
    if (!strcmp(image->format, "P5")) {
        // Formato binário (P5): lê os pixels diretamente do arquivo
        fread(image->pixels, sizeof(unsigned char), size, file);
    } else if (!strcmp(image->format, "P2")) {
        // Formato ASCII (P2): lê os pixels como texto e converte para números
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
 * @brief Cria um arquivo PGM a partir dos dados da estrutura PGMImage.
 * 
 * @param filename Nome do arquivo a ser criado.
 * @param image Estrutura com os dados da imagem.
 * @return int Retorna 0 em caso de sucesso, ou 1 se houver erro.
 */
int makePGM(const char *filename, const PGMImage *image) {
    int size = image->width * image->height;
    FILE *file;
    if ((file = fopen(filename, "w+")) == NULL) {
        printf("Erro ao criar o arquivo");
        return 1;
    }

    // Escreve o cabeçalho do arquivo PGM (formato, largura, altura, maxval)
    fprintf(file, "%s\n", image->format);
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%hd\n", image->maxval);

    // Escreve os dados dos pixels, dependendo do formato (P2 ou P5)
    if (image->format[1] == '5') {
        // Formato binário (P5): escreve os pixels diretamente no arquivo
        fwrite(image->pixels, sizeof(unsigned char), size, file);
    } else if (image->format[1] == '2') {
        // Formato ASCII (P2): escreve os pixels como texto
        for (int k = 0; k < size; k++) {
            fprintf(file, "%hd", image->pixels[k]);
            if (!((k+1) % (image->width)) && k+1 != size) {
                fprintf(file, "\n"); // Quebra de linha a cada linha da imagem
            } else {
                fprintf(file, " "); // Espaço entre os pixels
            }
        }
    }
    fclose(file);
    return 0;
}

/**
 * @brief Alterna o formato da imagem entre P2 (ASCII) e P5 (binário).
 * 
 * @param image Estrutura da imagem que terá o formato alterado.
 */
void switchPGMType(PGMImage *image) {
    image->format[1] = (image->format[1] == '2') ? '5' : '2';
}

/**
 * @brief Gera um histograma da imagem, contando a frequência de cada valor de pixel.
 * 
 * @param image Estrutura da imagem a ser analisada.
 * @return int* Retorna um array com o histograma.
 */
int *getHistogram(PGMImage image) {
    int *histogram = allocMemInt(image.maxval + 1);
    for (int k = 0; k < image.height * image.width; k++) histogram[image.pixels[k]]++;
    return histogram;
}

/**
 * @brief Libera a memória alocada para os pixels da imagem.
 * 
 * @param image Estrutura da imagem que terá a memória liberada.
 */
void freePGM(PGMImage *image) {
    if (image->pixels != NULL) {
        free(image->pixels);
    }
}
