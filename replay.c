#include "main.h"

void replaycmd(char* command)
{
    // printf("%s\n",command);
    char* token = strtok(command, " \t");
    // printf("token:%s\n",token);
    token = strtok(NULL, " \t");
    char finalcommand[MAX] = "";
    int interval, period;
    int i = 0;
    while(token != NULL)
    {
        if(strcmp(token,"-command") == 0)
        {
            token = strtok(NULL, " \t");
            if(token == NULL)
            {
                printf("error: no command given\n");
                return;
            }
            else
            {
                while(token != NULL && token[0] != '-')
                {
                    // printf("hi\n");
                    strcat(finalcommand,token);
                    strcat(finalcommand," ");
                    // printf("finalcommand: %s\n",finalcommand);
                    token = strtok(NULL, " \t");
                }
            }
        }
        else if(strcmp(token,"-interval") == 0)
        {
            token = strtok(NULL, " \t");
            if(token == NULL)
            {
                printf("error: no interval given\n");
                return;
            }
            else
            {
                interval = atoi(token);
                token = strtok(NULL, " \t");
            }
        }
        else if(strcmp(token,"-period") == 0)
        {
            token = strtok(NULL, " \t");
            if(token == NULL)
            {
                printf("error: no period given\n");
                return;
            }
            else
            {
                period = atoi(token);
                token = strtok(NULL, " \t");
            }
        }
    }
    // printf("%s\n",finalcommand);
    // printf("%d\n",interval);
    // printf("%d\n",period);
    char temp[MAX];
    while(1)
    {
        i++;
        if(i == period+1)
        {
            break;
        }
        sleep(1);
        if(i != 0 && i % interval == 0)
        {
            strcpy(temp,finalcommand);
            getcommand(temp);
        }
    }
}