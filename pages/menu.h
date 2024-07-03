#ifndef MENU_H
#define MENU_H

#include "../state.h"

void drawActivities(NodeActivity* activitieList){
    if (!activitieList) return;
    NodeActivity* aux = activitieList;
    int i = 0;
    while (aux){
        int j = 0;
        char activitiesNames[255] = ACTIVITY_NAMES;
        char* token = strtok(activitiesNames, ";");
        do{
            if (j == aux->type) break;
            j++;
        }while (token = strtok(NULL, ";"));
            
        char text[255];
        sprintf(text, "Actividad: %s\nDuracion: %d:%d:%d\nFecha: %d/%d/%d a las %d:%d:%d\nDistancia: %d m\nCalorias: %d", token, aux->duration.hour, aux->duration.minute, aux->duration.second, aux->date.day, aux->date.month, aux->date.year, aux->date.hour, aux->date.minute, aux->date.second, aux->distance, aux->calories);
        GuiDrawText(text, (Rectangle){ 500, 100 + 85*i, 300, 100 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        aux = aux->next;
        i++;
    }
}

void layer_menu(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, NodeActivity* activities[ACTIVITY_AMOUNT]){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz MENU", (Rectangle){ 500, 0, 300, 100 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    //Botones
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 50, 200, 200, 40 }, "Anadir actividad")) {
        *page = 3;
        seeAllNodesActivity(activities);
    }
    if (GuiButton((Rectangle){ 50, 250, 200, 40 }, "Perfil")) *page = 4;
    if (GuiButton((Rectangle){ 50, 300, 200, 40 }, "Estadisticas")) *page = 5;

    //Actividades
    drawActivities(activities[0]);
		
	EndDrawing();
}

#endif