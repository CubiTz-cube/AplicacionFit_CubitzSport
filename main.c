#include "state.h"
#include "library/userHash.h"
#include "library/activityList.h"
#include "library/filters.h"


#include "pages/login.h"
#include "pages/register.h"
#include "pages/menu.h"
#include "pages/addActivity.h"
#include "pages/profile.h"
#include "pages/stadistic.h"
#include "pages/importExport.h"
#include "pages/intro.h"

int main(){	
	HashTable* hashTableUsers = createHashTable(USERS_AMOUNT);
	if (!hashTableUsers) return -1;
	User** usersLoad = loadUsers(USERS_AMOUNT, "data/users.txt");
	if (!usersLoad) return -1;
	hashTableUsers->users = usersLoad;
	
	NodeActivity* activities[ACTIVITY_AMOUNT];
	for (int i = 0; i < ACTIVITY_AMOUNT; i++) activities[i] = NULL;
	loadNodesActivity(activities, "data/activities.txt");
	
	InitWindow(1280, 720, "CubiTz Sports");
	SetTargetFPS(60);
    
	Image logoN = LoadImage("public/images/isotipoColor.png");
	Image logoC = LoadImage("public/images/isotipoColor.png");
	ImageResize(&logoN, 50, 50);
	ImageResize(&logoC, 500, 500);

	Texture2D logoNegro = LoadTextureFromImage(logoN);
	Texture2D logoColor = LoadTextureFromImage(logoC);
	UnloadImage(logoN);
	UnloadImage(logoC);

    Font fontLekton = LoadFont("public/fonts/Lekton-Regular.ttf");
    Font fontAldrich = LoadFont("public/fonts/Aldrich-Regular.ttf");
	int actualUser = 1;
	
    int page = 7;
	while (!WindowShouldClose())
	{   
        if (page == 0) layer_login(&page, &fontLekton, &fontAldrich, &actualUser, hashTableUsers);
        else if (page == 1) layer_register(&page, &fontLekton, &fontAldrich, &actualUser, hashTableUsers);
        else if (page == 2) layer_menu(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities, logoNegro);
		else if (page == 3) layer_addActivity(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
		else if (page == 4) layer_profile(&page, &fontLekton, &fontAldrich, &actualUser, hashTableUsers);
		else if (page == 5) layer_stadistic(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
		else if (page == 6) layer_importExport(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
		else if (page == 7) layer_intro(&page, logoColor);
	}

	UnloadFont(fontLekton);
	UnloadFont(fontAldrich);
	UnloadTexture(logoNegro);
	UnloadTexture(logoColor);

	saveNodesActivity(activities, "data/activities.txt");
	saveUsers(hashTableUsers->users, USERS_AMOUNT, "data/users.txt");

	freeAllNodesActivity(activities);
	freeHashTable(hashTableUsers, USERS_AMOUNT);
	CloseWindow();
}