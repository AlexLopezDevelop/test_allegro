//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_CHAMPIONSHIP_H
#define TEST_ALLEGRO_CHAMPIONSHIP_H

#include "../models/gps.h"
#include "../models/pieces.h"
#include "../models/base.h"
#include "../models/racer.h"

typedef struct {
    Season * season;
    Warehouse * warehouse;
    Base * base;
    Racers * racers;
} Championship;

#endif //TEST_ALLEGRO_CHAMPIONSHIP_H
