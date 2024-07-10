#ifndef LOGIN_H
#define LOGIN_H

#include "../state.h"

int validarLogin(HashTable* hashTable,char* mail, char* password){
    if (mail[0] == '\0' || password[0] == '\0'){ 
        printf("mail vacio\n");
        return -1;
    }
    int user = searchHashTable(hashTable, mail);
    if (user == -1){ 
        printf("mail no encontrado\n");
        return -2;
    }
    else if (strcmp(hashTable->users[user]->password, password) == 0){
        printf("login exitoso\n");
        return user;
    }
    printf("contrasena incorrecta %d\n" ,strcmp(hashTable->users[user]->password, password));
    return -3;
}

void layer_login(int* page, Font* fontLekton, Font* fontAldrich, int* actualUser, HashTable* hashTableUsers){
    static char mail[100] = "";
    static char password[50] = "";
    static char message[100] = "";

    BeginDrawing();
	ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 1280, 50, (Color){ 60, 60, 80, 255 });

    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("Inicio de Sesion", (Rectangle){ 0, 5, 300, 50 }, TEXT_ALIGN_LEFT, (Color){ 255, 255, 255, 255 });

    GuiSetFont(*fontLekton);

    GuiDrawText("Correo: ", (Rectangle){ 0, 100, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine((Rectangle){ 200, 100, 300, 30 }, mail, 100, false);

    GuiDrawText("Contrasena: ", (Rectangle){ 0, 150, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine2((Rectangle){ 200, 150, 300, 30 }, password, 50, false);

    GuiDrawText(message, (Rectangle){ 600, 300, 650, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    GuiSetFont(*fontLekton);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    if (GuiButton((Rectangle){ 800, 100, 250, 80 }, "Comenzar")) {
        int result = validarLogin(hashTableUsers, mail, password);
        if (result >= 0){
            *actualUser = result;
            *page = 2;
        }else if (result == -1){
            strcpy(message, "Faltan campos por rellenar");
        }else if (result == -2){
            strcpy(message, "Correo no encontrado");
        }else if (result == -3){
            strcpy(message, "Contrasena incorrecta");
        }
    }
    if (GuiButton((Rectangle){ 800, 200, 250, 60 }, "Registrarse")) *page = 1;
		
	EndDrawing();
}

#endif