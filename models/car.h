//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_CAR_H
#define TEST_ALLEGRO_CAR_H

#include "pieces.h"

typedef struct {
    Piece * tires;
    Piece * aeroFront;
    Piece * aeroMiddleZone;
    Piece * aeroBack;
    Piece * petrol;
    Piece * engine;
} Car;

#endif //TEST_ALLEGRO_CAR_H
