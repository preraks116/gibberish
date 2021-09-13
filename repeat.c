#include "main.h"

void repeatcmd(char* command)
{
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    int n = atoi(token);
    // printf("%d\n",n);
    token = strtok(NULL, " \t");
    char finalcom[MAX] = " ";
    while (token != NULL) // prints every token
    {
        // printf("%s ", token);
        strcat(finalcom,token);
        strcat(finalcom," ");
        token = strtok(NULL, " \t");
    }
    // printf("%s\n",finalcom);
    for(int i = 0; i < n; i++)
    {
        char temp[MAX] = "";
        strcpy(temp,finalcom);
        getcommand(temp);
    }
}