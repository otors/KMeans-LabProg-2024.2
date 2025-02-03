// C Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Project Headers
#include "kmeans.h"
#include "pgm.h"
#include "utils.h"

int main() {
    // Main 



    // Testing zone
    PGMImage image;

    if (!readPGM("../database/dataset_Herlev_reduzido_PGM/carcinoma_in_situ/149143370-149143378-001.pgm", &image)) {

        makePGM("newImage-P5.pgm", &image);
        switchPGMType(&image);
        makePGM("newImage-P2.pgm", &image);

        freePGM(&image);
    } else {
        printf("Failed to load PGM file.\n");
    }

    return 0;
}
