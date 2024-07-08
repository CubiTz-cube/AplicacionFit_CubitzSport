/*
Ordenar listas enlazadas de actividades de usuario de mayor a menor y viceversa (Lista de actividades de un usuario)
*/

#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>
#include "structs.h"
#include "activityList.h"

//Funcion para buscar una actividad en la lista enlazada
NodeActivity* searchActivity(NodeActivity* head, int userId)
{
    NodeActivity* current = head;
    while (current != NULL) 
    {
        if (current->userId == userId) 
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//Filtrar actividades por usuario, devuelve una lista de listas enlazadas de actividades de un usuario
NodeActivity* filterActivitiesByUser(NodeActivity* activities[ACTIVITY_AMOUNT], int userID)
{
    NodeActivity* filteredActivities = NULL;
    for (int i = 0; i < ACTIVITY_AMOUNT; i++)
    {
        NodeActivity* activity = searchActivity(activities[i], userID);
        if (activity != NULL)
        {
            NodeActivity* newNode = (NodeActivity*)malloc(sizeof(NodeActivity));
            newNode->userId = activity->userId;
            newNode->type = activity->type;
            newNode->next = NULL;
            if (filteredActivities == NULL)
            {
                filteredActivities = newNode;
            }
            else
            {
                NodeActivity* current = filteredActivities;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }
    return filteredActivities;
}


#endif