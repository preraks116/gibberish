#include "main.h"
//function to send foreground process to background

void bgcmd(char* command)
{
    Ptrprocessnode Q = header;
    int jobno=0;
	char *token;
	token = strtok(command, " \t");
	token = strtok(NULL, " \t");
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
                setpgid(Q->pid, 0);
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(0, Q->pid);
                printf("Process %d is now in the background\n", Q->pid);
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

