#include "main.h"

void sigcmd(char* command)
{
    Ptrprocessnode Q = header;
    int jobno, signo;
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    if(token == NULL){printf("error: job number not specified\n");return;}
    jobno = atoi(token);
    token = strtok(NULL, " \t");
    if(token == NULL){printf("error: signal number not specified\n");return;}
    signo = atoi(token);
    while(Q->next != NULL)
    {
        Q = Q->next;
        if (Q->jobno == jobno)
        {
            kill(jobno,signo);
            return;
        }
    }
    
}