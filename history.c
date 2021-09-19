#include "main.h"

int historyIndex = 0;

void historyget()
{
    char homePath[MAX];
    strcpy(homePath,home);
    strcat(homePath,"/history.txt");
    FILE* file = fopen(homePath, "r"); 
    char buffer[MAX];
    fgets(buffer, sizeof(buffer), file);
    char* token = strtok(buffer, ";");
    token = strtok(NULL, ";");
    for(;token != NULL; historyIndex++)
    {
        strcpy(history[historyIndex],token);
        token = strtok(NULL, ";");
    }

}

void historylog(char* command)
{
    if(strcmp(command,history[historyIndex-1]) == 0)
    {
        return;
    }
    else if(strcmp(command,"@") == 0)
    {
        return;
    }
    if(historyIndex == 20)
    {
        for(int i = 0; i < 19; i++)
        {
            strcpy(history[i],history[i+1]);
        }
        strcpy(history[19],command);
    }
    else
    {
        strcpy(history[historyIndex],command);
        historyIndex++;
    }
}

void historycmd(char* command)
{
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    int x = historyIndex;
    char* token2 = strtok(NULL, " \t");
    if(token2 != NULL)
    {
        printf("error: too many arguments\n");
    }
    else
    {
        if(token != NULL)
        {
            x = atoi(token);
            if(x == 0)
            {
                printf("error: invalid arguments\n");
                return;
            }
        }
        for(int i = historyIndex - x ; i < historyIndex; i++)
        {
            if(history[i][0] != '\0')
            {
                printf("%s\n",history[i]);
            }
        }
    }
}

void historysave()
{
    char homePath[MAX];
    strcpy(homePath,home);
    strcat(homePath,"/history.txt");
    fd = open(homePath, O_CREAT | O_RDWR | O_TRUNC, 0600);
    char buffer[MAX];
    for(int i = 0; i < historyIndex; i++)
    {
        write(fd,history[i],strlen(history[i]));
        if(i != historyIndex - 1){write(fd," ;",2);}
    }
}
