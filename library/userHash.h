#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "structs.h"

/*
    Reserva la memoria para un usario y devuelve su puntero.
    Se tiene que asinar los valores de los campos de la estructura.
*/
User* createUser(){
    User* user = (User*)malloc(sizeof(User));
    if (!user) return NULL;

    user->info = (InfoUser*)malloc(sizeof(InfoUser));
    if (!user->info){
        free(user);
        return NULL;
    }
    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        user->recordsDistance[i] = 0;
        user->recordsCalories[i] = 0;
    }

    return user;
}

User** loadUsers(int size, char* filePath){
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
                if (strcmp(token, "\n") == 0){
                    return usersHash;
                }
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

            addUser->info->BMI = addUser->info->weight / (addUser->info->height/100.0);

            if (addUser->info->gender == 'm'){
                addUser->info->BFP = 1.2 * addUser->info->BMI + 0.23 * addUser->info->old - 10.8 - 5.4;
            }else{
                addUser->info->BFP = 1.2 * addUser->info->BMI + 0.23 * addUser->info->old - 10.8 * 2 - 5.4;
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

void saveUsers(User** usersHash, int size, char* filePath){
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

HashTable* createHashTable(int max){
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (!hashTable) return NULL;

    hashTable->amount = 0;
    hashTable->max = max;
    return hashTable;
}

void seeHashTable(HashTable* hashTable, int size){
    for (int i = 0; i < size; i++){
        if (hashTable->users[i]){
            printf("Espacio: %d\n", i);
            printf("Mail: %s\n", hashTable->users[i]->mail);
            printf("Password: %s\n", hashTable->users[i]->password);
            printf("Nombre: %s\n", hashTable->users[i]->info->name);
            printf("Edad: %d\n", hashTable->users[i]->info->old);
            printf("Genero: %c\n", hashTable->users[i]->info->gender);
            printf("Peso: %f\n", hashTable->users[i]->info->weight);
            printf("Altura: %d\n", hashTable->users[i]->info->height);
            for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                printf("Distancia %d: %d\n", j, hashTable->users[i]->recordsDistance[j]);
            }
            for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                printf("Calorias %d: %d\n", j, hashTable->users[i]->recordsCalories[j]);
            }
        }
    }
}

void freeHashTable(HashTable* hashTable, int size){
    for (int i = 0; i < size; i++){
        if (hashTable->users[i]){
            free(hashTable->users[i]->info);
            free(hashTable->users[i]);
        }
    }
    free(hashTable->users);
    free(hashTable);
}

int isFullHashTable(HashTable* hashTable){
    if (!hashTable) return -1;
    if (hashTable->amount >= hashTable->max){
        printf("Maxima cantidad de usuarios alcanzada\n");
        return 1;
    }
    return 0;
}

/*
    Uso solo dentro de las funciones de hash. No usar de forma idependiente
*/
int functionHash(int size, char* mail){
    int hash = 0;
    for (int i = 0; i < strlen(mail); i++){
        hash += mail[i];
    }
    return hash % size;
}

/*
    Recibe un puntero de estructura usuario con los valores ya asignados.
    Usa createUser para crear el usuario. Retorna la posicion donde lo añadio.
*/
int addHashTable(HashTable* hashTable, int size, User* user){
    if (!hashTable) return -1;
    if (isFullHashTable(hashTable)) return -1;

    int hash = functionHash(size, user->mail);
    if (hashTable->users[hash]){
        int i = 1;
        while (hashTable->users[hash]){
            hash = (hash + i) % size;
            i++;
        }
    }
    hashTable->users[hash] = user;
    return hash;
}

/*
    Recibe el mail del usuario a buscar.
    Devuelve la posicion del usuario en la table de hash.
    Si no se encuentra devuelve -1;
*/
int searchHashTable(HashTable* hashTable, char* mail){
    if (!hashTable) return -2;
    if (!mail) return -2;
    if (mail[0] == '\0') return -2;

    int hash = functionHash(hashTable->max, mail);
    for (int i = 0; i < hashTable->max; i++){
        if (hashTable->users[hash]){
            if (strcmp(hashTable->users[hash]->mail, mail) == 0){
                return hash;
            }
        }
        hash = (hash + 1) % hashTable->max;
    }
    return -1;
}

#endif