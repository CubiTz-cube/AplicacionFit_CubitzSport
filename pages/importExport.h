#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include "../state.h"

void layer_importExport(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    static char message[255] = "";
    static char filePath[255] = "";
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, 1280, 50, (Color){ 60, 60, 80, 255 });
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("Importar/Exportar", (Rectangle){ 200, 5, 400, 50 }, TEXT_ALIGN_LEFT, (Color){ 255, 255, 255, 255 });

    //Botones
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

    if (GuiButton((Rectangle){ 0, 0, 150, 50 }, "Volver al menu")){ 
        *page = 2;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 50, 200, 200, 40 }, "Exportar Actividades")) {
        if (exportNodesActivity(activities[0], "data/export.txt")){
            strcpy(message, "Actividades exportadas correctamente");
        }else{
            strcpy(message, "Error al exportar actividades");
        }
    }
    if (GuiButton((Rectangle){ 50, 250, 200, 40 }, "Importar Actividades")) {
        if (importNodesActivity(activities, filePath)) strcpy(message, "Actividades importadas correctamente");
        else strcpy(message, "Error al importar actividades");
    }

    //Inputs

    GuiTextInputLine((Rectangle){ 50, 300, 200, 40 }, filePath, 255, false);

    GuiDrawText(message, (Rectangle){ 600, 120+80*5, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    EndDrawing();
}

#endif