#ifndef INTRO_H
#define INTRO_H

#include "../state.h"

void layer_intro(int* page, Texture logoColor){
    static int counter = 0;

    BeginDrawing();
	ClearBackground(RAYWHITE);

    float opacity = (counter / 200.0);
    Color tint = Fade(WHITE, opacity);
    Rectangle sourceRec = { 0.0f, 0.0f, (float)logoColor.width, (float)logoColor.height };
    Rectangle destRec = { 390.0f, 110.0f, (float)logoColor.width, (float)logoColor.height };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(logoColor, sourceRec, destRec, origin, 0.0f, tint);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        *page = 0;
    }
    
    if (counter > 270){
        *page = 0;
    }

    counter++;
	EndDrawing();
}

#endif