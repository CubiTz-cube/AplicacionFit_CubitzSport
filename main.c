#include "state.h"
#include "library/userHash.h"
#include "library/activityList.h"

#include "pages/login.h"
#include "pages/register.h"
#include "pages/menu.h"
#include "pages/addActivity.h"
#include "pages/profile.h"
#include "pages/stadistic.h"

#define USERS_AMOUNT 3

int main(){	
	User** usersHash = loadUserHash(USERS_AMOUNT, "data/users.txt");
	if (!usersHash) return -1;
	NodeActivity* activities[ACTIVITY_AMOUNT];
	for (int i = 0; i < ACTIVITY_AMOUNT; i++) activities[i] = NULL;
	loadNodesActivity(activities, "data/activities.txt");

	seeUserHash(usersHash, USERS_AMOUNT);

	seeAllNodesActivity(activities);

	InitWindow(1280, 720, "OLP-76");
	SetTargetFPS(60);
    
    Font fontLekton = LoadFont("public/fonts/Lekton-Regular.ttf");
    Font fontAldrich = LoadFont("public/fonts/Aldrich-Regular.ttf");

    int page = 3;
	while (!WindowShouldClose())
	{   
        if (page == 0) layer_login(&page, &fontLekton, &fontAldrich);
        else if (page == 1) layer_register(&page, &fontLekton, &fontAldrich);
        else if (page == 2) layer_menu(&page, &fontLekton, &fontAldrich);
		else if (page == 3) layer_addActivity(&page, &fontLekton, &fontAldrich);
		else if (page == 4) layer_profile(&page, &fontLekton, &fontAldrich);
		else if (page == 5) layer_stadistic(&page, &fontLekton, &fontAldrich);
				
		//GuiFloatBox((Rectangle){ 55, 40, 135, 20 }, "= ", &result, -2000000.0, 2000000.0, false);
	}

	UnloadFont(fontLekton);
	UnloadFont(fontAldrich);

	saveNodesActivity(activities, "data/activities.txt");
	saveUserHash(usersHash, USERS_AMOUNT, "data/users.txt");

	freeAllNodesActivity(activities);
	freeUserHash(usersHash, USERS_AMOUNT);
	//CloseWindow();
}