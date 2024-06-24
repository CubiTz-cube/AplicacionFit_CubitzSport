#ifndef STRUCTS_H
#define STRUCTS_H

#include "../state.h"

typedef struct time{
    int hour;
    int minute;
    int second;
}Time;
typedef struct nodeActivity{
    int userId; // La posicion de usuario en la tabla de hash
    Time duration;
    Time startTime;
    int distance; // En m
    int calories;
    struct nodeActivity* next;
}NodeActivity;

typedef struct infoUser{
    char name[50];
   int old;
   char genero;
   float weight; // En kg
   int height; // En cm
   float BMI; // Indice de masa corporal
    int BFP; // Indice de grasa corporal
}InfoUser;
typedef struct achivement{
    int recordsDistance[ACTIVITY_AMOUNT];
    int recordsCalories[ACTIVITY_AMOUNT];
}Achivement;
typedef struct user{
   char mail[100];
   char password[50];
   int activities[ACTIVITY_AMOUNT];
   InfoUser* info;
    Achivement* achivement;
}User;

#endif