//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_FILE_H
#define TEST_ALLEGRO_FILE_H

#define START_CALENDAR_POSITION 0 // Starts in season 1

#include "../game.h"
#include "../models/pieces.h"
#include "../models/gps.h"
#include "../models/racer.h"
#include "../models/base.h"
#include <stdio.h>

int checkFile(char *filename, int itsBin);
void loadPieces(char *filename, Championship * championship);
void loadGPs(char *fileName, Season * season);
void loadRacers(char *filename, Championship * championship);
void loadBase(char *fileName, Base * base);
int saveClassification(RacerGlobal * racerGlobal);

#endif //TEST_ALLEGRO_FILE_H
