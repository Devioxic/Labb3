#include <stdio.h>
#include <stdlib.h>
#include "fil.h"

void createRegisterifNotExisting() {
    FILE *file = fopen(FILENAME, "w");
    fclose(file);
}

struct car *readRegister(int *nCars) { //TODO free cars
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        createRegisterifNotExisting();
        file = fopen(FILENAME, "r");
    }

    struct car *cars = malloc(sizeof(struct car) * MAXFILELEN);
    
    *nCars = fread(cars, sizeof(struct car), MAXFILELEN, file);

    fclose(file);

    return cars;
}

void writeRegister(struct car *cars, int nCars) {
    FILE *file = fopen(FILENAME, "wb");

    fwrite(cars, sizeof(struct car), nCars, file);

    fclose(file);
}