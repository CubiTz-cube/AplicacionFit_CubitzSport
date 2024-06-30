#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H
#include "../state.h"

void layer_addActivity(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, NodeActivity* activities[ACTIVITY_AMOUNT]){
    static int distance = 0;
    static int calories = 0;
    static int activitySelect = 0;
    static int startSeg, startMin, startHour = 0;
    static int durationSeg, durationMin, durationHour = 0;

    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 32);
    GuiDrawText("CubiTz Anadir \nactividad", (Rectangle){ 0, 0, 400, 100 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 300, 50, 150, 40 }, "Volver al menu")) *page = 2;
    if (GuiButton((Rectangle){ 200, 120+50*5, 200, 60 }, "Agregar")){
        addNodeActivity(&activities[activitySelect], actualUser, (Time){durationSeg, durationMin, durationHour}, (Date){0, 0, 0, 0, 0, 0}, distance, calories);
    }

    // Input para la actividad
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

    GuiDrawText("Actividad: ", (Rectangle){ 0, 120, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiDropdownBoxEdit((Rectangle){ 300, 120, 300, 30 }, ACTIVITY_NAMES, &activitySelect);

    GuiDrawText("Fecha y hora de inicio: ", (Rectangle){ 0, 120+50, 500, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    GuiDrawText("Tiempo de duracion: ", (Rectangle){ 0, 120+50*2, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    GuiDrawText("Calorias: ", (Rectangle){ 0, 120+50*3, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineInt((Rectangle){ 200, 120+50*3, 300, 30 }, &calories, 20000);

    GuiDrawText("Distacia: ", (Rectangle){ 0, 120+50*4, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineInt2((Rectangle){ 200, 120+50*4, 300, 30 }, &distance, 20000);
		
	EndDrawing();
}

#endif