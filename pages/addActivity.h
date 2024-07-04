#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H
#include "../state.h"
#include "../library/structs.h"

void GuiTextInputLineTime(Rectangle bounds, Time* times){
    #if !defined(RAYGUI_TEXTINPUTBOX_BUTTON_HEIGHT)
        #define RAYGUI_TEXTINPUTBOX_BUTTON_HEIGHT      24
    #endif
    #if !defined(RAYGUI_TEXTINPUTBOX_BUTTON_PADDING)
        #define RAYGUI_TEXTINPUTBOX_BUTTON_PADDING     12
    #endif
    #if !defined(RAYGUI_TEXTINPUTBOX_HEIGHT)
        #define RAYGUI_TEXTINPUTBOX_HEIGHT             26
    #endif
    // Used to enable text edit mode
    // WARNING: No more than one GuiTextInputBox() should be open at the same time
    static bool textEditModeSeg = false;
    static bool textEditModeMin = false;
    static bool textEditModeHour = false;

    int result = -1;

    int messageInputHeight = (int)bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - GuiGetStyle(STATUSBAR, BORDER_WIDTH);

    Rectangle textBoxBoundsSeg = { 0 };
    textBoxBoundsSeg.x = bounds.x + 2*bounds.width/3;
    textBoxBoundsSeg.y = bounds.y;
    textBoxBoundsSeg.width = bounds.width/3;
    textBoxBoundsSeg.height = bounds.height;
    GuiDrawText("Seg", (Rectangle){ textBoxBoundsSeg.x, textBoxBoundsSeg.y-30, textBoxBoundsSeg.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    Rectangle textBoxBoundsMin = { 0 };
    textBoxBoundsMin.x = bounds.x + bounds.width/3;
    textBoxBoundsMin.y = bounds.y;
    textBoxBoundsMin.width = bounds.width/3;
    textBoxBoundsMin.height = bounds.height;
    GuiDrawText("Min", (Rectangle){ textBoxBoundsMin.x, textBoxBoundsMin.y-30, textBoxBoundsMin.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    Rectangle textBoxBoundsHour = { 0 };
    textBoxBoundsHour.x = bounds.x;
    textBoxBoundsHour.y = bounds.y;
    textBoxBoundsHour.width = bounds.width/3;
    textBoxBoundsHour.height = bounds.height;
    GuiDrawText("Hour", (Rectangle){ textBoxBoundsHour.x, textBoxBoundsHour.y-30, textBoxBoundsHour.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    
    if (GuiValueBox(textBoxBoundsSeg, NULL, &times->second , 0, 60, textEditModeSeg)) textEditModeSeg = !textEditModeSeg;
    if (GuiValueBox(textBoxBoundsMin, NULL, &times->minute, 0, 60, textEditModeMin)) textEditModeMin = !textEditModeMin;
    if (GuiValueBox(textBoxBoundsHour, NULL, &times->hour, 0, 99, textEditModeHour)) textEditModeHour = !textEditModeHour;

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditModeSeg = false;
    if (result >= 0) textEditModeMin = false;
    if (result >= 0) textEditModeHour = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
}

void GuiTextInputLineDate(Rectangle bounds, Date* dates){
    #if !defined(RAYGUI_TEXTINPUTBOX_BUTTON_HEIGHT)
        #define RAYGUI_TEXTINPUTBOX_BUTTON_HEIGHT      24
    #endif
    #if !defined(RAYGUI_TEXTINPUTBOX_BUTTON_PADDING)
        #define RAYGUI_TEXTINPUTBOX_BUTTON_PADDING     12
    #endif
    #if !defined(RAYGUI_TEXTINPUTBOX_HEIGHT)
        #define RAYGUI_TEXTINPUTBOX_HEIGHT             26
    #endif
    // Used to enable text edit mode
    // WARNING: No more than one GuiTextInputBox() should be open at the same time
    static bool textEditModeSeg = false;
    static bool textEditModeMin = false;
    static bool textEditModeHour = false;
    static bool textEditModeDay = false;
    static bool textEditModeMonth = false;
    static bool textEditModeYear = false;

    int result = -1;

    int messageInputHeight = (int)bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - GuiGetStyle(STATUSBAR, BORDER_WIDTH);

    Rectangle textBoxBoundsSeg = { 0 };
    textBoxBoundsSeg.x = bounds.x + 5*bounds.width/6;
    textBoxBoundsSeg.y = bounds.y;
    textBoxBoundsSeg.width = bounds.width/6;
    textBoxBoundsSeg.height = bounds.height;
    GuiDrawText("Seg", (Rectangle){ textBoxBoundsSeg.x, textBoxBoundsSeg.y-30, textBoxBoundsSeg.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    Rectangle textBoxBoundsMin = { 0 };
    textBoxBoundsMin.x = bounds.x + 4*bounds.width/6;
    textBoxBoundsMin.y = bounds.y;
    textBoxBoundsMin.width = bounds.width/6;
    textBoxBoundsMin.height = bounds.height;
    GuiDrawText("Min", (Rectangle){ textBoxBoundsMin.x, textBoxBoundsMin.y-30, textBoxBoundsMin.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    Rectangle textBoxBoundsHour = { 0 };
    textBoxBoundsHour.x = bounds.x + 3*bounds.width/6;
    textBoxBoundsHour.y = bounds.y;
    textBoxBoundsHour.width = bounds.width/6;
    textBoxBoundsHour.height = bounds.height;
    GuiDrawText("Hour", (Rectangle){ textBoxBoundsHour.x, textBoxBoundsHour.y-30, textBoxBoundsHour.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    
    Rectangle textBoxBoundsDay = { 0 };
    textBoxBoundsDay.x = bounds.x + 2*bounds.width/6;
    textBoxBoundsDay.y = bounds.y;
    textBoxBoundsDay.width = bounds.width/6;
    textBoxBoundsDay.height = bounds.height;
    GuiDrawText("Day", (Rectangle){ textBoxBoundsDay.x, textBoxBoundsDay.y-30, textBoxBoundsDay.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    Rectangle textBoxBoundsMonth = { 0 };
    textBoxBoundsMonth.x = bounds.x + 1*bounds.width/6;
    textBoxBoundsMonth.y = bounds.y;
    textBoxBoundsMonth.width = bounds.width/6;
    textBoxBoundsMonth.height = bounds.height;
    GuiDrawText("Month", (Rectangle){ textBoxBoundsMonth.x, textBoxBoundsMonth.y-30, textBoxBoundsMonth.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    Rectangle textBoxBoundsYear = { 0 };
    textBoxBoundsYear.x = bounds.x;
    textBoxBoundsYear.y = bounds.y;
    textBoxBoundsYear.width = bounds.width/6;
    textBoxBoundsYear.height = bounds.height;
    GuiDrawText("Year", (Rectangle){ textBoxBoundsYear.x, textBoxBoundsYear.y-30, textBoxBoundsYear.width, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
    
    if (GuiValueBox(textBoxBoundsSeg, NULL, &dates->second , 0, 31, textEditModeSeg)) textEditModeSeg = !textEditModeSeg;
    if (GuiValueBox(textBoxBoundsMin, NULL, &dates->minute, 0, 12, textEditModeMin)) textEditModeMin = !textEditModeMin;
    if (GuiValueBox(textBoxBoundsHour, NULL, &dates->hour, 0, 24, textEditModeHour)) textEditModeHour = !textEditModeHour;
    if (GuiValueBox(textBoxBoundsDay, NULL, &dates->day, 0, 31, textEditModeDay)) textEditModeDay = !textEditModeDay;
    if (GuiValueBox(textBoxBoundsMonth, NULL, &dates->month, 0, 12, textEditModeMonth)) textEditModeMonth = !textEditModeMonth;
    if (GuiValueBox(textBoxBoundsYear, NULL, &dates->year, 0, 4000, textEditModeYear)) textEditModeYear = !textEditModeYear;

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditModeSeg = false;
    if (result >= 0) textEditModeMin = false;
    if (result >= 0) textEditModeHour = false;
    if (result >= 0) textEditModeDay = false;
    if (result >= 0) textEditModeMonth = false;
    if (result >= 0) textEditModeYear = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
}

void layer_addActivity(int* page, Font* fontLekton, Font* fontAldrich, int actualUser, HashTable* hashTableUsers, NodeActivity* activities[ACTIVITY_AMOUNT]){
    static int distance = 0;
    static int calories = 0;
    static int activitySelect = 0;
    static Time time = {0, 0, 0};
    static Date date = {0, 0, 0, 0, 0, 0};
    static char message[50] = "";

    BeginDrawing();

	ClearBackground(RAYWHITE);
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 32);
    GuiDrawText("CubiTz Anadir \nactividad", (Rectangle){ 0, 0, 400, 100 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 15);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 300, 50, 150, 40 }, "Volver al menu")) {
        *page = 2;
        distance = -1;
        calories = 0;
        activitySelect = 0;
        time = (Time){0, 0, 0};
        date = (Date){0, 0, 0, 0, 0, 0};
        strcpy(message, "");
    }
    if (GuiButton((Rectangle){ 600, 120+50*5, 200, 60 }, "Agregar")){
        if ((distance == 0 && (activitySelect == 0 || activitySelect == 2 || activitySelect == 4 || activitySelect == 9)) || (time.hour == 0 && time.minute == 0 && time.second == 0) || date.day == 0 || date.month == 0 || date.year == 0){
            strcpy(message, "Faltan campos por llenar");
        }else{
            int met[ACTIVITY_AMOUNT] = ACTIVITY_METS;
            calories = (int)(0.0175 * met[activitySelect] * hashTableUsers->users[actualUser]->info->weight)*(time.hour*60 + time.minute);

            if (distance > hashTableUsers->users[actualUser]->recordsDistance[activitySelect]){
                hashTableUsers->users[actualUser]->recordsDistance[activitySelect] = distance;
            }
            if (calories > hashTableUsers->users[actualUser]->recordsCalories[activitySelect]){
                hashTableUsers->users[actualUser]->recordsCalories[activitySelect] = calories;
            }

            addNodeActivity(&activities[activitySelect], actualUser, time, date, distance, calories, activitySelect);
            strcpy(message, "Actividad agregada");
        }
    }

    GuiDrawText(message, (Rectangle){ 600, 120+80*5, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    // Input para la actividad
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

    GuiDrawText("Actividad: ", (Rectangle){ 0, 120, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiDropdownBoxEdit((Rectangle){ 300, 120, 300, 30 }, ACTIVITY_NAMES, &activitySelect);

    GuiDrawText("Fecha y hora de inicio: ", (Rectangle){ 0, 120+80, 500, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiDrawText("Tiempo de duracion: ", (Rectangle){ 0, 120+80*2, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    if (activitySelect == 0 || activitySelect == 2 || activitySelect == 4 || activitySelect == 9){
        GuiDrawText("Distacia (m): ", (Rectangle){ 0, 120+80*3, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
        GuiTextInputLineInt2((Rectangle){ 250, 120+80*3, 300, 30 }, &distance, 20000);
    }else distance = 0;
    
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiTextInputLineDate((Rectangle){ 400, 120+80, 600, 30 }, &date);
    GuiTextInputLineTime((Rectangle){ 400, 120+80*2, 300, 30 }, &time);

	EndDrawing();
}

#endif