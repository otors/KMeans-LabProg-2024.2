/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/* Aluno: João Victor Pequeno Damasceno                    ∗/
/∗ Matrícula: 2024.1045050081                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

// C Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Project Headers
#include "lib/pgm.h"
#include "lib/kmeans.h"
#include "lib/utils.h"

int main(int argc, char const *argv[]) {
    // Main 



        /* Testing zone for pgm.c */
    // PGMImage image;

    // if (!readPGM("../database/dataset_Herlev_reduzido_PGM/carcinoma_in_situ/149143370-149143378-001.pgm", &image)) {

    //     makePGM("newImage-P5.pgm", &image);
    //     switchPGMType(&image);
    //     makePGM("newImage-P2.pgm", &image);

    //     freePGM(&image);
    // } else {
    //     printf("Failed to load PGM file.\n");
    // }

        /* Testing zone for kmeans.c */
    if (argc != 4) {
        printf("Uso: %s <imagemEntrada.pgm> <imagemSaida.pgm> <k>\n", argv[0]);
        exit(1);
    }

    PGMImage image;
    int k = atoi(argv[3]);

    // Lê a imagem de entrada
    if (readPGM(argv[1], &image) != 0) {
        fprintf(stderr, "Erro ao ler a imagem de entrada.\n");
        exit(1);
    }

    // Aplica o k-means à imagem
    int iter = kmeansClustering(&image, k, 30); // 30 iterações

    switchPGMType(&image);

    // Salva a imagem resultante
    makePGM(argv[2], &image);

    // Libera a memória alocada para os pixels
    freePGM(&image);

    printf("Sucesso com %d iterações!", iter);
    
    

    return 0;
}
