/*
Ordenar listas enlazadas de actividades de usuario de mayor a menor y viceversa (Lista de actividades de un usuario)
*/

#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>
#include "structs.h"
#include "activityList.h"

//Recorre el struct hasta que el usuario sea el indicado y luego ordena la lista enlazada de actividades
NodeActivity* filterActivitiesByUser(NodeActivity* activities[ACTIVITY_AMOUNT], int userId)
{
    NodeActivity* head = NULL;
    for (int i = 0; i < ACTIVITY_AMOUNT; i++)
    {
        if (!activities[i]) continue;
        NodeActivity* aux = activities[i];
        while (aux)
        {
            if (aux->userId == userId)
            {
                addNodeActivity(&head, aux->userId, aux->duration, aux->date, aux->distance, aux->calories, aux->type);
            }
            aux = aux->next;
        }
    }
    return head;
}


#endif