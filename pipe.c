#include "main.h"


int pipe_create(int *pipefd)
{
    if (pipe(pipefd) == -1)
    {
        printf("Error: pipe_create() failed.\n");
        return -1;
    }
    return 0;
}

int pipe_close(int *pipefd)
{
    if (close(pipefd[0]) == -1)
    {
        printf("Error: pipe_close() failed.\n");
        return -1;
    }
    if (close(pipefd[1]) == -1)
    {
        printf("Error: pipe_close() failed.\n");
        return -1;
    }
    return 0;
}

// void pipegetcommand(char* command)
// {
//     char* temp;
//     char commandcopy[MAX];
//     strcpy(commandcopy,command);
//     char* token = strtok_r(command, " \t", &temp);
//     char* args[MAX] = {NULL};
//     char com[MAX];
//     strcpy(com,token);
//     int i = 0;
//     while(token != NULL)
//     {   
//         args[i] = malloc(MAX);
//         if(strcmp(token,"&") != 0)
//         {
//             strcpy(args[i],token);
//         }
//         i++;
        
//         token = strtok_r(NULL, " \t", &temp);
//     }
//     if(strcmp(args[i-1],"") == 0){args[i-1] = NULL;}
//     setpgid(0, 0);
//     write(1, "\n",1);
//     int q = execvp(com,args);
//     if(q == -1)
//     {
//         printf("%s: command not found\n",com);
//     }
// }


void pipecmd(char* command)
{
    char* temp;
    int argno = 0;
    int pipefd[2] = {0,1};
    int pipefd2[2];
    char *token = strtok_r(command, "|", &temp);
    char args[MAX][MAX];
    while (token != NULL)
    {
        strcpy(args[argno], token);
        argno++;
        token = strtok_r(NULL, "|", &temp); 
    }
    for(int i = 0; i < argno; i++)
    {
        if(i < argno - 1)
        {
            int r = pipe_create(pipefd2);
            if(r < 0){return;}
        }
        int pid = fork();
        if(pid < 0){perror("fork failed");return;}
        if(pid == 0)
        {
            if(i > 0)
            {
                dup2(pipefd[0], 0);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            if(i < argno - 1)
            {
                dup2(pipefd2[1], 1);
                close(pipefd2[0]);
                close(pipefd2[1]);
            }
            // pipegetcommand(args[i]);
        }
        else
        {
            if(i > 0)
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            if(i < argno - 1)
            {
                pipefd[0] = pipefd2[0];
                pipefd[1] = pipefd2[1];
            }
        }
    }
    if(argno > 1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
    }
    reset_stdio();
}