#define STANDARDBUF 32

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fil.h"

void printCar(int index, struct car *cars)
{
    printf("Type: %s, Brand: %s, RegNumber: %s \n", cars[index].type, cars[index].brand, cars[index].regNumber);
}

void printAllCars(struct car *cars, int nCars)
{
    printf("Number of cars: %d\n", nCars);
    if (nCars == 0)
    {
        printf("No cars in register\n");
        return;
    }
    for (int i = 0; i < nCars; i++)
    {
        printCar(i, cars);
    }
}

int createNewOwner(struct person *owner)
{
    printf("First name:\n");
    fflush(stdin);
    char firstName[MAXFIRSTNAMELEN];
    fgets(firstName, MAXFIRSTNAMELEN + 1, stdin);
    strtok(firstName, "\n");

    printf("Last name:\n");
    fflush(stdin);
    char lastName[MAXLASTNAMELEN];
    fgets(lastName, MAXLASTNAMELEN + 1, stdin);
    strtok(lastName, "\n");

    printf("Age:\n");
    fflush(stdin);
    char *endptr;
    char agebuff[STANDARDBUF];
    fgets(agebuff, STANDARDBUF + 1, stdin);
    long age = strtol(agebuff, &endptr, 10);
    if (endptr == agebuff)
    {
        printf("Invalid age\n");
        return 1;
    }

    strncpy(owner->firstName, firstName, (sizeof(owner->firstName) - 1));
    strncpy(owner->lastName, lastName, (sizeof(owner->lastName) - 1));

    owner->age = age;
    return 0;
}

void addCar(struct car *cars, int *nCars)
{
    printf("Type:\n");
    fflush(stdin);
    char type[MAXTYPELEN];
    fgets(type, MAXTYPELEN + 1, stdin);
    strtok(type, "\n");

    printf("Brand:\n");
    fflush(stdin);
    char brand[MAXBRANDLEN];
    fgets(brand, MAXBRANDLEN + 1, stdin);
    strtok(brand, "\n");

    printf("RegNumber:\n");
    fflush(stdin);
    char regNumber[MAXREGNUMBERLEN];
    fgets(regNumber, MAXREGNUMBERLEN + 1, stdin);
    strtok(regNumber, "\n");

    int rtrnmsg = createNewOwner(&cars[*nCars].owner);

    if (rtrnmsg == 0)
    {
        strncpy(cars[*nCars].type, type, (sizeof(cars[*nCars].type) - 1));
        strncpy(cars[*nCars].brand, brand, (sizeof(cars[*nCars].brand) - 1));
        strncpy(cars[*nCars].regNumber, regNumber, MAXREGNUMBERLEN);

        (*nCars)++;
    }
}

void removeCar(struct car *cars, int *nCars)
{
    printf("Select index: \n");
    fflush(stdin);
    char *endptr;
    char indexBuf[STANDARDBUF];
    fgets(indexBuf, (STANDARDBUF - 1), stdin);

    long index = strtol(indexBuf, &endptr, 10);

    if (endptr == indexBuf)
    {
        printf("Invalid index\n");
        return;
    }

    if (index < 0 || index >= *nCars)
    {
        printf("Invalid index\n");
        return;
    }
    if (index > 0)
    {
        index--;
    }
    for (int i = index; i < *nCars; i++)
    {
        cars[i] = cars[i + 1];
    }
    (*nCars)--;
}

void sortCars(struct car *cars, int nCars)
{
    for (int i = 0; i < nCars; i++)
    {
        for (int j = 0; j < nCars; j++)
        {
            if (strcmp(cars[i].brand, cars[j].brand) < 0)
            {
                struct car temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }
}

int main()
{
    char indexBuf[STANDARDBUF];
    struct car cars[MAXFILELEN];
    int nCars = 0;
    nCars = readRegister(cars);

    while (true)
    {
        printf("1. Add a vehicle\n");
        printf("2. Remove a vehicle\n");
        printf("3. Sort vehicles\n");
        printf("4. View a vehicle\n");
        printf("5. View all vehicles\n");
        printf("0. Exit\n");

        int choice = 10;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: //Borde vara konstanter
            if (nCars >= MAXFILELEN)
            {
                printf("Register is full, remove a vehicle first\n");
                break;
            }
            addCar(cars, &nCars);
            break;
        case 2:
            removeCar(cars, &nCars);
            break;
        case 3:
            sortCars(cars, nCars);
            break;
        case 4:
            printf("Select index: \n");
            fflush(stdin);
            fgets(indexBuf, (STANDARDBUF - 1), stdin);
            int index = atoi(indexBuf);
            if (index < 0 || index >= nCars)
            {
                printf("Invalid index\n");
                break;
            }
            if (index > 0)
            {
                index--;
            }
            printCar(index, cars);
            break;
        case 5:
            printAllCars(cars, nCars);
            break;
        case 0:
            writeRegister(cars, nCars);
            return 0;
        default:
            printf("Invalid choice\n");
            while (getchar() != '\n')
                ;
            break;
        }
    }

    return 0;
}