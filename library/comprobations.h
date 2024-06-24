//#include <iostream>
#include <fstream>
#include <string>

int isEmailRegistered(const std::string& email) 
{
    std::ifstream file("users.txt");
    std::string line;
    
    while (std::getline(file, line)) 
    {
        if (line == email) 
        {
            return 1;
        }
    }
    
    return 0;
}

int isStringNumeric(const std::string& str) 
{
    for (char c : str) 
    {
        if (!std::isdigit(c)) 
        {
            return 0;
        }
    }
    
    return 1;
}