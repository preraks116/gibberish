#include "main.h"


int jobIndex = 0;

struct processNode
{
    char processcommand[MAX];
    int jobno;
    char processname[MAX]; 
    int pid; 
    char status;
    Ptrprocessnode next;
};

Ptrprocessnode InitProcessNode() 
{
    Ptrprocessnode P = (Ptrprocessnode)malloc(sizeof(processnode));
    P->pid = 0;
    P->next = NULL;
    P->status = 'R';
    return P;
}

void extcmd(char* command)
{
    int bg = 0;
    char commandcopy[MAX];
    strcpy(commandcopy,command);
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
            printf("%s: command not found\n",com);
        }
        exit(1);
    }
    else
    {
        int r = 0;
        if(bg == 0)
        {
            setpgid(forkReturn,0);
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
            while(Q->next != NULL && strcmp(command,Q->processcommand) <= 0)
            {
                Q = Q->next;
            }
            strcpy(P->processname,com);
            P->jobno = ++jobIndex;
            strcpy(P->processcommand,commandcopy);
            P->pid = forkReturn;
            P->next = Q->next;
            Q->next = P;
            printf("%d\n",forkReturn);
        }
    }
}