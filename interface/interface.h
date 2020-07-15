//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_INTERFACE_H
#define TEST_ALLEGRO_INTERFACE_H

#define MENU_OPTION_EXIT -1
#define MENU_OPTION_1 1
#define MENU_OPTION_2 2
#define MENU_OPTION_3 3
#define MENU_OPTION_4 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../configuration/configuration.h"
#include "../models/racer.h"
#include "../models/player.h"
#include "../models/championship.h"
#include "../race/race.h"
#include "../models/check.h"

void showMainMenu();
int readOption(int * option);
int switchOption(int * option, Racer * racer, Championship * championship, Player * player, RacerGlobal * racerGlobal, Check * check);
int racerData(Racer * racer);

#endif //TEST_ALLEGRO_INTERFACE_H
