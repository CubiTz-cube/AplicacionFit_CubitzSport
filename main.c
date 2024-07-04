#include "state.h"
#include "library/userHash.h"
#include "library/activityList.h"

#include "pages/login.h"
#include "pages/register.h"
#include "pages/menu.h"
#include "pages/addActivity.h"
#include "pages/profile.h"
#include "pages/stadistic.h"
#include "pages/importExport.h"

int main(){	
	HashTable* hashTableUsers = createHashTable(USERS_AMOUNT);
	if (!hashTableUsers) return -1;
	User** usersLoad = loadUsers(USERS_AMOUNT, "data/users.txt");
	if (!usersLoad) return -1;
	hashTableUsers->users = usersLoad;
	
	NodeActivity* activities[ACTIVITY_AMOUNT];
	for (int i = 0; i < ACTIVITY_AMOUNT; i++) activities[i] = NULL;
	loadNodesActivity(activities, "data/activities.txt");

	seeHashTable(hashTableUsers, USERS_AMOUNT);

	seeAllNodesActivity(activities);

	InitWindow(1280, 720, "OLP-76");
	SetTargetFPS(60);
    
    Font fontLekton = LoadFont("public/fonts/Lekton-Regular.ttf");
    Font fontAldrich = LoadFont("public/fonts/Aldrich-Regular.ttf");
	int actualUser = 1;//-1;
	
    int page = 6;
	while (!WindowShouldClose())
	{   
        if (page == 0) layer_login(&page, &fontLekton, &fontAldrich);
        else if (page == 1) layer_register(&page, &fontLekton, &fontAldrich);
        else if (page == 2) layer_menu(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
		else if (page == 3) layer_addActivity(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
		else if (page == 4) layer_profile(&page, &fontLekton, &fontAldrich, &actualUser, hashTableUsers);
		else if (page == 5) layer_stadistic(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
		else if (page == 6) layer_importExport(&page, &fontLekton, &fontAldrich, actualUser, hashTableUsers, activities);
	}

	UnloadFont(fontLekton);
	UnloadFont(fontAldrich);

	saveNodesActivity(activities, "data/activities.txt");
	saveUsers(hashTableUsers->users, USERS_AMOUNT, "data/users.txt");

	freeAllNodesActivity(activities);
	freeHashTable(hashTableUsers, USERS_AMOUNT);
	CloseWindow();
}