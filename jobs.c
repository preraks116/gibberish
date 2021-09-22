#include "main.h"

void jobscmd(char* command)
{
    int flagR = 0, flagS = 0; 
    char *token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    if(token == NULL)
    {
        flagS = 1;
        flagR = 1;
    }
    else if(strcmp(token,"-r") == 0)
    {
        flagR = 1;
    }
    else if(strcmp(token,"-s") == 0)
    {
        flagS = 1;
    }
    Ptrprocessnode X = header->next;
    while(X != NULL)
    {
        if(flagR == 1 && X->status == 'R')
        {
            printf("[%d] ",X->jobno);
            printf("Running ");
            printf("%s ",X->processcommand);
            printf("[%d]\n",X->pid);
        }
        else if(flagS == 1 && X->status == 'S')
        {
            printf("[%d] ",X->jobno);
            printf("Stopped ");
            printf("%s ",X->processcommand);
            printf("[%d]\n",X->pid);
        }
        X = X->next;
    }
}
