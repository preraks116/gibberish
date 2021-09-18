#include "main.h"

struct processNode
{
    char processname[MAX]; 
    int pid; 
    Ptrprocessnode next;
};

Ptrprocessnode InitProcessNode() 
{
    Ptrprocessnode P = (Ptrprocessnode)malloc(sizeof(processnode));
    P->pid = 0;
    P->next = NULL;
    return P;
}

void extcmd(char* command)
{
    int bg = 0;
    if(strchr(command,'&')){bg = 1;}
    char* token = strtok(command, " \t");
    char* args[MAX] = {NULL};
    char com[MAX];
    strcpy(com,token);
    int i = 0;
    while(token != NULL)
    {   
        args[i] = malloc(MAX);
        if(strcmp(token,"&") != 0)
        {
            strcpy(args[i],token);
        }
        i++;
        
        token = strtok(NULL, " \t");
    }
    if(strcmp(args[i-1],"") == 0){args[i-1] = NULL;}
    int forkReturn = fork();
    if(forkReturn < 0)
    {
        perror("fork failed");
        return;
    }
    

    if(forkReturn == 0)
    {
        setpgid(0, 0);
        int q = execvp(com,args);
        if(q == -1)
        {
            printf("error : command not found\n");
        }
    }
    else
    {
        int r = 0;
        if(bg == 0)
        {
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, forkReturn);
            waitpid(forkReturn,&r,WUNTRACED);
            tcsetpgrp(0, getpgrp());
            signal(SIGTTOU, SIG_DFL);
        }
        else
        {
            Ptrprocessnode P = InitProcessNode();
            Ptrprocessnode Q = header;
            while(Q->next != NULL)
            {
                Q = Q->next;
            }
            strcpy(P->processname,com);
            P->pid = forkReturn;
            Q->next = P;
            printf("%d\n",forkReturn);
        }
    }
}