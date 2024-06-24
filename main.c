#include "state.h"
#include "library/userHash.h"
#include "library/activityList.h"

#include "pages/login.h"
#include "pages/register.h"
#include "pages/menu.h"

#define USERS_AMOUNT 3

int main(){	
	User** usersHash = loadUserHash(USERS_AMOUNT, "data/users.txt");
	if (!usersHash) return -1;
	NodeActivity* activities[ACTIVITY_AMOUNT];
	for (int i = 0; i < ACTIVITY_AMOUNT; i++) activities[i] = NULL;
	loadNodesActivity(activities, "data/activities.txt");

	printAllNodesActivity(activities);

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

	UnloadFont(fontLekton);
	UnloadFont(fontAldrich);

	saveNodesActivity(activities, "data/activities.txt");
	saveUserHash(usersHash, USERS_AMOUNT, "data/users.txt");

	freeAllNodesActivity(activities);
	freeUserHash(usersHash, USERS_AMOUNT);
	CloseWindow();
}