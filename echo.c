#include "main.h"

void echocmd(char* command) ///// SEG FAULTS IF YOU PUT AROUND 20 SPACES 
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