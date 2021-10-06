#include "main.h"

void redirect_input(char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file %s\n",filename);
        exit(1);
    }
    dup2(fd, 0); //redirect stdin to file
    close(fd);
}

void redirect_output(char *filename)
{
    int fd;
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Error opening file %s\n",filename);
        exit(1);
    }
    dup2(fd, 1); //redirect stdout to file
    close(fd);
}

void redirect_io(char *filename)
{
    int fd;
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Error opening file %s\n",filename);
        exit(1);
    }
    dup2(fd, 1); 
    dup2(fd, 0); 
    close(fd);
}

void reset_stdio()
{
    dup2(storage_out, 1);
    dup2(storage_in, 0);
}

void inputredircmd(char *command)
{
    char *filename;
    char finalcom[MAX];
    int i = 0;
    char *token = strtok(command, " \t");

    char args[MAX][MAX];
    while (token != NULL)
    {
        strcpy(args[i], token);
        i++;
        token = strtok(NULL, " \t");
    }
    // args[i+1] = malloc(MAX);
    // for (int i = 0; args[i] != NULL; i++)
    // {
    //     printf("%s\n", args[i]);
    // }
    int argindex = 0;
    strcpy(finalcom, args[0]);
    // argindex++;
    for (argindex = 1; argindex < i; argindex++)
    {
        if (strcmp(args[argindex], ">") == 0)
        {
            filename = args[argindex + 1];
            redirect_output(filename);
            argindex++;
        }
        else if (strcmp(args[argindex], "<") == 0)
        {
            filename = args[argindex + 1];
            redirect_input(filename);
            argindex++;
        }
        else
        {
            strcat(finalcom, " ");
            strcat(finalcom, args[argindex]);
        }
    }
    getcommand(finalcom);
    reset_stdio();
}
