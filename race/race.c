//
// Created by Alex Lopez on 19/06/2020.
//

#include "race.h"

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

void initView(Championship * championship) {
    int currentSeason = (*(*championship).season).currentCalendarPosition;

    if (currentSeason < (*(*championship).season).totalGps) {
        printf("\nPreparando carrera #%d: %s\n", currentSeason + 1, (*(*championship).season).gps[currentSeason].name);

        int closeWindow = false;

        // user onclick keys
        while(!closeWindow) {

            // Close window
            if (LS_allegro_key_pressed(ALLEGRO_KEY_R)) {
                closeWindow = true;
            }


            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),100,40,0,"%s %s","Bienvenido a ", (*(*championship).season).gps[currentSeason].name);
            al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,70,0,"%s %d","Velocidad:", (*(*championship).season).gps[currentSeason].properSpeed);
            al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,90,0,"%s %d","Aceleracion: ", (*(*championship).season).gps[currentSeason].properAcceleration);
            al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,110,0,"%s %d","Consumo: ", (*(*championship).season).gps[currentSeason].properConsumption);
            al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,130,0,"%s %d","Fiabilidad: ", (*(*championship).season).gps[currentSeason].properFlexibility);
            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),100,160,0,"%s","Pulsa R para comenzar la carrera");


            //Draw screen
            LS_allegro_clear_and_paint(BLACK);
        }


    } else {
        printf("\nYa has finalizado la temporada\n");
    }

}

