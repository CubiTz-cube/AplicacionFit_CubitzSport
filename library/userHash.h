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

    user->achivement = (Achivement*)malloc(sizeof(Achivement));
    if (!user->achivement){
        free(user->info);
        free(user);
        return NULL;
    }

    return user;
}

User** loadUserHash(int size, char* filaPath){
    User** usersHash = (User**)malloc(size * sizeof(User*));
    if (!usersHash) return NULL;

    for (int i = 0; i < size; i++){
        usersHash[i] = NULL;
    }
    
    FILE* file = fopen(filaPath, "r");
    if (file){
        char line[256];

        while(fgets(line, sizeof(line), file)){
            int i = 0;
            int loadSpace = -1;
            User* addUser = createUser();

            char* token = strtok(line, "|");
            while (token != NULL) {
                printf("%s\n", token);
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
                    for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                        addUser->activities[j] = token[j] - '0';
                    }
                    break;
                case 4:
                    strcpy(addUser->info->name, token);
                    break;
                case 5:
                    addUser->info->old = atoi(token);
                    break;
                case 6:
                    addUser->info->genero = token[0];
                    break;
                case 7:
                    addUser->info->weight = atof(token);
                    break;
                case 8:
                    addUser->info->height = atoi(token);
                    break;
                case 9:
                    for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                        addUser->achivement->recordsDistance[j] = token[j] - '0';
                    }
                    break;
                case 10:
                    for (int j = 0; j < ACTIVITY_AMOUNT; j++){
                        addUser->achivement->recordsDistance[j] = token[j] - '0';
                    }
                    break;
                default:
                    break;
                }
                token = strtok(NULL, "|");
                i++;
            }
            usersHash[loadSpace] = addUser;
        }
    }else{
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    return usersHash;
}

void freeUserHash(User** usersHash, int size){
    for (int i = 0; i < size; i++){
        free(usersHash[i]->achivement);
        free(usersHash[i]->info);
        free(usersHash[i]);
    }
    free(usersHash);
}

#endif