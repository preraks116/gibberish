#include "main.h"

void ctrlChandler()
{
    printf("\n");
    prompt();
}

void ctrlZhandler()
{
    int curpid = tcgetpgrp(0);
    if(curpid == shellpid)
    {
        return;
    }
    kill(SIGSTOP,curpid);
    Ptrprocessnode P = InitProcessNode();
    Ptrprocessnode Q = header;
    while(Q->next != NULL && strcmp(command,Q->processcommand) > 0)
    {
        Q = Q->next;
    }
    strcpy(P->processcommand,command);
    char* token = strtok(command, " \t");
    strcpy(P->processname,token);
    P->jobno = ++jobIndex;
    P->pid = curpid;
    P->next = Q->next;
    Q->next = P;
    printf("%d\n",curpid);
    printf("\n");
    prompt();
}

void ctrlDhandler(int pt)
{
    if(pt > 0){return;}
    printf("logout\n");
    getcommand("logout");
}


