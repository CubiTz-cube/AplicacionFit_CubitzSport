#include "state.h"
#include "library/userHash.h"
#include "library/activityList.h"

#include "pages/login.h"
#include "pages/register.h"
#include "pages/menu.h"

int main(){	
	User** usersHash = loadUserHash(3, "data/users.txt");

	NodeActivity* voleyH = NULL;

	Time duration = {1, 30, 0};
	Time startTime = {10, 0, 0};

	addNodeActivity(&voleyH, 0, duration, startTime, 1000, 500);
	addNodeActivity(&voleyH, 0, duration, startTime, 1000, 600);
	addNodeActivity(&voleyH, 0, duration, startTime, 1000, 900);
	addNodeActivity(&voleyH, 0, duration, startTime, 1000, 100);
	
	printNodesActivity(voleyH);

	freeNodesActivity(&voleyH);

	return 0;

	InitWindow(1280, 720, "OLP-76");
	SetTargetFPS(60);
    
    Font fontLekton = LoadFont("public/fonts/Lekton-Regular.ttf");
    Font fontAldrich = LoadFont("public/fonts/Aldrich-Regular.ttf");

    int page = 0;

	while (!WindowShouldClose())
	{   
        if (page == 0) layer_login(&page, &fontLekton, &fontAldrich);
        else if (page == 1) layer_register(&page, &fontLekton, &fontAldrich);
        else if (page == 2) layer_menu(&page, &fontLekton, &fontAldrich);

		/*BeginDrawing();

		ClearBackground(RAYWHITE);
        
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        GuiSetFont(LoadFont("public/fonts/Aldrich-Regular.ttf"));
        GuiDrawText("CubiTz", (Rectangle){ 500, 10, 100, 120 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });
		
		GuiFloatBox((Rectangle){ 55, 40, 135, 20 }, "= ", &result, -2000000.0, 2000000.0, false);
		
		EndDrawing();*/
	}

	saveUserHash(usersHash, 3, "data/users.txt");
	freeUserHash(usersHash, 3);
	CloseWindow();
}