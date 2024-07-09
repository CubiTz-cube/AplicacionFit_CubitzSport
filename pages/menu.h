#ifndef MENU_H
#define MENU_H

#include "../state.h"

void drawRecords(int* recordsD, int* recordsC){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    int j = 0;
    GuiDrawText("Records Personales", (Rectangle){ 1000, 15, 300, 20 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
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

int drawActivitiesUser(NodeActivity* activityUser, int page, int amount){
    if (!activityUser) return -1;
    NodeActivity* aux = activityUser;
    char activitiesNames[50][ACTIVITY_AMOUNT] = ACTIVITY_NAMESARRAY;
    int i = 0;
    int j = 0;
    while (aux){
        if (i < page*amount){
            aux = aux->next;
            i++;
            continue;
        }
        if (j == amount) break;
        char text[255];
        sprintf(text, "Actividad: %s\nDuracion: %d:%d:%d\nFecha: %d/%d/%d a las %d:%d:%d\nDistancia: %d m\nCalorias: %d", activitiesNames[aux->type], aux->duration.hour, aux->duration.minute, aux->duration.second, aux->date.day, aux->date.month, aux->date.year, aux->date.hour, aux->date.minute, aux->date.second, aux->distance, aux->calories);
        GuiDrawText(text, (Rectangle){ 500, 75 + 85*j, 300, 100 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        aux = aux->next;
        j++;
    }
    if (j == 0) return 0;
    return 1;
}

void layer_menu(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    static char message[255] = "";
    static int pageActivities = 0;
    BeginDrawing();

	ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 1280, 50, (Color){ 210, 210, 210, 255 });
    DrawRectangle(0, 50, 300, 670, (Color){ 80, 80, 80, 255 });
    DrawRectangle(1040, 50, 300, 670, (Color){ 180, 180, 180, 255 });

    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 36);
    GuiDrawText("CubiTz Sport", (Rectangle){ 0, 0, 300, 50 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiDrawText("Registros", (Rectangle){ 500, 15, 300, 20 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    //Botones 
    //Menu
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 30, 60, 240, 40 }, "#150# Agregar actividad")) {
        *page = 3;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 30, 60+50, 240, 40 }, "#185# Perfil")) {
        *page = 4;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 30, 60+50*2, 240, 40 }, "#189# Estadisticas")){ 
        *page = 5;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 30, 60+50*3, 240, 40 }, "#10#Open Exportar/Importar")) {
        *page = 6;
        message[0] = '\0';
    }
    // Paginas
    if (GuiButton((Rectangle){ 300, 680, 150, 40 }, "Anterior") && pageActivities > 0) {
        pageActivities--;
    }
    if (GuiButton((Rectangle){ 890, 680, 150, 40 }, "Siguiente")) {
        pageActivities++;
    }

    GuiDrawText(message, (Rectangle){ 600, 120+80*5, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    char textPage[255];
    sprintf(textPage, "Pagina %d", pageActivities+1);
    GuiDrawText(textPage, (Rectangle){ 600, 680, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    //Actividades
    drawRecords(hashTableUsers->users[actualUser]->recordsDistance, hashTableUsers->users[actualUser]->recordsCalories);
    
    NodeActivity* ActivityUser = filterActivitiesByUser(activities, actualUser);
    if (!drawActivitiesUser(ActivityUser, pageActivities, 6)){
        pageActivities--;
    }
    freeNodesActivity(&ActivityUser);

	EndDrawing();
}

#endif