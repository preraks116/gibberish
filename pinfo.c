#include "main.h"


void pinfocmd(char* command)
{
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    char procstat[MAX] = "/proc/";
    char curpid[MAX]; 
    if(token == NULL)
    {
        sprintf(curpid, "%d", getpid());
    }
    else
    {
        strcpy(curpid,token);
    }
    strcat(procstat,curpid);
    char copyprocstat[MAX];
    strcpy(copyprocstat,procstat);
    strcat(procstat,"/stat");
    char buffer[MAX];
    char buffer2[MAX];
    int fd = open(procstat, O_RDONLY);
    if(fd == -1)
    {
        printf("error: pid %s not found\n",curpid);
    }
    else
    {
        read(fd, buffer, MAX);
        close(fd);
        char* token = strtok(buffer, " \t");
        token = strtok(NULL, " \t");
        token = strtok(NULL, " \t");
        // printf("%s\n",buffer);
        printf("pid -- %s\n",curpid);
        char status[MAX];
        strcpy(status,token);
        int y = atoi(curpid);
        if(y == tcgetpgrp(0))
        {
            strcat(status,"+");
        }
        
        printf("Process Status -- %s\n",status);
        strcat(procstat,"m");
        int fd2 = open(procstat,O_RDONLY);
        if(fd2 == -1)
        {
            printf("error: pid %s not found\n",curpid);
        }
        else
        {
            read(fd, buffer2, MAX);
            close(fd);
            char* token2 = strtok(buffer2," \t");
            printf("memory -- %s {Virtual Memory}\n",token2);
        }
        strcat(copyprocstat,"/exe");
        char buffer3[MAX];
        int x = readlink(copyprocstat,buffer3,MAX);
        buffer3[x] = '\0';
        // printf("%s\n",buffer2);
        char tilde[] = "~";
        if(strstr(buffer3,home))
        {
            printf("Executable Path -- %s\n",strcat(tilde,&buffer3[strlen(home)]));
        }
        else
        {
            printf("Executable Path -- %s\n",buffer3);
        }
    }
}