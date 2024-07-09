#ifndef STADISTIC_H
#define STADISTIC_H
#include "../state.h"
#include "../library/filters.h"

void drawHourActivityUser(int X, int Y, NodeActivity* activitiesUsers){
    int hours[24] = {0};
    NodeActivity* aux = activitiesUsers;
    while (aux){
        hours[aux->date.hour]++;
        aux = aux->next;
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiDrawText("Horas de actividad", (Rectangle){ X, Y, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    int j = 1;
    for (int i = 0; i<24; i++){
        //if (hours[i] == 0) continue;
        char text[255];
        sprintf(text, "Hora %d : %d actividades", i+1, hours[i]);
        if (i < 12) GuiDrawText(text, (Rectangle){ X, Y+10 + 25*j, 250, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        else GuiDrawText(text, (Rectangle){ X+250, Y+10 + 25*j, 250, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        if (j == 12) j = 0;
        j++;
    }
}

void drawHourActivityGlobal(int X, int Y, NodeActivity* activities[ACTIVITY_AMOUNT]){

    int hours[24] = {0};
    for (int i = 0; i<ACTIVITY_AMOUNT; i++){
        NodeActivity* aux = activities[i];
        while (aux){
            //printf("Hora: %d\n", aux->date.hour);
            hours[aux->date.hour]++;
            aux = aux->next;
        }
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiDrawText("Horas de actividad global", (Rectangle){ X, Y, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    int j = 1;
    for (int i = 0; i<24; i++){
        //if (hours[i] == 0) continue;
        char text[255];
        sprintf(text, "Hora %d : %d actividades", i+1, hours[i]);
        if (i < 12) GuiDrawText(text, (Rectangle){ X, Y+10 + 25*j, 250, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        else GuiDrawText(text, (Rectangle){ X+250, Y+10 + 25*j, 250, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        if (j == 12) j = 0;
        j++;
    }

}

void drawMaxRecord(NodeActivity* activities[ACTIVITY_AMOUNT], HashTable* hashTableUsers, int X, int Y){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 18);
    GuiDrawText("Records de Calorias", (Rectangle){ X, Y, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiDrawText("Records de Distancia", (Rectangle){ X+300, Y, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    char actityNames[50][ACTIVITY_AMOUNT] = ACTIVITY_NAMESARRAY;
    int indexC = 1;
    int indexD = 1;
    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        if (!activities[i]) continue;
        int maxD = 0;
        int userD = 0;

        char text[255];
        sprintf(text, "%s | %d kc\nUsuario: %s", actityNames[i], activities[i]->calories, hashTableUsers->users[activities[i]->userId]->mail);
        GuiDrawText(text, (Rectangle){ X, Y+10 + 40*indexC, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        indexC++;

        // Calcular distancia maxima
        NodeActivity* aux = activities[i];
        while (aux){
            if (aux->distance > maxD){
                maxD = aux->distance;
                userD = aux->userId;
            }
            aux = aux->next;
        }
        if (maxD != 0){
            char text[255];
            sprintf(text, "%s | %d m\nUsuario: %s", actityNames[i], maxD, hashTableUsers->users[userD]->mail);
            GuiDrawText(text, (Rectangle){ X+300, Y+10 + 40*indexD, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
            indexD++;
        }
    }
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 15);
}

void layer_stadistic(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz Estadisticas", (Rectangle){ 0, 0, 400, 60 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 300, 50, 150, 40 }, "Volver al menu")) *page = 2;

    //Estadisticas
    
    drawMaxRecord(activities, hashTableUsers, 500, 90);

    drawHourActivityGlobal( 0, 90, activities);
    NodeActivity* activitiesUser = filterActivitiesByUser(activities, actualUser);
    drawHourActivityUser( 500, 300, activitiesUser);
	freeNodesActivity(&activitiesUser);

	EndDrawing();
}

#endif