#ifndef PAGECONFIG_H

// Importar las librerias necesarias
#include "library/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "library/raygui.h"

// Definir las constantes globales
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define ACTIVITY_AMOUNT 3

#define PAGECONFIG_H

// Definir Interfaces Custom

// Igual que el textInput pero en linea
void GuiTextInputLine(Rectangle bounds, char *text, int textMaxSize, bool *secretViewActive)
{
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
    static bool textEditMode = false;

    int result = -1;

    int messageInputHeight = (int)bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - GuiGetStyle(STATUSBAR, BORDER_WIDTH);

    Rectangle textBoxBounds = { 0 };
    textBoxBounds.x = bounds.x;
    textBoxBounds.y = bounds.y;
    textBoxBounds.width = bounds.width;
    textBoxBounds.height = bounds.height;

    if (secretViewActive != NULL)
    {
        static char stars[] = "****************";
        if (GuiTextBox(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x, textBoxBounds.y, textBoxBounds.width - 4 - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.height },
            ((*secretViewActive == 1) || textEditMode)? text : stars, textMaxSize, textEditMode)) textEditMode = !textEditMode;

        GuiToggle(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x + textBoxBounds.width - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.y, RAYGUI_TEXTINPUTBOX_HEIGHT, RAYGUI_TEXTINPUTBOX_HEIGHT }, (*secretViewActive == 1)? "#44#" : "#45#", secretViewActive);
    }
    else
    {
        if (GuiTextBox(textBoxBounds, text, textMaxSize, textEditMode)) textEditMode = !textEditMode;
    }

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditMode = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
}

void GuiTextInputLineInt(Rectangle bounds, int *changeInt, int textMaxSize, bool *secretViewActive){
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
    static bool textEditMode = false;

    int result = -1;

    int messageInputHeight = (int)bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - GuiGetStyle(STATUSBAR, BORDER_WIDTH);

    Rectangle textBoxBounds = { 0 };
    textBoxBounds.x = bounds.x;
    textBoxBounds.y = bounds.y;
    textBoxBounds.width = bounds.width;
    textBoxBounds.height = bounds.height;
    
    char textStr[100] = {0};
    sprintf(textStr, "%d", *changeInt);

    if (secretViewActive != NULL)
    {
        static char stars[] = "****************";
        if (GuiTextBox(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x, textBoxBounds.y, textBoxBounds.width - 4 - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.height },
            ((*secretViewActive == 1) || textEditMode)? textStr : stars, textMaxSize, textEditMode)) textEditMode = !textEditMode;

        GuiToggle(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x + textBoxBounds.width - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.y, RAYGUI_TEXTINPUTBOX_HEIGHT, RAYGUI_TEXTINPUTBOX_HEIGHT }, (*secretViewActive == 1)? "#44#" : "#45#", secretViewActive);
    }
    else
    {
        if (GuiTextBox(textBoxBounds, textStr, textMaxSize, textEditMode)) textEditMode = !textEditMode;
    }

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditMode = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
    *changeInt = atoi(textStr);
}
void GuiTextInputLineInt2(Rectangle bounds, int *changeInt, int textMaxSize, bool *secretViewActive){
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
    static bool textEditMode = false;

    int result = -1;

    int messageInputHeight = (int)bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - GuiGetStyle(STATUSBAR, BORDER_WIDTH);

    Rectangle textBoxBounds = { 0 };
    textBoxBounds.x = bounds.x;
    textBoxBounds.y = bounds.y;
    textBoxBounds.width = bounds.width;
    textBoxBounds.height = bounds.height;
    
    char textStr[100] = {0};
    sprintf(textStr, "%d", *changeInt);

    if (secretViewActive != NULL)
    {
        static char stars[] = "****************";
        if (GuiTextBox(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x, textBoxBounds.y, textBoxBounds.width - 4 - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.height },
            ((*secretViewActive == 1) || textEditMode)? textStr : stars, textMaxSize, textEditMode)) textEditMode = !textEditMode;

        GuiToggle(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x + textBoxBounds.width - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.y, RAYGUI_TEXTINPUTBOX_HEIGHT, RAYGUI_TEXTINPUTBOX_HEIGHT }, (*secretViewActive == 1)? "#44#" : "#45#", secretViewActive);
    }
    else
    {
        if (GuiTextBox(textBoxBounds, textStr, textMaxSize, textEditMode)) textEditMode = !textEditMode;
    }

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditMode = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
    *changeInt = atoi(textStr);
}

void GuiTextInputLineFloat(Rectangle bounds, float *changeFloat, int textMaxSize, bool *secretViewActive){
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
    static bool textEditMode = false;

    int result = -1;

    int messageInputHeight = (int)bounds.height - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - GuiGetStyle(STATUSBAR, BORDER_WIDTH);

    Rectangle textBoxBounds = { 0 };
    textBoxBounds.x = bounds.x;
    textBoxBounds.y = bounds.y;
    textBoxBounds.width = bounds.width;
    textBoxBounds.height = bounds.height;
    
    char textStr[100] = {0};
    sprintf(textStr, "%f", *changeFloat);

    if (secretViewActive != NULL)
    {
        static char stars[] = "****************";
        if (GuiTextBox(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x, textBoxBounds.y, textBoxBounds.width - 4 - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.height },
            ((*secretViewActive == 1) || textEditMode)? textStr : stars, textMaxSize, textEditMode)) textEditMode = !textEditMode;

        GuiToggle(RAYGUI_CLITERAL(Rectangle){ textBoxBounds.x + textBoxBounds.width - RAYGUI_TEXTINPUTBOX_HEIGHT, textBoxBounds.y, RAYGUI_TEXTINPUTBOX_HEIGHT, RAYGUI_TEXTINPUTBOX_HEIGHT }, (*secretViewActive == 1)? "#44#" : "#45#", secretViewActive);
    }
    else
    {
        if (GuiTextBox(textBoxBounds, textStr, textMaxSize, textEditMode)) textEditMode = !textEditMode;
    }

    int prevBtnTextAlignment = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (result >= 0) textEditMode = false;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, prevBtnTextAlignment);
    *changeFloat = atof(textStr);
}

#endif