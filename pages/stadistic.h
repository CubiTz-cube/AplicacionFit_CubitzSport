#ifndef STADISTIC_H
#define STADISTIC_H
#include "../state.h"

void drawMaxRecord(HashTable* hashTableUsers){
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
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 26);
    drawMaxRecord(hashTableUsers);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 15);
		
	EndDrawing();
}

#endif