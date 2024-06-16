#include "state.h"

#include "pages/login.h"
#include "pages/menu.h"

int main()
{
	InitWindow(1280, 720, "OLP-76");
	SetTargetFPS(60);
    
    Font fontLekton = LoadFont("public/fonts/Lekton-Regular.ttf");
    Font fontAldrich = LoadFont("public/fonts/Aldrich-Regular.ttf");

    int page = 0;

	while (!WindowShouldClose())
	{   
        if (page == 0) layer_login(&page, &fontLekton, &fontAldrich);
        else if (page == 1) layer_menu(&page, &fontLekton, &fontAldrich);

		/*BeginDrawing();

		ClearBackground(RAYWHITE);
        
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        GuiSetFont(LoadFont("public/fonts/Aldrich-Regular.ttf"));
        GuiDrawText("CubiTz", (Rectangle){ 500, 10, 100, 120 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
		
		GuiFloatBox((Rectangle){ 55, 40, 135, 20 }, "= ", &result, -2000000.0, 2000000.0, false);
		
		EndDrawing();*/
	}

	CloseWindow();
}