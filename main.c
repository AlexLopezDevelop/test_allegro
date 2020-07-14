#include "game.h"

int main(int argc, char *argv[]) {

    if (checkArgs(argc, argv)) {
        return 1;
    }

    startGame(argc, argv);

    return 0;
}