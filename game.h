//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_GAME_H
#define TEST_ALLEGRO_GAME_H

#define MAX_CHAR 26
#define TOTAL_ARGS 5

#include <stdio.h>
#include "LS_allegro.h"
#include "./interface/interface.h"
#include "./file/file.h"
#include "models/racer.h"
#include "models/pieces.h"
#include "models/gps.h"
#include "models/base.h"
#include "models/championship.h"
#include "models/player.h"
#include "models/check.h"

#define true 1
#define false 0

void startGame(int argc, char *argv[]);
int checkArgs(int argc, char *argv[]);
void freeMemory(int * option, Racer * racer, Championship * championship);

#endif //TEST_ALLEGRO_GAME_H
