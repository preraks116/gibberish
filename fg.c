#include "main.h"
//function to get background process to foreground
//need to handle case where jobno specified is already in the foreground.
void fgcmd(char* command)
{
    Ptrprocessnode Q = header;
    int jobno=0;
	char *token;
    char* temp;
    int status;
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
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(0, Q->pid);
                Q->status = 'R';
                waitpid(Q->pid, &status, WUNTRACED);
                if(!WIFSTOPPED(status)){removejob(Q->pid);}
                tcsetpgrp(0, getpgrp());
                printf("Process %d is now in the foreground\n", Q->pid);
                signal(SIGTTOU, SIG_DFL);
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
