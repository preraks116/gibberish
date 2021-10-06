#include "main.h"

void repeatcmd(char* command)
{
    char* temp;
    char* token = strtok_r(command, " \t", &temp);
    token = strtok_r(NULL, " \t", &temp);
    if(token == NULL)
    {
        printf("error: too few arguments\n");
        return;
    }

    int n = atoi(token);
    if(n == 0)
    {
        printf("error: invalid argument\n");
        return;
    }
    token = strtok_r(NULL, " \t", &temp);
    if(token == NULL)
    {
        printf("error: too few arguments\n");
        return;
    }
    char finalcom[MAX] = " ";
    while (token != NULL) 
    {
        strcat(finalcom,token);
        strcat(finalcom," ");
        token = strtok_r(NULL, " \t", &temp);
    }
    for(int i = 0; i < n; i++)
    {
        char temp[MAX] = "";
        strcpy(temp,finalcom);
        getcommand(temp);
    }
}