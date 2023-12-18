#ifndef FIL_H
#define FIL_H

#define FILENAME "bilRegister.bin"
#define MAXFILELEN 10
#define MAXTYPELEN 20
#define MAXBRANDLEN 20
#define MAXREGNUMBERLEN 6
#define MAXFIRSTNAMELEN 20
#define MAXLASTNAMELEN 20

struct person {
    char *firstName;
    char *lastName;
    int age;
};

struct car {
    char *type;
    char *brand;
    char *regNumber;
    struct person owner;
};

void createRegisterifNotExisting();

struct car *readRegister(int *nCars);

void writeRegister(struct car *cars, int nCars);

#endif