void trafficLight() {
    int closeWindow = false;

    clock_t begin;
    double time_spent;
    /* Mark beginning time */
    begin = clock();

    // user onclick keys
    while(!closeWindow) {



        // Close window
        if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
            closeWindow = true;
        }


        time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;

        // on
        if (time_spent>=0.1) {
            al_draw_filled_circle (150, 150, 50, LS_allegro_get_color(RED));
            al_draw_filled_circle (150, 300, 50, LS_allegro_get_color(RED));
        }

        if (time_spent>=0.2) {
            al_draw_filled_circle (300, 150, 50, LS_allegro_get_color(RED));
            al_draw_filled_circle (300, 300, 50, LS_allegro_get_color(RED));
        }

        if (time_spent>=0.3) {
            al_draw_filled_circle (450, 150, 50, LS_allegro_get_color(RED));
            al_draw_filled_circle (450, 300, 50, LS_allegro_get_color(RED));
        }

        if (time_spent>=0.4) {
            al_draw_filled_circle (600, 150, 50, LS_allegro_get_color(RED));
            al_draw_filled_circle (600, 300, 50, LS_allegro_get_color(RED));
        }

        if (time_spent>=0.5) {
            al_draw_filled_circle (750, 150, 50, LS_allegro_get_color(RED));
            al_draw_filled_circle (750, 300, 50, LS_allegro_get_color(RED));
        }

        // off

        if (time_spent>=0.7) {
            al_draw_filled_circle (150, 150, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (150, 300, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (300, 150, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (300, 300, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (450, 150, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (450, 300, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (600, 150, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (600, 300, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (750, 150, 50, LS_allegro_get_color(BLACK));
            al_draw_filled_circle (750, 300, 50, LS_allegro_get_color(BLACK));
        }

        if (time_spent>=0.75) {
            closeWindow = true;
        }

        //Draw screen
        LS_allegro_clear_and_paint(BLACK);
    }
}

int startRace(Championship * championship, Player * player, RacerGlobal * racerGlobal, Check * check) {

    // check if car its configured
    if (check->configureCar == 0) {
        printf("\nAun no has configurado el coche\n");
        return 1;
    }


    // check if no more seasons
    int currentSeason = (*(*championship).season).currentCalendarPosition;

    if (currentSeason >= 5) {
        printf("\nFin de Temporada\n");
        return 1;
    }

    initView(championship);
    //trafficLight();

    int seasonSpeed = (*(*championship).season[currentSeason].gps).properSpeed;
    int seasonAcceleration = (*(*championship).season[currentSeason].gps).properAcceleration;
    int seasonConsumption = (*(*championship).season[currentSeason].gps).properConsumption;
    int seasonFlexibility = (*(*championship).season[currentSeason].gps).properFlexibility;
    int totalRacers = (*(*championship).racers).totalRacers;

    Racers *racersSeason = malloc(sizeof(Racers));
    Racer racer;

    (*racersSeason).racer = malloc(sizeof(Racer));
    (*racersSeason).racer = realloc((*racersSeason).racer, sizeof(Racer) * (totalRacers + 1));

    // create racers with season data
    for (int i = 0; i < totalRacers; ++i) {

        // season player date update
        racer.speed = seasonSpeed - (*(*championship).racers).racer[i].speed;
        racer.acceleration = seasonAcceleration - (*(*championship).racers).racer[i].speed;
        racer.consumption = seasonConsumption - (*(*championship).racers).racer[i].consumption;
        racer.flexibility = seasonFlexibility - (*(*championship).racers).racer[i].flexibility;
        strcpy(racer.name, (*(*championship).racers).racer[i].name);
        strcpy(racer.team, (*(*championship).racers).racer[i].team);
        racer.dorsal = (*(*championship).racers).racer[i].dorsal;
        racer.physicalCondition = (*(*championship).racers).racer[i].physicalCondition;
        racer.reflexes = (*(*championship).racers).racer[i].reflexes;
        racer.temperament = (*(*championship).racers).racer[i].temperament;
        racer.tireManagement = (*(*championship).racers).racer[i].tireManagement;

        (*racersSeason).racer[i] = racer;
    }

    // add player
    //(*racersSeason).racer = realloc((*racersSeason).racer, sizeof(Racer));

    racer.speed = seasonSpeed - (*(*player).racer).speed;
    racer.acceleration = seasonAcceleration - (*(*player).racer).speed;
    racer.consumption = seasonConsumption - (*(*player).racer).consumption;
    racer.flexibility = seasonFlexibility - (*(*player).racer).flexibility;
    strcpy(racer.name, (*(*player).racer).name);
    strcpy(racer.team, (*(*player).racer).team);
    racer.dorsal = (*(*player).racer).dorsal;
    racer.physicalCondition = (*(*player).racer).physicalCondition;
    racer.reflexes = (*(*player).racer).reflexes;
    racer.temperament = (*(*player).racer).temperament;
    racer.tireManagement = (*(*player).racer).tireManagement;

    // add all players
    (*racersSeason).racer[totalRacers] = racer;
    (*racersSeason).totalRacers = totalRacers;

    // get seconds players
    float *racersSeconds = racersSeconds = malloc(sizeof(int) * (*racersSeason).totalRacers);
    float seasonSeconds = (*(*championship).season[currentSeason].gps).baseTime;

    for (int j = 0; j < (*racersSeason).totalRacers; ++j) {
        racersSeconds[j] = seasonSeconds + (*racersSeason).racer[j].speed + (*racersSeason).racer[j].acceleration + (*racersSeason).racer[j].consumption + (*racersSeason).racer[j].flexibility;
    }

    // get pit stop players and update time
    int racersPitStops[8];
    int seasonPitStops;
    int playerPitStopTime;

    for (int j = 0; j < ((*racersSeason).totalRacers + 1); ++j) {

        seasonPitStops = (*(*championship).season[currentSeason].gps).pitStopNum;

        if ((*racersSeason).racer[j].consumption < (*(*championship).season[currentSeason].gps).properConsumption) {
            seasonPitStops--;
        } else {
            seasonPitStops++;
        }

        racersPitStops[j] = seasonPitStops;
        playerPitStopTime = 5 * racersPitStops[j];

        // update time
        racersSeconds[j] = racersSeconds[j] + playerPitStopTime;
    }

    // update time with player skills
    int totalPlayerSkills;
    float playerSkillTime;

    for (int k = 0; k < ((*racersSeason).totalRacers + 1); ++k) {

        totalPlayerSkills = (*racersSeason).racer[k].reflexes + (*racersSeason).racer[k].physicalCondition +
                            (*racersSeason).racer[k].temperament + (*racersSeason).racer[k].tireManagement;

        playerSkillTime = (float) (totalPlayerSkills / 4) / 2;

        racersSeconds[k] = racersSeconds[k] - playerSkillTime;
    }

    // race screen
    int closeWindow = false;

    clock_t begin;
    double time_spent;
    /* Mark beginning time */
    begin = clock();

    while(!closeWindow) {

        // Close window
        if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
            closeWindow = true;
        }

        int width = 1300;
        int height = 720;

        al_draw_filled_rectangle(0, 0, width*0.8, height*0.9, LS_allegro_get_color(WHITE));

        for (int i = 0; i < totalRacers; i++) {
            al_draw_line((width*0.5)*0.1, ((height*0.9)*0.1)*(i+1), (width*0.9)-(width*0.7)*0.2, ((height*0.9)*0.1)*(i+1), LS_allegro_get_color(BLACK), 5);
            al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(WHITE), (width*0.1)*0.1, ((height*0.9)*0.1)*(i+1)-10, 0, "%d", 23);
        }

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),1060,670,0,"%s" "%d" "%s" "%d", "STOPS: ", racersPitStops[6], "/", (*(*championship).season[currentSeason].gps).pitStopNum);

        //Draw screen
        LS_allegro_clear_and_paint(BLACK);

    }

    // Create time struct
    for (int i = 0; i < (totalRacers + 1); i++) {
        racerGlobal[i].racer = (*racersSeason).racer[i];
        racerGlobal[i].time = racersSeconds[i];
    }


    // order by time
    for (int i = 0; i < (totalRacers + 1); ++i) {
        for (int j = totalRacers; j > i; --j) {
            if (racerGlobal[i].time > racerGlobal[j].time) {
                RacerGlobal aux = racerGlobal[i];
                racerGlobal[i] = racerGlobal[j];
                racerGlobal[j] = aux;
            }
        }
    }


    //add points

    racerGlobal[0].points = 25;
    racerGlobal[1].points = 18;
    racerGlobal[2].points = 15;
    racerGlobal[3].points = 10;
    racerGlobal[4].points = 8;
    racerGlobal[5].points = 6;
    racerGlobal[6].points = 5;
    racerGlobal[7].points = 3;

    // next gps



    if (currentSeason < MAX_SEASON) {
        (*(*championship).season).currentCalendarPosition = currentSeason + 1;
    }

    (*check).season = 1;

}
