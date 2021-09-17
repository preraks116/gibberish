#include "main.h"

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
    int forkReturn = fork();
    if(forkReturn < 0)
    {
        perror("fork failed");
    }
    else if(forkReturn == 0)
    {
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
            waitpid(forkReturn,&r,WUNTRACED);
        }
        else{printf("%d\n",forkReturn);}
    }
}