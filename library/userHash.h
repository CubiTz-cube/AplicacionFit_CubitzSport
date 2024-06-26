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

/*
    Recibe el tamaño de la tabla hash y el mail del usuario.
    Devuelve una posicion en esta en funcial al mail.
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
    Usa createUser para crear el usuario.
*/
void addHashTable(HashTable* hashTable, int size, User* user){
    if (!hashTable) return;
    if (hashTable->amount >= hashTable->max) {
        printf("Maxima cantidad de usuarios alcanzada\n");
        return;
    }

    int hash = functionHash(size, user->mail);
    if (hashTable->users[hash]){
        int i = 1;
        while (hashTable->users[hash]){
            hash = (hash + i) % size;
            i++;
        }
    }
    hashTable->users[hash] = user;
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

#endif