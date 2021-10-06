#include "main.h"

void echocmd(char* command)
{
    // printf("command: %s\n",command);
    char* temp;
    char* token = strtok_r(command, " \t", &temp);
    token = strtok_r(NULL, " \t",&temp);
    while (token != NULL) // prints every token
    {
        printf("%s ", token);
        token = strtok_r(NULL, " \t", &temp);
    }
    printf("\n");
}