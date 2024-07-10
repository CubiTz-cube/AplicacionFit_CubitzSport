#ifndef REGISTER_H
#define REGISTER_H

#include "../state.h"

int IsmailDuplicate(HashTable* hashTable,char* mail){
    if (mail[0] == '\0') {
        return -1;
    }
    if (searchHashTable(hashTable, mail) == -1){ 
        return false;
    }else{
        return true;
    }
}

void layer_register(int* page, Font* fontLekton, Font* fontAldrich, int* actualUser, HashTable* hashTableUsers){
    static char mail[100] = "";
    static char password[50] = "";
    static char name[50] = "";
    static int old = 0;
    static int gender = 0;
    static float weight = 0.0;
    static int height = 0;
    static char message[100] = "";
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, 1280, 50, (Color){ 60, 60, 80, 255 });

    GuiSetFont(*fontAldrich);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiDrawText("Registro", (Rectangle){ 0, 5, 400, 50 }, TEXT_ALIGN_LEFT, (Color){ 255, 255, 255, 255 });

    GuiSetFont(*fontLekton);

    GuiDrawText("Correo: ", (Rectangle){ 0, 100, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine((Rectangle){ 200, 100, 300, 30 }, mail, 100, false);

    GuiDrawText("Contrasena: ", (Rectangle){ 0, 150, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine2((Rectangle){ 200, 150, 300, 30 }, password, 100, false);

    GuiDrawText("Nombre: ", (Rectangle){ 0,250, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLine3((Rectangle){ 200, 250, 300, 30 }, name, 50, false);

    GuiDrawText("Edad: ", (Rectangle){ 0, 300, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineInt((Rectangle){ 200, 300, 300, 30 }, &old, 200);

    GuiDrawText("Genero: ", (Rectangle){ 0, 350, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiComboBox((Rectangle){ 200, 350, 300, 30 }, "Masculino;Femenino", &gender);

    GuiDrawText("Peso: ", (Rectangle){ 0,400, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineFloat((Rectangle){ 200, 400, 300, 30 }, &weight,500);

    GuiDrawText("Altura: ", (Rectangle){ 0,450, 300, 30 }, TEXT_ALIGN_LEFT, (Color){ 0, 0, 0, 255 });
    GuiTextInputLineInt2((Rectangle){ 200, 450, 300, 30 }, &height, 500);

    GuiDrawText(message, (Rectangle){ 600, 300, 650, 30 }, TEXT_ALIGN_CENTER, (Color){ 0, 0, 0, 255 });

    if (GuiButton((Rectangle){ 800, 100, 250, 80 }, "Comenzar")) {
        int mailDuplicate = IsmailDuplicate(hashTableUsers,mail);
        printf("mailDuplicate: %d mail %s password %s name %s old %d weight %f height %d\n",mailDuplicate,mail,password,name,old,weight,height);
        if(mailDuplicate == 0 && mail[0] != '\0' && password[0] != '\0' && name[0] != '\0' && old > 0 && weight > 0 && height > 0){
            printf("Usuario creado\n");
            User* usuario = createUser();
            strcpy(usuario->mail, mail);
            strcpy(usuario->password, password);
            strcpy(usuario->info->name, name);
            usuario->info->old = old;
            usuario->info->height = height;
            usuario->info->weight = weight;
            if (gender == 0) usuario->info->gender = 'm';
            else usuario->info->gender = 'f';

            *actualUser = addHashTable(hashTableUsers,USERS_AMOUNT, usuario);
            if (*actualUser == -1){
                strcpy(message,"Tabla de usuario llena");
            }else{
                *page = 2;
            }

        }else if (mailDuplicate == 1){
            strcpy(message,"Usuario ya existe");
        }else{
            strcpy(message,"Faltan campos por rellenar");
        }
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    if (GuiButton((Rectangle){ 800, 200, 250, 60 }, "Inicio de Sesion")) *page = 0;
    
  EndDrawing();
}

#endif