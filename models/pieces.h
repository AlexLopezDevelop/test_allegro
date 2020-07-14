//
// Created by Alex Lopez on 19/06/2020.
//

#ifndef TEST_ALLEGRO_PIECES_H
#define TEST_ALLEGRO_PIECES_H

#include "../game.h"

typedef struct {
    char name[MAX_CHAR];
    int speed;
    int acceleration;
    int consumption;
    int reliability;
} Piece;

typedef struct {
    char name[MAX_CHAR];
    int totalPieces;
    Piece *pieces;
} Category;

typedef struct {
    int totalCategories;
    Category *categories;
} Warehouse;

#endif //TEST_ALLEGRO_PIECES_H
