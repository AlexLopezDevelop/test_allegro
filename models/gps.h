//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_GPS_H
#define TEST_ALLEGRO_GPS_H

#include "../game.h"

typedef struct {
    int calendarPosition;
    char name[MAX_CHAR];
    int properSpeed;
    int properAcceleration;
    int properConsumption;
    int properFlexibility;
    float baseTime;
    int pitStopTime;
    int pitStopNum;
} Gps;

typedef struct {
    int totalGps;
    int currentCalendarPosition;
    Gps * gps;
} Season;

#endif //TEST_ALLEGRO_GPS_H
