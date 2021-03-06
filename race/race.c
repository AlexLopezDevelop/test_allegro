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

void timer() {
    float time1, time0;
    int counter = 0;

    time0 = (float) clock();

    while (counter < 6) {
        time1 = (float) clock();

        if ((time1 - time0) / (float) CLOCKS_PER_SEC >= 1) {
            counter++;
            time0 = (float) clock();
        }
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

    if (currentSeason >= 4) {
        printf("\nFin de Temporada\n");
        return 1;
    }

    initView(championship);
    trafficLight();

    int seasonSpeed = (*(*championship).season).gps[currentSeason].properSpeed;
    int seasonAcceleration = (*(*championship).season).gps[currentSeason].properAcceleration;
    int seasonConsumption = (*(*championship).season).gps[currentSeason].properConsumption;
    int seasonFlexibility = (*(*championship).season).gps[currentSeason].properFlexibility;
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
    float seasonSeconds = (*(*championship).season).gps[currentSeason].baseTime;

    for (int j = 0; j < (*racersSeason).totalRacers; ++j) {
        racersSeconds[j] = seasonSeconds + (*racersSeason).racer[j].speed + (*racersSeason).racer[j].acceleration + (*racersSeason).racer[j].consumption + (*racersSeason).racer[j].flexibility;
    }

    // get pit stop players and update time
    int racersPitStops[8];
    int seasonPitStops;
    int playerPitStopTime;

    for (int j = 0; j < ((*racersSeason).totalRacers + 1); ++j) {

        seasonPitStops = (*(*championship).season).gps[currentSeason].pitStopNum;

        if ((*racersSeason).racer[j].consumption < (*(*championship).season).gps[currentSeason].properConsumption) {
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

    //show race
    // race screen
    int closeWindow = false;
    int xCirculo = 0;
    int speedVehicle[8];

    // clean array
    for (int j = 0; j < 8; ++j) {
        speedVehicle[j] = 0;
    }

    while(!closeWindow) {

        int width = 1300;
        int height = 720;
        int aux1 = (width*0.9)-(width*0.7)*0.2;
        int aux2 = (width*0.5)*0.1;
        int aux3;


        al_draw_filled_rectangle(0, 0, width*0.8, height*0.9, LS_allegro_get_color(WHITE));

        for (int i = 0; i < (totalRacers + 1); i++) {
            al_draw_line((width*0.5)*0.1, ((height*0.9)*0.1)*(i+1), (width*0.9)-(width*0.7)*0.2, ((height*0.9)*0.1)*(i+1), LS_allegro_get_color(BLACK), 5);
            al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(WHITE), (width*0.1)*0.1, ((height*0.9)*0.1)*(i+1)-10, 0, "%d", 23);
        }


        for (int i = 0; i < (totalRacers + 1); i++) {
            al_draw_filled_circle ((width*0.5)*0.1+(speedVehicle[i]), ((height*0.9)*0.1)*(i+1), 10, LS_allegro_get_color(RED));
        }

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),1060,670,0,"%s" "%d" "%s" "%d", "STOPS: ", racersPitStops[6], "/", (*(*championship).season).gps[currentSeason].pitStopNum);

        timer();
        //xCirculo += 20;
        for (int j = 0; j < 8; ++j) {
            aux3 = (aux1 - aux2) / (int) racersSeconds[j];
            speedVehicle[j] += aux3; //timepo coche (velocidad coche)
        }


        //Draw screen
        LS_allegro_clear_and_paint(BLACK);

        // Close window
        int currentSpeed = (int) speedVehicle[7];
        if (aux1 <= currentSpeed) { // check if my racer end the race
            closeWindow = true;
            break;
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

    //show stats
    closeWindow = false;
    int playerPosition = 0;

    // get player position
    for (int l = 0; l < sizeof(racerGlobal); ++l) {
        if (strcmp(player->racer->name, racerGlobal[l].racer.name) == 0) {
            playerPosition = l;
        }
    }

    playerPosition += 1;

    // user onclick keys
    while(!closeWindow) {

        // Close window
        if (LS_allegro_key_pressed(ALLEGRO_KEY_ENTER)) {
            closeWindow = true;
        }


        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),100,40,0,"%s", player->racer->name);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,70,0,"%s %d","Ha finalizado en la posicion ", playerPosition);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),100,90,0,"%s","Pulsa enter para volver al menu ");

        //Draw screen
        LS_allegro_clear_and_paint(BLACK);
    }

}
