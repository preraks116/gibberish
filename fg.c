#include "main.h"
//function to get background process to foreground
//need to handle case where jobno specified is already in the foreground.
void fgcmd(char* command)
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
                printf("Process %d is now in the foreground\n", Q->pid);
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
