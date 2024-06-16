#ifndef REGISTER_H
#define REGISTER_H

#include "../state.h"

void layer_register(int* page, Font* fontLekton, Font* fontAldrich){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz REGISTER", (Rectangle){ 500, 10, 500, 220 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 500, 200, 100, 40 }, "Login")) *page = 0;
		
	EndDrawing();
}

#endif