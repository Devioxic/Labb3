#ifndef FIL_H
#define FIL_H

#define FILENAME "bilRegister.txt"
#define MAXFILELEN 10
#define MAXTYPELEN 20
#define MAXBRANDLEN 20
#define MAXREGNUMBERLEN 6
#define MAXFIRSTNAMELEN 20
#define MAXLASTNAMELEN 20

struct person {
    char firstName[MAXFIRSTNAMELEN];
    char lastName[MAXLASTNAMELEN];
    int age;
};

struct car {
    char type[MAXTYPELEN];
    char brand[MAXBRANDLEN];
    char regNumber[MAXREGNUMBERLEN];
    struct person owner;
};

void createRegisterifNotExisting();

int readRegister(struct car *cars);

void writeRegister(struct car *cars, int nCars);

#endif