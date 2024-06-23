#ifndef STRUCTS_H
#define STRUCTS_H

#include "../state.h"

typedef struct time{
    int hour;
    int minute;
    int second;
}Time;
typedef struct nodeActivity{
    Time duration;
    Time startTime;
    int distance; // En m
    int calories;
    int userId; // La posicion de usuario en la tabla de hash
}NodeActivity;

typedef struct infoUser{
    char name[50];
   int edad;
   char genero;
   int weight;
   int height;
   float IMC;
    int BFP;
}InfoUser;
typedef struct achivement{
    int recordsDistance[ACTIVITY_AMOUNT];
    int recordsCalories[ACTIVITY_AMOUNT];
}Achivement;
typedef struct user{
   char mail[100];
   char password[50];
   NodeActivity* activities[ACTIVITY_AMOUNT];
   InfoUser info;
    Achivement achivement;
}User;

#endif