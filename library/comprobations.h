#include <stdlib.h>

int isNumeric(const char* str) 
{
    if (str == NULL) 
    {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] < '0' || str[i] > '9') 
        {
            return 0;
        }
    }

    return 1;
}

int mailCheck(const char* str) 
{
    if (str == NULL) 
    {
        return 0;
    }

    int at = 0;
    int dot = 0;

    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] == '@') 
        {
            at++;
        }

        if (str[i] == '.') 
        {
            dot++;
        }
    }

    if (at == 1 && dot >= 1) 
    {
        return 1;
    }

    return 0;
}