#include "main.h"


int pipe_create(int *pipefd)
{
    if (pipe(pipefd) == -1)
    {
        printf("Error: %d %d pipe_create() failed.\n", pipefd[0], pipefd[1]);
        return -1;
    }
    return 0;
}

int pipe_close(int *pipefd)
{
    if (close(pipefd[0]) == -1)
    {
        printf("Error: %d pipe_close() failed.\n", pipefd[0]);
        return -1;
    }
    if (close(pipefd[1]) == -1)
    {
        printf("Error: %d pipe_close() failed.\n", pipefd[1]);
        return -1;
    }
    return 0;
}

void pipecmd(char* command)
{
    char* temp;
    int argno = 0;
    char *token = strtok_r(command, "|", &temp);
    char args[MAX][MAX];
    while (token != NULL)
    {
        strcpy(args[argno], token);
        // printf("%s\n", args[argno]);
        argno++;
        token = strtok_r(NULL, "|", &temp); 
    }
    int ** pipearray = (int **) malloc((argno - 1) * sizeof(int *));
    for(int i = 0; i < argno - 1; i++){pipearray[i] = (int *) malloc(2 * sizeof(int));}
    int r = pipe_create(pipearray[0]);if(r < 0){return;}
    int fd = dup(1);
    dup2(pipearray[0][1], 1);
    getcommand(args[0]);
    close(pipearray[0][1]);
    for(int i = 1; i < argno - 1; i++)
    {
        int r = pipe_create(pipearray[i]);if(r < 0){return;}
        dup2(pipearray[i-1][0], 0);
        dup2(pipearray[i][1], 1);
        getcommand(args[i]);
        close(pipearray[i-1][0]);
        close(pipearray[i][1]);
        free(pipearray[i-1]);
    }
    dup2(pipearray[argno-2][0], 0);
    dup2(fd, 1);
    getcommand(args[argno - 1]);
    close(pipearray[argno-2][0]);
    free(pipearray[argno-2]);
    free(pipearray);
    reset_stdio();
}