#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "structs.h"

User* createUser(){
    User* user = (User*)malloc(sizeof(User));
    if (!user) return NULL;

    user->info = (InfoUser*)malloc(sizeof(InfoUser));
    if (!user->info){
        free(user);
        return NULL;
    }

    return user;
}

User** loadUserHash(int size, char* filePath){
    User** usersHash = (User**)malloc(size * sizeof(User*));
    if (!usersHash) return NULL;

    for (int i = 0; i < size; i++){
        usersHash[i] = NULL;
    }
    
    FILE* file = fopen(filePath, "r");
    if (!file) {
        printf("Archivo creado: %s\n", filePath);
        fopen(filePath, "w");
        file = fopen(filePath, "r");
    }
    if (file){
        char line[256];

        while(fgets(line, sizeof(line), file)){
            int i = 0;
            int loadSpace = -1;
            User* addUser = createUser();

            char recordDistance[ACTIVITY_AMOUNT*10];
            char recordCalories[ACTIVITY_AMOUNT*10];

            char* token = strtok(line, "|");
            while (token != NULL) {
                switch (i){
                case 0:
                    loadSpace = atoi(token);
                    break;
                case 1:
                    strcpy(addUser->mail, token);
                    break;
                case 2:
                    strcpy(addUser->password, token);
                    break;
                case 3:
                    strcpy(addUser->info->name, token);
                    break;
                case 4:
                    addUser->info->old = atoi(token);
                    break;
                case 5:
                    addUser->info->gender = token[0];
                    break;
                case 6:
                    addUser->info->weight = atof(token);
                    break;
                case 7:
                    addUser->info->height = atoi(token);
                    break;
                case 8:
                    strcpy(recordDistance, token);
                    break;
                case 9:
                    strcpy(recordCalories, token);
                    break;
                default:
                    break;
                }
                token = strtok(NULL, "|");
                i++;
            }
            token = strtok(recordDistance, ",");
            for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                addUser->recordsDistance[j] = atoi(token);
                token = strtok(NULL, ",");
            }

            token = strtok(recordCalories, ",");
            for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                addUser->recordsCalories[j] = atoi(token);
                token = strtok(NULL, ",");
            }
            usersHash[loadSpace] = addUser;
        }
    }else{
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    fclose(file);
    return usersHash;
}

void saveUserHash(User** usersHash, int size, char* filePath){
    FILE* file = fopen(filePath, "w");
    if (file){
        for (int i = 0; i < size; i++){
            if (usersHash[i]){
                fprintf(file, "%d|%s|%s|%s|%d|%c|%f|%d|", 
                i, 
                usersHash[i]->mail, 
                usersHash[i]->password, 
                usersHash[i]->info->name, 
                usersHash[i]->info->old, 
                usersHash[i]->info->gender, 
                usersHash[i]->info->weight, 
                usersHash[i]->info->height);
                for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                    fprintf(file, "%d,", usersHash[i]->recordsDistance[j]);
                }
                fprintf(file, "|");
                for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                    fprintf(file, "%d,", usersHash[i]->recordsCalories[j]);
                }
                fprintf(file, "\n");
            }
        }
    }else{
        printf("Error al abrir el archivo\n");
    }
    fclose(file);
}

void freeUserHash(User** usersHash, int size){
    for (int i = 0; i < size; i++){
        if (usersHash[i]){
            free(usersHash[i]->info);
            free(usersHash[i]);
        }
    }
    free(usersHash);
}

int functionHash(int size, char* mail){
    int hash = 0;
    for (int i = 0; i < strlen(mail); i++){
        hash += mail[i];
    }
    return hash % size;
}

void addUserHash(User** usersHash, int size, User* user){
    int hash = functionHash(size, user->mail);
    if (usersHash[hash]){
        int i = 1;
        while (usersHash[hash]){
            hash = (hash + i) % size;
            i++;
        }
    }
    usersHash[hash] = user;
}

void seeUserHash(User** usersHash, int size){
    for (int i = 0; i < size; i++){
        if (usersHash[i]){
            printf("Espacio: %d\n", i);
            printf("Mail: %s\n", usersHash[i]->mail);
            printf("Password: %s\n", usersHash[i]->password);
            printf("Nombre: %s\n", usersHash[i]->info->name);
            printf("Edad: %d\n", usersHash[i]->info->old);
            printf("Genero: %c\n", usersHash[i]->info->gender);
            printf("Peso: %f\n", usersHash[i]->info->weight);
            printf("Altura: %d\n", usersHash[i]->info->height);
            for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                printf("Distancia %d: %d\n", j, usersHash[i]->recordsDistance[j]);
            }
            for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                printf("Calorias %d: %d\n", j, usersHash[i]->recordsCalories[j]);
            }
        }
    }
}

#endif