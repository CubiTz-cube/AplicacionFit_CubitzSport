#ifndef STRUCTS_H
#define STRUCTS_H

#include "../state.h"

typedef struct time{
    int hour;
    int minute;
    int second;
}Time;

typedef struct infoUser{
    char name[50];
   int old;
   char gender;
   float weight; // En kg
   int height; // En cm
   float BMI; // Indice de masa corporal
    int BFP; // Indice de grasa corporal
}InfoUser;

typedef struct nodeActivity{
    int userId; // La posicion de usuario en la tabla de hash
    Time duration;
    Time startTime;
    int distance; // En m
    int calories;
    struct nodeActivity* next;
}NodeActivity;

typedef struct user{
   char mail[100];
   char password[50];
   int recordsDistance[ACTIVITY_AMOUNT];
   int recordsCalories[ACTIVITY_AMOUNT];
   InfoUser* info;
}User;

#endif