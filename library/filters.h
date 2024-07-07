/*
Ordenar listas enlazadas de mayor a menor y viceversa, que tambien se puedan
ordenar entre lapsos de tiempos definidos
*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "userHash.h"
#include "activityList.h"
#include "state.h"

//Funcion para buscar una actividad en la lista enlazada
NodeActivity* searchActivity(NodeActivity* head, int userId) //El type no hace falta ya que se saca de en que posicion del array de listas enlazadas esta
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

//Funcion para comparar dos fechas de usuarios
int compareDates(Date date1, Date date2) 
{
    if ((date1.year < date2.year) || (date1.year == date2.year && date1.month < date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day)) 
    {
        return 1;
    } 
    else if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day) 
    {
        return 0;
    } 
    else 
    {
        return -1;
    }
}

NodeActivity* merge(NodeActivity* left, NodeActivity* right) 
{
    if (left == NULL) 
    {
        return right;
    }
    if (right == NULL) 
    {
        return left;
    }
    
    NodeActivity* result = NULL;
    if (compareDates(left->date, right->date) <= 0) 
    {
        result = left;
        result->next = merge(left->next, right);
    } 
    else 
    {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

void split(NodeActivity* head, NodeActivity** left, NodeActivity** right) 
{
    NodeActivity* slow = head;
    NodeActivity* fast = head->next;
    
    while (fast != NULL) 
    {
        fast = fast->next;
        if (fast != NULL) 
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

NodeActivity* mergeSort(NodeActivity* head) 
{
    if (head == NULL || head->next == NULL) 
    {
        return head;
    }
    
    NodeActivity* left;
    NodeActivity* right;
    
    split(head, &left, &right);
    
    left = mergeSort(left);
    right = mergeSort(right);
    
    return merge(left, right);
}
    
// Función para filtrar y ordenar actividades entre dos fechas.
NodeActivity* filterAndSortActivities(NodeActivity* head, Date startDate, Date endDate) 
{
    NodeActivity* filtered = NULL;
    NodeActivity* current = head;
    NodeActivity* prev = NULL;
    NodeActivity* next = NULL;
    
    // Filtrar actividades que estén dentro del rango de fechas.
    while (current != NULL) 
    {
        next = current->next;
        if (compareDates(current->date, startDate) >= 0 && compareDates(current->date, endDate) <= 0) 
        {
            // Si la actividad está dentro del rango, la añadimos a la lista filtrada.
            current->next = filtered;
            filtered = current;
        }
        current = next;
    }
    
    // Ordenar las actividades filtradas por fecha utilizando el merge sort.
    filtered = mergeSort(filtered);
    
    return filtered;
}

//Filtrar actividades por usuario, devuelve una lista de listas enlazadas de actividades de TODOS los usuarios
NodeActivity* filterActivitiesByUser(NodeActivity* activities[ACTIVITY_AMOUNT], int userID)
{
    NodeActivity* filtered = NULL;
    NodeActivity* current = NULL;
    NodeActivity* prev = NULL;
    NodeActivity* next = NULL;
    
    for (int i = 0; i < ACTIVITY_AMOUNT; i++)
    {
        current = searchActivity(activities[i], userID);
        if (current != NULL)
        {
            next = current->next;
            current->next = filtered;
            filtered = current;
        }
    }
    return filtered;
}