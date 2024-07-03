#ifndef LIST_H
#define LIST_H
#include "structs.h"

NodeActivity* createNodeActivity(int userId, Time duration, Date date, int distance, int calories){
    NodeActivity* newN = (NodeActivity*)malloc(sizeof(NodeActivity));
    if (!newN) {
        printf("Error: Reservar memoria para el nodo de actividad.\n");
        return NULL;
    }
    newN->userId = userId;
    newN->duration = duration;
    newN->date = date;
    newN->distance = distance;
    newN->calories = calories;
    newN->next = NULL;

    return newN;
}
// Recibe la cabecera de una lista enlazada (No de un array de listas enlazadas) y le agrega un nodo.
void addNodeActivity(NodeActivity** head, int userId, Time duration, Date date, int distance, int calories){
    NodeActivity* newN = createNodeActivity(userId, duration, date, distance, calories);
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
        printf("Inicio: %d:%d:%d %d/%d/%d\n", aux->date.hour, aux->date.minute, aux->date.second, aux->date.day, aux->date.month, aux->date.year);
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
    int userId, year, month, day, hour, minute, second, distance, calories;
    char duration[20];
    char date[20];
    char line[255];

    while (fgets(line, sizeof(line), file)){
        int i = 0;
        int loadSpace = -1;

        char* token = strtok(line, "|");
        while (token) {
            if (strcmp(token, "\n") == 0){
                return;
            }
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
                strcpy(date, token);
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
        second = atoi(token);
        token = strtok(NULL, ",");
        minute = atoi(token);
        token = strtok(NULL, ",");
        hour= atoi(token);
        Time duration = {second, minute, hour};

        token = strtok(date, ",");
        second = atoi(token);
        token = strtok(NULL, ",");
        minute = atoi(token);
        token = strtok(NULL, ",");
        hour = atoi(token);
        token = strtok(NULL, ",");
        day = atoi(token);
        token = strtok(NULL, ",");
        month = atoi(token);
        token = strtok(NULL, ",");
        year = atoi(token);
        Date date = {second, minute, hour, day, month, year};

        addNodeActivity(&activities[loadSpace], userId, duration, date, distance, calories);
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
            fprintf(file, "%d|%d|%d,%d,%d|%d,%d,%d,%d,%d,%d|%d|%d\n", i, aux->duration.second, aux->userId, aux->duration.minute, aux->duration.hour, aux->date.second, aux->date.minute, aux->date.hour, aux->date.day, aux->date.month, aux->date.year, aux->distance, aux->calories);
            aux = aux->next;
        }
    }

    fclose(file);
}

#endif