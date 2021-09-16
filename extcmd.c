#include "main.h"

void extcmd(char* command)
{
    char* token = strtok(command, " \t");
    char* args[MAX] = {NULL};
    char com[MAX];
    strcpy(com,token);
    int i = 0;
    while(token != NULL)
    {   
        args[i] = malloc(MAX);
        strcpy(args[i],token);
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
        waitpid(forkReturn,&r,WUNTRACED);
    }
}