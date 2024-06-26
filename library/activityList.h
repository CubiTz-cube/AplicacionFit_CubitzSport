#ifndef LIST_H
#define LIST_H
#include "structs.h"

NodeActivity* createNodeActivity(int userId, Time duration, Time startTime, int distance, int calories){
    NodeActivity* newN = (NodeActivity*)malloc(sizeof(NodeActivity));
    if (!newN) {
        printf("Error: Reservar memoria para el nodo de actividad.\n");
        return NULL;
    }
    newN->userId = userId;
    newN->duration = duration;
    newN->startTime = startTime;
    newN->distance = distance;
    newN->calories = calories;
    newN->next = NULL;

    return newN;
}

void addNodeActivity(NodeActivity** head, int userId, Time duration, Time startTime, int distance, int calories){
    NodeActivity* newN = createNodeActivity(userId, duration, startTime, distance, calories);
    if (!newN) return;

    if (!*head) {
        *head = newN;
        return;
    }

    NodeActivity* aux = *head;
    if (newN->calories < aux->calories) {
        newN->next = aux;
        *head = newN;
        return;
    }

    while (aux->next && newN->calories > aux->next->calories) {
        aux = aux->next;
    }

    if (!aux->next) {
        aux->next = newN;
    } else {
        newN->next = aux->next;
        aux->next = newN;
    }
}

void printNodesActivity(NodeActivity* head){
    NodeActivity* aux = head;
    while (aux) {
        printf("\n");
        printf("Usuario: %d\n", aux->userId);
        printf("Duracion: %d:%d:%d\n", aux->duration.hour, aux->duration.minute, aux->duration.second);
        printf("Inicio: %d:%d:%d\n", aux->startTime.hour, aux->startTime.minute, aux->startTime.second);
        printf("Distancia: %d\n", aux->distance);
        printf("Calorias: %d\n", aux->calories);
        aux = aux->next;
    }
}

void seeAllNodesActivity(NodeActivity** activities){
    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        printf("\n");
        printf("ACTIVITY %d\n", i+1);
        printNodesActivity(activities[i]);
    }
}

void freeNodesActivity(NodeActivity** head){
    while (*head) {
        NodeActivity* aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}

void freeAllNodesActivity(NodeActivity** activities){
    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        freeNodesActivity(&activities[i]);
    }
}

void loadNodesActivity(NodeActivity** activities, char* filePath){
    FILE* file = fopen(filePath, "r");
    if (!file) {
        printf("Archivo creado: %s\n", filePath);
        fopen(filePath, "w");
        file = fopen(filePath, "r");
    }
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s.\n", filePath);
        return;
    }
    int userId, hour, minute, second, distance, calories;
    char duration[20];
    char startTime[20];
    char line[255];

    while (fgets(line, sizeof(line), file)){
        int i = 0;
        int loadSpace = -1;

        char* token = strtok(line, "|");
        while (token) {
            switch (i){
            case 0:
                loadSpace = atoi(token);
                break;
            case 1:
                userId = atoi(token);
                break;
            case 2:
                strcpy(duration, token);
                break;
            case 3:
                strcpy(startTime, token);
                break;
            case 4:
                distance = atoi(token);
                break;
            case 5:
                calories = atoi(token);
                break;
            }
            token = strtok(NULL, "|");
            i++;
        }
        token = strtok(duration, ",");
        hour = atoi(token);
        token = strtok(NULL, ",");
        minute = atoi(token);
        token = strtok(NULL, ",");
        second = atoi(token);
        Time duration = {hour, minute, second};

        token = strtok(startTime, ",");
        hour = atoi(token);
        token = strtok(NULL, ",");
        minute = atoi(token);
        token = strtok(NULL, ",");
        second = atoi(token);
        Time startTime = {hour, minute, second};

        addNodeActivity(&activities[loadSpace], userId, duration, startTime, distance, calories);
    }
    fclose(file);
}

void saveNodesActivity(NodeActivity** activities, char* filePath){
    FILE* file = fopen(filePath, "w");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s.\n", filePath);
        return;
    }

    for (int i = 0; i < ACTIVITY_AMOUNT; i++){
        NodeActivity* aux = activities[i];
        while (aux) {
            fprintf(file, "%d|%d|%d,%d,%d|%d,%d,%d|%d|%d\n", i, aux->userId, aux->duration.hour, aux->duration.minute, aux->duration.second, aux->startTime.hour, aux->startTime.minute, aux->startTime.second, aux->distance, aux->calories);
            aux = aux->next;
        }
    }

    fclose(file);
}

#endif