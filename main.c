#define STANDARDBUF 32

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fil.h"

void printCar(int index, struct car *cars)
{
    printf("Index: %d\n", index);
    printf("%d. %s %s %s\n", index + 1, cars[index].type, cars[index].brand, cars[index].regNumber);
}

void printCars(int nCars, struct car *cars)
{
    for (int i = 0; i < nCars; i++)
    {
        printCar(i, cars);
    }
}

void addOwner(struct person *owner)
{
    printf("First name: \n");
    fflush(stdout);
    char firstName[MAXFIRSTNAMELEN+1];
    fgets(firstName, (MAXFIRSTNAMELEN), stdin);
    strtok(firstName, "\n");

    printf("Last name: \n");
    fflush(stdout);
    char lastName[MAXLASTNAMELEN+1];
    fgets(lastName, (MAXLASTNAMELEN), stdin);
    strtok(lastName, "\n");

    printf("Age: \n");
    fflush(stdout);
    char ageBuf[STANDARDBUF];
    fgets(ageBuf, (STANDARDBUF), stdin);
    int age = atoi(ageBuf);

    owner->firstName = firstName;
    owner->lastName = lastName;
    owner->age = age;
}

void addVehicle(struct car *cars, int nCars)
{
    printf("Type: \n");
    fflush(stdout);
    char type[MAXTYPELEN+1];
    fgets(type, (MAXTYPELEN), stdin);
    strtok(type, "\n");

    printf("Brand: \n");
    fflush(stdout);
    char brand[MAXBRANDLEN+1];
    fgets(brand, (MAXBRANDLEN), stdin);
    strtok(brand, "\n");

    printf("Reg number: \n");
    fflush(stdout);
    char regNumber[MAXREGNUMBERLEN+1];
    fgets(regNumber, (MAXREGNUMBERLEN), stdin);
    strtok(regNumber, "\n");

    struct person owner;
    addOwner(&owner);

    printf("Added vehicle: %s %s %s\n", type, brand, regNumber);

    cars[nCars] = (struct car){
        .type = type,
        .brand = brand,
        .regNumber = regNumber,
        .owner = owner};

    while (getchar() != '\n');
    fflush(stdout);
}

int main()
{
    char indexBuf[STANDARDBUF];
    struct car cars[MAXFILELEN];
    int nCars = 0;

    readRegister(&nCars);

    while (true)
    {
        printf("1. Add a vehicle\n");
        printf("2. Remove a vehicle\n");
        printf("3. Sort vehicles\n");
        printf("4. View a vehicle\n");
        printf("5. View all vehicles\n");
        printf("0. Exit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (nCars >= MAXFILELEN)
            {
                printf("Register is full, remove a vehicle first\n");
                break;
            }
            addVehicle(cars, nCars);
            nCars++;
            break;
        case 2:
            printf("Remove a vehicle\n");
            break;
        case 3:
            printf("Sort vehicles\n");
            break;
        case 4:
            printf("Select index: \n");
            fflush(stdout);
            fgets(indexBuf, (STANDARDBUF-1), stdin);
            int index = atoi(indexBuf);
            if (index < 0 || index >= nCars)
            {
                printf("Invalid index\n");
                break;
            }
            if (index > 0) {
                index--;
            }
            printCar(index, cars);
            break;
        case 5:
            printCars(nCars, cars);
            break;
        case 0:
            printf("Exit\n");
            return 0;
        default:
            printf("Invalid choice\n");
            while (getchar() != '\n');
            break;
        }
    }

    return 0;
}