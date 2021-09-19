#include "main.h"

void repeatcmd(char* command)
{
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
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
    token = strtok(NULL, " \t");
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
        token = strtok(NULL, " \t");
    }
    for(int i = 0; i < n; i++)
    {
        char temp[MAX] = "";
        strcpy(temp,finalcom);
        getcommand(temp);
    }
}