#ifndef MENU_H
#define MENU_H

#include "../state.h"

void layer_menu(int* page, Font* fontLekton, Font* fontAldrich){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz MENU", (Rectangle){ 500, 10, 300, 220 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 500, 200, 200, 40 }, "Anadir actividad")) *page = 3;
    if (GuiButton((Rectangle){ 500, 250, 200, 40 }, "Perfil")) *page = 4;
    if (GuiButton((Rectangle){ 500, 300, 200, 40 }, "Estadisticas")) *page = 5;
		
	EndDrawing();
}

#endif