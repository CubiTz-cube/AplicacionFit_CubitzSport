#ifndef STADISTIC_H
#define STADISTIC_H
#include "../state.h"

void layer_stadistic(int* page, Font* fontLekton, Font* fontAldrich){
    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("CubiTz Estadisticas", (Rectangle){ 500, 10, 400, 220 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 500, 200, 150, 40 }, "Volver al menu")) *page = 2;

    
		
	EndDrawing();
}

#endif