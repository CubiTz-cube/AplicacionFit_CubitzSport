#ifndef PROFILE_H
#define PROFILE_H
#include "../state.h"

void layer_profile(int* page, Font* fontLekton, Font* fontAldrich, int* actualUser, HashTable* hashTableUsers){
    static int genderSelect = -1;
    if (genderSelect == -1){
        if (hashTableUsers->users[*actualUser]->info->gender == 'm') genderSelect = 0;
        else genderSelect = 1;}
    char BMI[100]; 
    char BFP[100];  

    BeginDrawing();
	ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, 1280, 50, (Color){ 210, 210, 210, 255 });
    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("Perfil", (Rectangle){ 200, 0, 300, 50 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 0, 0, 150, 50 }, "Volver al menu")) *page = 2;
    
    // Input de User Info
    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

    char mail[150]; 
    sprintf(mail, "Correo: %s", hashTableUsers->users[*actualUser]->mail);
    GuiDrawText(mail, (Rectangle){ 0, 120, 400, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    GuiDrawText("Nombre: ", (Rectangle){ 0, 120+50, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine((Rectangle){ 200, 120+50, 300, 30 }, hashTableUsers->users[*actualUser]->info->name, 50, false);

    GuiDrawText("Edad: ", (Rectangle){ 0, 120+50*2, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineInt((Rectangle){ 200, 120+50*2, 300, 30 }, &hashTableUsers->users[*actualUser]->info->old, 150);

    if (genderSelect == 0) {hashTableUsers->users[*actualUser]->info->gender = 'm';}
    else if (genderSelect == 1) hashTableUsers->users[*actualUser]->info->gender = 'f';
    GuiDrawText("Genero: ", (Rectangle){ 0, 120+50*3, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiComboBox((Rectangle){ 200, 120+50*3, 300, 30 }, "Masculino;Femenino", &genderSelect);

    GuiDrawText("Peso: ", (Rectangle){ 0, 120+50*4, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineFloat((Rectangle){ 200, 120+50*4, 300, 30 }, &hashTableUsers->users[*actualUser]->info->weight, 50);

    GuiDrawText("Altura: ", (Rectangle){ 0, 120+50*5, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineInt2((Rectangle){ 200, 120+50*5, 300, 30 }, &hashTableUsers->users[*actualUser]->info->height, 500);

    float resultBMI = hashTableUsers->users[*actualUser]->info->weight / (hashTableUsers->users[*actualUser]->info->height/100.0);
    if (resultBMI > 0)
    hashTableUsers->users[*actualUser]->info->BMI = resultBMI;
    sprintf(BMI, "Indice de masa muscular: %f", hashTableUsers->users[*actualUser]->info->BMI);
    GuiDrawText(BMI, (Rectangle){ 0, 120+50*6, 800, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });

    int resultBFP = 0;
    if (hashTableUsers->users[*actualUser]->info->gender == 'm'){
        resultBFP = 1.2 * hashTableUsers->users[*actualUser]->info->BMI + 0.23 * hashTableUsers->users[*actualUser]->info->old - 10.8 - 5.4;;
        if (resultBFP > 0)
        hashTableUsers->users[*actualUser]->info->BFP = resultBFP;
    }else{
        resultBFP = 1.2 * hashTableUsers->users[*actualUser]->info->BMI + 0.23 * hashTableUsers->users[*actualUser]->info->old - 10.8 * 2 - 5.4;
        if (resultBFP > 0)
        hashTableUsers->users[*actualUser]->info->BFP = resultBFP;
    }
    sprintf(BFP, "Indice de grasa corporal: %d", hashTableUsers->users[*actualUser]->info->BFP);
    GuiDrawText(BFP, (Rectangle){ 0, 120+50*7, 800, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
		
	EndDrawing();
}

#endif