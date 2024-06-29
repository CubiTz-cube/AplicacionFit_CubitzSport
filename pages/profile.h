#ifndef PROFILE_H
#define PROFILE_H
#include "../state.h"

void layer_profile(int* page, Font* fontLekton, Font* fontAldrich, int* actualUser, HashTable* hashTableUsers){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz Perfil", (Rectangle){ 0, 0, 300, 100 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    // Input de User Info

    int Xtemp = 0; int Ytemp = 120;
    int Wtemp = 300; int Htemp = 30; 
    int padingX = 200; int padingY = 50;

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

    GuiDrawText("Nombre: ", (Rectangle){ Xtemp, Ytemp, Wtemp, Htemp }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine((Rectangle){ Xtemp+padingX, Ytemp, Wtemp, Htemp }, hashTableUsers->users[*actualUser]->info->name, 50, false);
    GuiDrawText(hashTableUsers->users[*actualUser]->mail, (Rectangle){ Xtemp, Ytemp+padingY, Wtemp, Htemp }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 300, 50, 150, 40 }, "Volver al menu")) *page = 2;
		
	EndDrawing();
}

#endif