#include "main.h"

void printjobs(char* status,Ptrprocessnode X)
{
    printf("[%d] ",X->jobno);
    printf("%s ",status);
    for(int i = 0; X->processcommand[i+1] != '&'; i++){printf("%c",X->processcommand[i]);}
    printf(" [%d]\n",X->pid);
}

void jobscmd(char* command)
{
    int flagR = 0, flagS = 0; 
    char* temp;
    char *token = strtok_r(command, " \t", &temp);
    token = strtok_r(NULL, " \t", &temp);
    if(token == NULL){flagS = 1;flagR = 1;}
    else if(strcmp(token,"-r") == 0){flagR = 1;}
    else if(strcmp(token,"-s") == 0){flagS = 1;}
    Ptrprocessnode X = header->next;
    char status;
    while(X != NULL)
    {
        status = getstatus(X->pid);
        if(flagR == 1)
        {
            
            if(status != 'T'){printjobs("Running",X);}
        } 
        if(flagS == 1)
        {
            if(status == 'T'){printjobs("Stopped",X);}
        } 
        X = X->next;
    }
}

void addjob(char* command, int pid, char status)
{
    char* temp;
    Ptrprocessnode P = InitProcessNode();
    Ptrprocessnode Q = header;
    while(Q->next != NULL && strcmp(command,Q->processcommand) > 0)
    {
        Q = Q->next;
    }
    P->jobno = ++jobIndex;
    strcpy(P->processcommand,command);
    char* token = strtok_r(command, " \t", &temp);
    strcpy(P->processname,token);
    P->pid = pid;
    P->status = status;
    // P->status = getstatus(pid);
    P->next = Q->next;
    Q->next = P;
}

void removejob(int pid)
{
    // Ptrprocessnode P = InitProcessNode();
    Ptrprocessnode Q = header;
    while(Q->next != NULL && Q->next->pid != pid)
    {
        Q = Q->next;
    }
    Ptrprocessnode P = Q->next;
    Q->next = Q->next->next;
    free(P);
}