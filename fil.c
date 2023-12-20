#include <stdio.h>
#include <stdlib.h>
#include "fil.h"

void createRegisterifNotExisting() {
    FILE *file = fopen(FILENAME, "w");
    fclose(file);
}

int readRegister(struct car cars[]) {
    FILE *file = fopen(FILENAME, "r");

    int nCars = 0;

    if (file == NULL) {
        printf("File not found\n");
        printf("Trying to create file\n");
        createRegisterifNotExisting();
        file = fopen(FILENAME, "r");
        if (file == NULL) {
            printf("File could not be created\n");
            exit(1);
        }
        return 0;
    }

    while (fscanf(file, "%[^,],%[^,],%[^,], %[^,],%[^,],%d\n", cars[nCars].type, cars[nCars].brand, cars[nCars].regNumber, cars[nCars].owner.firstName, cars[nCars].owner.lastName, &cars[nCars].owner.age) != EOF) {
        printf("%s,%s,%s, %s,%s,%d\n", cars[nCars].type, cars[nCars].brand, cars[nCars].regNumber, cars[nCars].owner.firstName, cars[nCars].owner.lastName, cars[nCars].owner.age);
        nCars++;
    }
    fclose(file);

    return nCars;
}

void writeRegister(struct car cars[], int nCars) {
    FILE *file = fopen(FILENAME, "w");

    for (int i = 0; i < nCars; i++) {
        fprintf(file, "%s,%s,%s, %s,%s,%d\n", cars[i].type, cars[i].brand, cars[i].regNumber, cars[i].owner.firstName, cars[i].owner.lastName, cars[i].owner.age);
    }

    fclose(file);
}