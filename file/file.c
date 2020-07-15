//
// Created by Alex Lopez on 19/06/2020.
//

#include "file.h"

int checkFile(char *filename, int itsBin) {
    FILE * file;

    // Check can open
    if (itsBin) {
        file = fopen(filename, "rb");
    } else {
        file = fopen(filename, "r");
    }

    if (file == NULL) {
        return 1;
    }

    // Check empty file
    int size = 0;
    if(file!=NULL) {
        fseek (file, 0, SEEK_END);

        size = ftell (file);
        rewind(file);
    }

    if (size==0) {
        return 2;
    }

    // Valid file
    fclose(file);
    return 0;
}

void loadPieces(char *fileName, Championship * championship) {
    FILE *file = NULL;
    char line[MAX_CHAR];

    file = fopen((char *) fileName, "r");

    if (file == NULL) {
        printf("\nError al abrir el fichero: %s\n", (char *) fileName);
    } else {

        file = fopen((char *) fileName, "r");

        int i = 0;

        while (!feof(file)) {

            switch (i) {
                case 0:
                    // total categories
                    fgets(line, MAX_CHAR, file);
                    (*(*championship).warehouse).totalCategories = (int) atoi(&line[0]);
                    (*(*championship).warehouse).categories = (Category *) malloc(sizeof(Category) * (*(*championship).warehouse).totalCategories);
                    i++;
                    break;
                case 1:
                    // categories
                    for (int j = 0; j < (*(*championship).warehouse).totalCategories; j++) {
                        fgets(line, MAX_CHAR, file);
                        strcpy((*(*championship).warehouse).categories[j].name, line);
                        fgets(line, MAX_CHAR, file);
                        (*(*championship).warehouse).categories[j].totalPieces = (int) atoi(&line[0]);
                        (*(*championship).warehouse).categories[j].pieces = (Piece *) malloc(sizeof(Piece) * (*(*championship).warehouse).categories[j].totalPieces);

                        // pieces
                        for (int k = 0; k < (*(*championship).warehouse).categories[j].totalPieces; k++) { // Piece
                            fgets(line, MAX_CHAR, file);
                            strcpy((*(*championship).warehouse).categories[j].pieces[k].name, line);

                            fgets(line, MAX_CHAR, file);
                            (*(*championship).warehouse).categories[j].pieces[k].speed = atoi(&line[0]);

                            fgets(line, MAX_CHAR, file);
                            (*(*championship).warehouse).categories[j].pieces[k].acceleration = atoi(&line[0]);

                            fgets(line, MAX_CHAR, file);
                            (*(*championship).warehouse).categories[j].pieces[k].consumption = atoi(&line[0]);

                            fgets(line, MAX_CHAR, file);
                            (*(*championship).warehouse).categories[j].pieces[k].reliability = atoi(&line[0]);

                        }
                    }
                    i++;
                    break;
                default:
                    //next lines
                    fgets(line, MAX_CHAR, file);
                    break;
            }
        }

        fclose(file);
    }
}

void loadGPs(char * fileName, Season * season) {
    FILE *file = NULL;
    char line[MAX_CHAR];

    file = fopen((char *) fileName, "r");

    if (file == NULL) {
        printf("\nError al abrir el fichero: %s\n", (char *) fileName);
    } else {

        int i = 0;

        while (!feof(file)) {
            switch (i) {
                case 0:
                    // total gps
                    fgets(line, MAX_CHAR, file);
                    (*season).totalGps = atoi(&line[0]);
                    (*season).currentCalendarPosition = START_CALENDAR_POSITION;
                    (*season).gps = malloc(sizeof(Gps) * (*season).totalGps);
                    i++;
                    break;
                case 1:
                    // gps
                    for (int j = 0; j < (*season).totalGps; ++j) {
                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].calendarPosition = atoi(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        strcpy((*season).gps[j].name, line);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].properSpeed = atoi(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].properAcceleration = atoi(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].properConsumption = atoi(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].properFlexibility = atoi(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].baseTime = atof(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].pitStopTime = atoi(&line[0]);

                        fgets(line, MAX_CHAR, file);
                        (*season).gps[j].pitStopNum = atoi(&line[0]);
                    }
                    i++;
                    break;
                default:
                    fgets(line, MAX_CHAR, file);
                    break;
            }

        }

        fclose(file);
    }
}

void loadRacers(char *fileName, Championship * championship) {
    FILE *file = NULL;
    Racer line;

    file = fopen((char *) fileName, "rb");

    if (file == NULL) {
        printf("\nError al abrir el fichero: %s\n", (char *) fileName);
    } else {

        int i = 0;

        fread(&line, sizeof(Racer), 1, file);
        (*(*championship).racers).racer[0] = line;

        while (!feof(file)) {
            i++;
            fread(&line, sizeof(Racer), 1, file);
            (*(*championship).racers).racer = (Racer *) realloc((*(*championship).racers).racer, sizeof(Racer) * sizeof((*(*championship).racers).racer));
            (*(*championship).racers).racer[i] = line;
        }

        // setup racersº
        (*(*championship).racers).totalRacers = i;
        fclose(file);
    }
}

void loadBase(char *fileName, Base * base) {
    FILE *file = NULL;
    Base line;

    file = fopen((char *) fileName, "rb");

    if (file == NULL) {
        printf("\nError al abrir el fichero: %s\n", (char *) fileName);
    } else {

        // Only one time
        fread(&line, sizeof(Base), 1, file);
        *base = line;

        // avoid data below
        while (!feof(file)) {
            fread(&line, sizeof(Base), 1, file);
        }

        fclose(file);
    }
}

int saveClassification(RacerGlobal * racerGlobal) {

    // creating file pointer to work with files
    FILE *file;

    // opening file in writing mode
    file = fopen("classification.txt", "w");

    // exiting program
    if (file == NULL) {
        printf("Error!");
        exit(1);
    }

    for (int i = 0; i < sizeof(racerGlobal); ++i) {
        fprintf(file, "%d. %s con %d segundos.  Puntos: %d\n",i+1 , racerGlobal[i].racer.name, racerGlobal[i].time, racerGlobal[i].points);
    }

    fclose(file);
    return 0;
}