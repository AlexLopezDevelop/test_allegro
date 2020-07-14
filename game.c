//
// Created by Alex Lopez on 19/06/2020.
//

#include "game.h"

void startGame(int argc, char *argv[]) {
    printf("\nCreated by cristianalex.lopez\n");
    printf("\nBienvenidos a LS Racing!\n");

    // Store all pieces
    Season * season = (Season *) malloc(sizeof(Season));
    Racer * racer = malloc(sizeof(Racer));
    Base base;
    Championship * championship = malloc(sizeof(Championship));
    Player *  player = malloc(sizeof(Player));
    Car * car = malloc(sizeof(Car));
    (*player).car = car;

    (*championship).racers = malloc(sizeof(Racers));
    (*(*championship).racers).racer = malloc(sizeof(Racer));

    (*championship).warehouse = malloc(sizeof(Warehouse));
    //(*(*championship).warehouse).categories = malloc(sizeof(Category));
    //(*(*(*championship).warehouse).categories).pieces = malloc(sizeof(Piece));

    // Load files
    loadGPs(argv[1], season);
    loadPieces(argv[2], championship);
    loadBase(argv[3], &base);
    loadRacers(argv[4], championship);

    // init game model
    (*championship).season = season;
    (*championship).base = &base;

    // init game
    int option = 0;
    int endGame = false;

    while(!endGame){

        int correctInput = 0;

        while (!correctInput) {
            showMainMenu();
            correctInput = readOption(&option);
        }

        endGame = switchOption(&option, racer, championship, player);
    }
}

int checkArgs(int argc, char *argv[]) {

    if((int) argc != TOTAL_ARGS) {
        printf("Error. El programa tiene que recibir 4 argumentos.");
        return 1;
    }

    // txt file 1
    int fileStatus = checkFile(argv[1], false);
    if (fileStatus == 1) {
        printf("\nError. Ha ocurrido un error durante el procesamiento de los ficheros.\n");
        return 1;
    } else if (fileStatus == 2) {
        printf("\nError. Hay un fichero vacio.\n");
        return 1;
    }

    // txt file 2
    fileStatus = checkFile(argv[2], false);
    if (fileStatus == 1) {
        printf("\nError. Ha ocurrido un error durante el procesamiento de los ficheros.\n");
        return 1;
    } else if (fileStatus == 2) {
        printf("\nError. Hay un fichero vacio.\n");
        return 1;
    }

    // txt file 3
    fileStatus = checkFile(argv[3], true);
    if (fileStatus == 1) {
        printf("\nError. Ha ocurrido un error durante el procesamiento de los ficheros.\n");
        return 1;
    } else if (fileStatus == 2) {
        printf("\nError. Hay un fichero vacio.\n");
        return 1;
    }

    // txt file 4
    fileStatus = checkFile(argv[4], true);
    if (fileStatus == 1) {
        printf("\nError. Ha ocurrido un error durante el procesamiento de los ficheros.\n");
        return 1;
    } else if (fileStatus == 2) {
        printf("\nError. Hay un fichero vacio.\n");
        return 1;
    }

    return 0;
}

void freeMemory(int * option, Racer * racer, Championship * championship) {
    //free(option);
    free(racer);

    free((*(*championship).racers).racer);
    //free((*championship).racers);

    free((*(*(*championship).warehouse).categories).pieces);
    free((*(*championship).warehouse).categories);
    //free((*championship).warehouse);

    free((*(*championship).season).gps);
    //free((*championship).season);

    //free((*championship).base);

    //free(championship);
}