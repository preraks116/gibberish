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

char getstatus(int curpid)
{
    char pid[MAX];
    char* temp;
    sprintf(pid,"%d",curpid);
    char procstat[MAX] = "/proc/";
    char buffer[MAX];
    char status;
    strcat(procstat,pid);
    strcat(procstat,"/stat");
    int fd = open(procstat, O_RDONLY);
    if(fd == -1)
    {
        printf("error: pid %d not found\n",curpid);
    }
    else
    {
        read(fd, buffer, MAX);
        close(fd);
        char* token = strtok_r(buffer, " \t", &temp);
        token = strtok_r(NULL, " \t", &temp);
        token = strtok_r(NULL, " \t", &temp);
        status = token[0];
    }
    return status;
}

void extcmd(char* command)
{
    int bg = 0;
    char* temp;
    char commandcopy[MAX];
    strcpy(commandcopy,command);
    if(strchr(command,'&')){bg = 1;}
    char* token = strtok_r(command, " \t", &temp);
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
        
        token = strtok_r(NULL, " \t", &temp);
    }
    if(strcmp(args[i-1],"") == 0){args[i-1] = NULL;}
    int forkReturn = fork();
    if(forkReturn < 0)
    {
        perror("fork failed");
        return;
    }
    
    addjob(commandcopy,forkReturn,'R');
    // printf("%c\n",getstatus(forkReturn));
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
            removejob(forkReturn);
            tcsetpgrp(0, getpgrp());
            signal(SIGTTOU, SIG_DFL);
        }
        else
        {
            // addjob(commandcopy,forkReturn,'R');
            printf("%d\n",forkReturn);
        }
    }
}