#ifndef LOGIN_H
#define LOGIN_H

#include "../state.h"

void layer_login(int* page, Font* fontLekton, Font* fontAldrich){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz LOGIN", (Rectangle){ 500, 10, 300, 220 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 500, 200, 100, 40 }, "Menu")) *page = 1;
		
	EndDrawing();
}

#endif