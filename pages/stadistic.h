#ifndef STADISTIC_H
#define STADISTIC_H
#include "../state.h"
#include "../library/filters.h"

void drawHourActivityGlobal(int X, int Y, NodeActivity* activities[ACTIVITY_AMOUNT]){

    int hours[24] = {0};
    for (int i = 0; i<ACTIVITY_AMOUNT; i++){
        NodeActivity* aux = activities[i];
        while (aux){
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
        if (i < 12) GuiDrawText(text, (Rectangle){ X, Y + 25*j, 250, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        else GuiDrawText(text, (Rectangle){ X+250, Y + 25*j, 250, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        if (j == 12) j = 0;
        j++;
    }

}

void drawMaxRecord(HashTable* hashTableUsers){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 26);

    int maxDistance = 0;
    int maxDistanceUser = 0;
    int maxCalories = 0;
    int maxCaloriesUser = 0;
    for (int i = 0; i<USERS_AMOUNT; i++){
        if (!hashTableUsers->users[i]) continue;
        for (int j = 0; j<ACTIVITY_AMOUNT; j++){
            if (hashTableUsers->users[i]->recordsDistance[j] > maxDistance) {
                maxDistance = hashTableUsers->users[i]->recordsDistance[j];
                maxDistanceUser = i;
            }
            if (hashTableUsers->users[i]->recordsCalories[j] > maxCalories) {
                maxCalories = hashTableUsers->users[i]->recordsCalories[j];
                maxCaloriesUser = i;
            }
        }
    }
    char textD[255];
    sprintf(textD, "Distancia maxima: %d m\nUsuario: %s\nNombre: %s", maxDistance, hashTableUsers->users[maxDistanceUser]->mail, hashTableUsers->users[maxCaloriesUser]->info->name);
    char textC[255];
    sprintf(textC, "Calorias maxima: %d kc\nUsuario: %s\nNombre: %s", maxCalories ,hashTableUsers->users[maxCaloriesUser]->mail, hashTableUsers->users[maxCaloriesUser]->info->name);
    if (maxDistance != 0) GuiDrawText(textD, (Rectangle){ 900, 20 + 90*1, 300, 150 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    if (maxCalories != 0) GuiDrawText(textC, (Rectangle){ 900, 20 + 90*2, 300, 150 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

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
    
    drawMaxRecord(hashTableUsers);

    drawHourActivityGlobal( 0, 90, activities);
		
	EndDrawing();
}

#endif