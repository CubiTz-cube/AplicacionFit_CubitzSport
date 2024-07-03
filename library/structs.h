#ifndef STRUCTS_H
#define STRUCTS_H

#include "../state.h"

typedef struct time
{
    int second;
    int minute;
    int hour;
}Time;

typedef struct date{
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
}Date;

typedef struct infoUser{
    char name[50];
   int old;
   char gender;
   float weight; // En kg
   int height; // En cm
   float BMI; // Indice de masa muscular
    int BFP; // Porcentaje grasa corporal
}InfoUser;

typedef struct nodeActivity
{
    int userId; // La posicion de usuario en la tabla de hash
    Time duration;
    Date date;
    int distance; // En m
    int calories;
    int type;
    struct nodeActivity* next;
}NodeActivity;

typedef struct user{
   char mail[100];
   char password[50];
   int recordsDistance[ACTIVITY_AMOUNT];
   int recordsCalories[ACTIVITY_AMOUNT];
   InfoUser* info;
}User;

typedef struct hashTable{
    User** users;
    int amount;
    int max;
}HashTable;


#endif