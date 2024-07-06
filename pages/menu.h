#ifndef MENU_H
#define MENU_H

#include "../state.h"

void drawActivities(NodeActivity* activitieList){
    if (!activitieList) return;
    NodeActivity* aux = activitieList;
    int i = 0;
    while (aux){
        int j = 0;
        char activitiesNames[50][ACTIVITY_AMOUNT] = ACTIVITY_NAMESARRAY;
            
        char text[255];
        sprintf(text, "Actividad: %s\nDuracion: %d:%d:%d\nFecha: %d/%d/%d a las %d:%d:%d\nDistancia: %d m\nCalorias: %d", activitiesNames[aux->type], aux->duration.hour, aux->duration.minute, aux->duration.second, aux->date.day, aux->date.month, aux->date.year, aux->date.hour, aux->date.minute, aux->date.second, aux->distance, aux->calories);
        GuiDrawText(text, (Rectangle){ 500, 100 + 85*i, 300, 100 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        aux = aux->next;
        i++;
    }
}

void drawRecords(int* recordsD, int* recordsC){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    int j = 0;
    GuiDrawText("Records Personales", (Rectangle){ 1000, 15, 300, 50 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        char text[255];
        char activitiesNames[50][ACTIVITY_AMOUNT] = ACTIVITY_NAMESARRAY;
        if (recordsD[i] == 0 && recordsC[i] == 0) continue;

        if (recordsD[i] == 0) sprintf(text, "Record %s\nCalorias: %d", activitiesNames[i], recordsC[i]);
        else if (recordsC[i] == 0) sprintf(text, "Record %s\nDistancia: %d m", activitiesNames[i], recordsD[i]);
        else sprintf(text, "Record %s\nDistancia: %d m\nCalorias: %d", activitiesNames[i], recordsD[i], recordsC[i]);
        GuiDrawText(text, (Rectangle){ 1000, 50 + 45*j, 300, 100 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        j++;
    }
}

void layer_menu(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    static char message[255] = "";
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz MENU", (Rectangle){ 0, 0, 300, 50 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    //Botones
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 50, 60, 200, 40 }, "Anadir actividad")) {
        *page = 3;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 50, 60+50, 200, 40 }, "Perfil")) {
        *page = 4;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 50, 60+50*2, 200, 40 }, "Estadisticas")){ 
        *page = 5;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 50, 60+50*3, 200, 40 }, "Exportar/Importar")) {
        *page = 6;
        message[0] = '\0';
    }

    GuiDrawText(message, (Rectangle){ 600, 120+80*5, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    //Actividades
    drawActivities(activities[0]);
    drawRecords(hashTableUsers->users[actualUser]->recordsDistance, hashTableUsers->users[actualUser]->recordsCalories);
		
	EndDrawing();
}

#endif