//
// Created by Alex Lopez on 19/06/2020.
//

#include "configuration.h"

// default player car
void carPlayer(Player * player, Championship * championship) {
    (*(*player).car).tires = &(*(*championship).warehouse).categories[0].pieces[0];
    (*(*player).car).aeroFront = &(*(*championship).warehouse).categories[1].pieces[0];
    (*(*player).car).aeroMiddleZone = &(*(*championship).warehouse).categories[2].pieces[0];
    (*(*player).car).aeroBack = &(*(*championship).warehouse).categories[3].pieces[0];
    (*(*player).car).petrol = &(*(*championship).warehouse).categories[4].pieces[0];
    (*(*player).car).engine = &(*(*championship).warehouse).categories[5].pieces[0];
}

void updateCarPlayer(Player * player, Championship * championship, int currentPiece, int currentCategory) {
    switch (currentCategory) {
        case 0:
            (*(*player).car).tires = &(*(*championship).warehouse).categories[currentCategory].pieces[currentPiece];
            break;
        case 1:
            (*(*player).car).aeroFront = &(*(*championship).warehouse).categories[currentCategory].pieces[currentPiece];
            break;
        case 2:
            (*(*player).car).aeroMiddleZone = &(*(*championship).warehouse).categories[currentCategory].pieces[currentPiece];
            break;
        case 3:
            (*(*player).car).aeroBack = &(*(*championship).warehouse).categories[currentCategory].pieces[currentPiece];
            break;
        case 4:
            (*(*player).car).petrol = &(*(*championship).warehouse).categories[currentCategory].pieces[currentPiece];
            break;
        case 5:
            (*(*player).car).engine = &(*(*championship).warehouse).categories[currentCategory].pieces[currentPiece];
            break;
        default:
            printf("\nUpdateCarPlayer default\n");
            break;
    }
}

void configureCar(Racer * racer, Championship * championship, Player * player) {

    // Check if racer exists
    if (strcmp((*racer).name, "") == 0) {
        racerData(racer);
        (*player).racer = racer;
        carPlayer(player, championship);
    }

    //Init Allegro
    LS_allegro_init(1300,720,"Configuracion del coche");


    // Screen actions
    int closeWindow = false;
    int currentPiece = 0;
    int currentCategory = 0;

    // user onclick keys
    while(!closeWindow) {

        // Close window
        if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
            updateCarPlayer(player, championship, currentPiece, currentCategory);
            closeWindow = true;
        }

        // Piece category
        if (LS_allegro_key_pressed(ALLEGRO_KEY_UP)) {

            updateCarPlayer(player, championship, currentPiece, currentCategory);

            if (currentCategory > 0) {
                currentCategory--;
            } else {
                currentCategory = (*(*championship).warehouse).totalCategories - 1;
            }

        }

        if (LS_allegro_key_pressed(ALLEGRO_KEY_DOWN)) {

            updateCarPlayer(player, championship, currentPiece, currentCategory);

            if (currentCategory < (*(*championship).warehouse).totalCategories - 1) {
                currentCategory++;
            } else {
                currentCategory = 0;
            }

        }

        // Model piece
        if (LS_allegro_key_pressed(ALLEGRO_KEY_LEFT)) {

            if (currentPiece > 0) {
                currentPiece--;
            } else {
                currentPiece = (*(*championship).warehouse).categories[currentCategory].totalPieces - 1;
            }

        }

        if (LS_allegro_key_pressed(ALLEGRO_KEY_RIGHT)) {
            if (currentPiece < (*(*championship).warehouse).categories[currentCategory].totalPieces - 1) {
                currentPiece++;
            } else {
                currentPiece = 0;
            }
        }

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),100,40,0,"%s", (*(*championship).warehouse).categories[currentCategory].name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,70,0,"%s", (*(*championship).warehouse).categories[currentCategory].pieces[currentPiece].name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,90,0,"%s %d","Velocidad: ", (*(*championship).warehouse).categories[currentCategory].pieces[currentPiece].speed);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,110,0,"%s %d","Aceleracion: ", (*(*championship).warehouse).categories[currentCategory].pieces[currentPiece].acceleration);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,130,0,"%s %d","Consumo: ", (*(*championship).warehouse).categories[currentCategory].pieces[currentPiece].consumption);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,150,0,"%s %d","Fiabilidad: ", (*(*championship).warehouse).categories[currentCategory].pieces[currentPiece].reliability);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),100,250,0,"%s","Configuracion Actual");
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,280,0,"%s %s","Neumaticos:", (*(*(*player).car).tires).name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,300,0,"%s %s","Aero frontal: ", (*(*(*player).car).aeroFront).name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,320,0,"%s %s","Aero zona media: ", (*(*(*player).car).aeroMiddleZone).name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,340,0,"%s %s","Aero posterior: ", (*(*(*player).car).aeroBack).name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,360,0,"%s %s","Gasolina: ", (*(*(*player).car).petrol).name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,380,0,"%s %s","Motor: ", (*(*(*player).car).engine).name);


        //Draw screen
        LS_allegro_clear_and_paint(BLACK);
    }
}