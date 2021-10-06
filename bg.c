#include "main.h"
//function to send foreground process to background

void bgcmd(char* command)
{
    Ptrprocessnode Q = header;
    int jobno=0;
	char *token;
    char* temp;
	token = strtok_r(command, " \t", &temp);
	token = strtok_r(NULL, " \t", &temp);
    if(token == NULL){printf("error: job number not specified\n");return;}
	jobno = atoi(token);
    while(Q->next != NULL)
    {
        Q = Q->next;
        if (Q->jobno == jobno)
        {
            if(kill(Q->pid, SIGCONT) == 0)
            {
                Q->status = 'R';
                printf("Process %d is now running in the background\n", Q->pid);
                return;
            }
            else
            {
                printf("Error: Process %d not found\n", Q->pid);
                return;
            }
        }
    }
}

