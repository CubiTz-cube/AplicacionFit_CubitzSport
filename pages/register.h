#ifndef REGISTER_H
#define REGISTER_H

#include "../state.h"

void layer_register(int* page, Font* fontLekton, Font* fontAldrich){
    static char mail[100];
    static char password[50];
    static char name[50];
    static int old = 0;
    static int gender = 0;
    static float weight = 0;
    static int height = 0;
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz REGISTER", (Rectangle){ 500, 10, 400, 220 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 500, 200, 100, 40 }, "Menu")) *page = 2;
    if (GuiButton((Rectangle){ 500, 250, 100, 40 }, "Login")) *page = 0;

    // Input de User Info
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

    //GuiDrawText("Correo: ", (Rectangle){ 500, 300, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    //GuiTextInputLine((Rectangle){ 700, 300, 300, 30 }, mail, 100, false);

		
	EndDrawing();
}

#endif