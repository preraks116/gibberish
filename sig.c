#include "main.h"

void sigcmd(char* command)
{
    Ptrprocessnode Q = header;
    int jobno, signo;
    char* temp;
    char* token = strtok_r(command, " \t", &temp);
    token = strtok_r(NULL, " \t", &temp);
    if(token == NULL){printf("error: job number not specified\n");return;}
    jobno = atoi(token);
    token = strtok_r(NULL, " \t", &temp);
    if(token == NULL){printf("error: signal number not specified\n");return;}
    signo = atoi(token);
    while(Q->next != NULL)
    {
        Q = Q->next;
        if (Q->jobno == jobno)
        {
            // printf("%d\n",Q->pid);
            kill(Q->pid,signo);
            return;
        }
    }
    printf("error: job number specified does not exist\n");
    
}