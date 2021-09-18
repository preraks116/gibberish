#include "main.h"

void echocmd(char* command)
{
    // printf("command: %s\n",command);
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    while (token != NULL) // prints every token
    {
        printf("%s ", token);
        token = strtok(NULL, " \t");
    }
    printf("\n");
}