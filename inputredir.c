#include "main.h"

void redirect_input(char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
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
        printf("Error opening file\n");
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
        printf("Error opening file\n");
        exit(1);
    }
    dup2(fd, 1); 
    dup2(fd, 0); 
    close(fd);
}

void reset_stdio()
{
    dup2(0, 1);
    dup2(0, 0);
}

void inputredircmd(char *command)
{
    char *filename;
    char finalcom[MAX];
    int i = 0;
    char *token = strtok(command, " \t");
    char *args[MAX] = {NULL};
    while (token != NULL)
    {
        args[i] = malloc(MAX);
        strcpy(args[i], token);
        i++;
        token = strtok(NULL, " \t");
    }
    // for (int i = 0; args[i] != NULL; i++)
    // {
    //     printf("%s\n", args[i]);
    // }
    int argindex = 0;
    while (args[argindex] != NULL)
    {
        // if (strcmp(args[argindex], "<") == 0)
        // {
        //     filename = args[argindex + 1];
        //     redirect_input(filename);
        //     break;
        // }
        // else if (strcmp(args[argindex], ">") == 0)
        // {
        //     filename = args[argindex + 1];
        //     redirect_output(filename);
        //     break;
        // }
        // else if (strcmp(args[argindex], ">>") == 0)
        // {
        //     filename = args[argindex + 1];
        //     redirect_io(filename);
        //     break;
        // }
        if (strcmp(args[argindex], ">") == 0)
        {
            filename = args[argindex + 1];
            strcpy(finalcom, args[0]);
            for (int i = 1; i < argindex; i++)
            {
                strcat(finalcom, " ");
                strcat(finalcom, args[i]);
            }
            // printf("%s\n", finalcom);
            // printf("%s\n",filename);
            redirect_output(filename);
            break;
        }
        else if (strcmp(args[argindex], "<") == 0)
        {
            filename = args[argindex + 1];
            strcpy(finalcom, args[0]);
            for (int i = 1; i < argindex; i++)
            {
                strcat(finalcom, " ");
                strcat(finalcom, args[i]);
            }
            redirect_input(filename);
            break;
        }
        argindex++;
    }
    getcommand(finalcom);
    reset_stdio();
}
