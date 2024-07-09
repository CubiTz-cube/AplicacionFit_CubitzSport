#ifndef STADISTIC_H
#define STADISTIC_H
#include "../state.h"
#include "../library/filters.h"

void drawHourActivityUser(int X, int Y, NodeActivity* activitiesUsers){
    int max = 1;
    int hours[24] = {0};
    if (activitiesUsers){
        NodeActivity* aux = activitiesUsers;
        while (aux){
            hours[aux->date.hour]++;
            if (hours[aux->date.hour] > max) max = hours[aux->date.hour];
            aux = aux->next;
        }
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiDrawText("Tus horas de actividades", (Rectangle){ X, Y, 690, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    for (int i = 0; i<24; i++){
        DrawCircle(X+15+30*i, Y+150-hours[i]*(100/max), 2, (Color){ 0, 0, 0, 255 });
        if (i != 0){
            DrawLine(X+15+30*(i-1), Y+150-hours[i-1]*(100/max), X+15+30*i, Y+150-hours[i]*(100/max), (Color){ 0, 0, 0, 255 });
        }

        char text[255];
        sprintf(text, "%d", i+1);
        GuiDrawText(text, (Rectangle){ X+30*i, Y+150, 30, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    }
}

void drawHourActivityGlobal(int X, int Y, NodeActivity* activities[ACTIVITY_AMOUNT]){
    int max = 1;
    int hours[24] = {0};
    for (int i = 0; i<ACTIVITY_AMOUNT; i++){
        if (!activities[i]) continue;
        NodeActivity* aux = activities[i];
        while (aux){
            hours[aux->date.hour]++;
            if (hours[aux->date.hour] > max) max = hours[aux->date.hour];
            aux = aux->next;
        }
    }
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiDrawText("Horas de actividades global", (Rectangle){ X, Y, 690, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    for (int i = 0; i<24; i++){
        DrawCircle(X+15+30*i, Y+150-hours[i]*(100/max), 2, (Color){ 0, 0, 0, 255 });
        if (i != 0){
            DrawLine(X+15+30*(i-1), Y+150-hours[i-1]*(100/max), X+15+30*i, Y+150-hours[i]*(100/max), (Color){ 0, 0, 0, 255 });
        }

        char text[255];
        sprintf(text, "%d", i+1);
        GuiDrawText(text, (Rectangle){ X+30*i, Y+150, 30, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    }

}

void drawMaxRecord(NodeActivity* activities[ACTIVITY_AMOUNT], HashTable* hashTableUsers, int X, int Y){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 18);
    GuiDrawText("Records de Calorias Global", (Rectangle){ X, Y, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    GuiDrawText("Records de Distancia Global", (Rectangle){ X+280, Y, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    char actityNames[50][ACTIVITY_AMOUNT] = ACTIVITY_NAMESARRAY;
    int indexC = 1;
    int indexD = 1;
    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        if (!activities[i]) continue;
        int maxD = 0;
        int userD = 0;

        char text[255];
        sprintf(text, "%s | %d kc\nUsuario: %s", actityNames[i], activities[i]->calories, hashTableUsers->users[activities[i]->userId]->mail);
        GuiDrawText(text, (Rectangle){ X, Y+10 + 40*indexC, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
        indexC++;

        // Calcular distancia maxima
        NodeActivity* aux = activities[i];
        while (aux){
            if (aux->distance > maxD){
                maxD = aux->distance;
                userD = aux->userId;
            }
            aux = aux->next;
        }
        if (maxD != 0){
            char text[255];
            sprintf(text, "%s | %d m\nUsuario: %s", actityNames[i], maxD, hashTableUsers->users[userD]->mail);
            GuiDrawText(text, (Rectangle){ X+280, Y+10 + 40*indexD, 500, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
            indexD++;
        }
    }
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 15);
}

void layer_stadistic(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    BeginDrawing();
	ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 1280, 50, (Color){ 60, 60, 80, 255 });
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("Estadisticas", (Rectangle){ 200, 5, 400, 50 }, TEXT_ALIGN_LEFT, (Color){ 255, 255, 255, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 0, 0, 150, 50 }, "Volver al menu")) *page = 2;

    //Estadisticas
    
    drawMaxRecord(activities, hashTableUsers, 600, 90);

    drawHourActivityGlobal( 0, 90, activities);
    NodeActivity* activitiesUser = filterActivitiesByUser(activities, actualUser);
    drawHourActivityUser( 0, 300, activitiesUser);
	freeNodesActivity(&activitiesUser);

	EndDrawing();
}

#endif