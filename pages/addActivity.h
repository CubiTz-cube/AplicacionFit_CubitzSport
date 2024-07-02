#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H
#include "../state.h"
#include "../library/structs.h"

void GuiTextInputLineTime(Rectangle bounds, Time* times, int intMaxSize){
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
    textBoxBoundsSeg.x = bounds.x;
    textBoxBoundsSeg.y = bounds.y;
    textBoxBoundsSeg.width = bounds.width/3;
    textBoxBoundsSeg.height = bounds.height;
    Rectangle textBoxBoundsMin = { 0 };
    textBoxBoundsMin.x = bounds.x + bounds.width/3;
    textBoxBoundsMin.y = bounds.y;
    textBoxBoundsMin.width = bounds.width/3;
    textBoxBoundsMin.height = bounds.height;
    Rectangle textBoxBoundsHour = { 0 };
    textBoxBoundsHour.x = bounds.x + 2*bounds.width/3;
    textBoxBoundsHour.y = bounds.y;
    textBoxBoundsHour.width = bounds.width/3;
    textBoxBoundsHour.height = bounds.height;
    
    if (GuiValueBox(textBoxBoundsSeg, NULL, times->second , 0, intMaxSize, textEditModeSeg)) textEditModeSeg = !textEditModeSeg;
    if (GuiValueBox(textBoxBoundsMin, NULL, times->minute, 0, intMaxSize, textEditModeMin)) textEditModeMin = !textEditModeMin;
    if (GuiValueBox(textBoxBoundsHour, NULL, times->hour, 0, intMaxSize, textEditModeHour)) textEditModeHour = !textEditModeHour;

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditModeSeg = false;
    if (result >= 0) textEditModeMin = false;
    if (result >= 0) textEditModeHour = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
}

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