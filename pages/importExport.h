#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include "../state.h"
#include "../library/structs.h"
#include "../library/activityList.h"

void layer_importExport(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    static char message[255] = "";
    static char filePath[255] = "";
    BeginDrawing();
    ClearBackground(RAYWHITE);

    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("Importar/Exportar", (Rectangle){ 0, 0, 400, 60 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    //Botones
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

    if (GuiButton((Rectangle){ 300, 50, 150, 40 }, "Volver al menu")){ 
        *page = 2;
        message[0] = '\0';
    }
    if (GuiButton((Rectangle){ 50, 200, 200, 40 }, "Exportar Actividades")) {
        exportNodesActivity(activities[0], "data/export.txt");
        strcpy(message, "Actividades exportadas correctamente");
    }
    if (GuiButton((Rectangle){ 50, 250, 200, 40 }, "Importar Actividades")) {
        if (importNodesActivity(activities, "data/export.txt")) strcpy(message, "Actividades importadas correctamente");
        else strcpy(message, "Error al importar actividades");
    }

    //Inputs

    GuiTextInputLine((Rectangle){ 50, 300, 200, 40 }, filePath, 255, false);

    GuiDrawText(message, (Rectangle){ 600, 120+80*5, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    EndDrawing();
}

#endif