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
        printf("Actividad\n");
        printf("Usuario: %d\n", aux->userId);
        printf("Duracion: %d:%d:%d\n", aux->duration.hour, aux->duration.minute, aux->duration.second);
        printf("Inicio: %d:%d:%d\n", aux->startTime.hour, aux->startTime.minute, aux->startTime.second);
        printf("Distancia: %d\n", aux->distance);
        printf("Calorias: %d\n", aux->calories);
        aux = aux->next;
    }
}

void freeNodesActivity(NodeActivity** head){
    while (*head) {
        NodeActivity* aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}

#endif