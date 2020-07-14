//
// Created by Alex Lopez on 19/06/2020.
//

#include "../game.h"
#include "interface.h"

void showMainMenu() {
    printf("\n");
    printf("     1. Configurar coche\n");
    printf("     2. Carrera\n");
    printf("     3. Ver clasificatoria\n");
    printf("     4. Guardar temporada\n");
    printf("\nQue opcion quieres ejecutar? ");
}

int readOption(int * option) {

    fflush(stdin);

    // Get user option
    char userInput[MAX_CHAR];
    scanf("%s", (char *) &userInput);

    // check exit case
    if (strcmp(userInput, "exit") == 0) {
        *option = -1;
        return 1;

    } else { // check if its number
        // TODO: Loop for more digits, HARDCODED for just one
        if (strlen(userInput) == 1) {
            if (isdigit(userInput[0])) {
                *option = atoi(userInput);
                return 1;
            }
        }
    }

    printf("\nError. Opcion no valida.\n");
    return 0;
}

int switchOption(int * option, Racer * racer, Championship * championship, Player * player) {

    switch (*option) {

        case -1:
            freeMemory(option, racer, championship);
            printf("\nHasta pronto!\n");
            return 1;

        case MENU_OPTION_1:
            configureCar(racer, championship, player);
            return 0;

        case MENU_OPTION_2:
            startRace(championship, player);
            return 0;

        case MENU_OPTION_3:

            return 0;

        case MENU_OPTION_4:

            return 0;

        default:
            printf("\nError. Opcion no valida.\n");
            return 0;
    }
}

int racerData(Racer * racer) {

    char userInput[MAX_CHAR];
    bool correctInput = false;

    // Name
    while (!correctInput) {
        fflush(stdin);
        printf("\nNombre del piloto? ");
        scanf("%s", (char *) &userInput);
        if (strlen(userInput) > 0 && strlen(userInput) <= MAX_CHAR) {
            strcpy((*racer).name, userInput);
            correctInput = true;
        } else {
            printf("\nError, el tamaño maximo es de 25 caracteres\n");
        }
    }

    correctInput = false;

    // Team name
    while (!correctInput) {
        fflush(stdin);
        printf("\nNombre de la escuderia? ");
        scanf("%s", (char *) &userInput);
        if (strlen(userInput) > 0 && strlen(userInput) <= MAX_CHAR) {
            strcpy((*racer).team, userInput);
            correctInput = true;
        } else {
            printf("\nError, el tamaño maximo es de 25 caracteres\n");
        }
    }

    correctInput = false;

    // Dorsal
    while (!correctInput) {
        int num;
        char term;
        fflush(stdin);
        printf("\nDorsal? ");
        int totalScanf = scanf("%d%c", &num, &term);
        if(totalScanf != 2 || term != '\n') { // check if its number
            printf("\nError, el dorsal tiene que ser un entero entre 1 y 99\n");
        } else {
            if (num >= 1 && num <= 99) {
                (*racer).dorsal = num;
                correctInput = true;
            } else {
                printf("\nError, el dorsal tiene que ser un entero entre 1 y 99\n");
            }

        }
    }

    correctInput = false;

    // Reflexes
    while (!correctInput) {
        int num;
        char term;
        fflush(stdin);
        printf("\nReflejos? ");
        if(scanf("%d%c", &num, &term) != 2 || term != '\n') { // check if its number
            printf("\nError, reflejos tiene que ser un entero entre 0 y 10\n");
        } else {
            if (num >= 0 && num <= 10) {
                (*racer).reflexes = num;
                correctInput = true;
            } else {
                printf("\nError, reflejos tiene que ser un entero entre 0 y 10\n");
            }

        }
    }

    correctInput = false;

    // Physical condition
    while (!correctInput) {
        int num;
        char term;
        fflush(stdin);
        printf("\nCondicion fisica? ");
        if(scanf("%d%c", &num, &term) != 2 || term != '\n') { // check if its number
            printf("\nError, la condicion fisica tiene que ser un entero entre 0 y 10\n");
        } else {
            if (num >= 0 && num <= 10) {
                (*racer).physicalCondition = num;
                correctInput = true;
            } else {
                printf("\nError, la condicion fisica tiene que ser un entero entre 0 y 10\n");
            }

        }
    }

    correctInput = false;

    // Temperament
    while (!correctInput) {
        int num;
        char term;
        fflush(stdin);
        printf("\nTemperamento? ");
        if(scanf("%d%c", &num, &term) != 2 || term != '\n') { // check if its number
            printf("\nError, el temperamento tiene que ser un entero entre 0 y 10\n");
        } else {
            if (num >= 0 && num <= 10) {
                (*racer).temperament = num;
                correctInput = true;
            } else {
                printf("\nError, el temperamento tiene que ser un entero entre 0 y 10\n");
            }

        }
    }

    correctInput = false;

    // Tire management
    while (!correctInput) {
        int num;
        char term;
        fflush(stdin);
        printf("\nGestion de neumaticos? ");
        if(scanf("%d%c", &num, &term) != 2 || term != '\n') { // check if its number
            printf("\nError, la gestion de neumaticos tiene que ser un entero entre 0 y 10\n");
        } else {
            if (num >= 0 && num <= 10) {
                (*racer).tireManagement = num;
                correctInput = true;
            } else {
                printf("\nError, la gestion de neumaticos tiene que ser un entero entre 0 y 10\n");
            }

        }
    }

    printf("\nCargando configurador\n");

    return 0;
}
