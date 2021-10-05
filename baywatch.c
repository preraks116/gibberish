#include "main.h"

void baywatchcmd(char *command)
{
    char *token = strtok(command, " \t");
    // printf("token:%s\n",token);
    token = strtok(NULL, " \t");
    char temp[MAX] = "";
    int interval = 1;
    int i = 0;
    int p = 0, q = 0, r = 0;
    while (token != NULL)
    {
        if (strcmp(token, "-n") == 0)
        {
            token = strtok(NULL, " \t");
            if (token == NULL)
            {
                printf("error: no command given\n");
                return;
            }
            else
            {
                interval = atoi(token);
                token = strtok(NULL, " \t");
            }
        }
        else
        {
            if (strcmp(token,"interrupt") == 0)
            {
                p = 1;
            }
            else if (strcmp(token,"newborn") == 0)
            {
                q = 1;
            }
            else if (strcmp(token,"dirty") == 0)
            {
                r = 1;
            }
            token = strtok(NULL, " \t");
        }
    }
    if(p+q+r<1){printf("error: too few arguments");return;}
    else if(p+q+r>1){printf("error: too many arguments");return;}
    else
    {
        // printing till q is pressed
        
        while(1)
        {
            printf("hi\n");
            sleep(1);
            if(getchar()=='q')
            {
                break;
            }
        }
        

        // while(1)
        // {
        //     // printf("%s\n",output);
        //     sleep(1);
        //     // char response = waitForCharInput(1);
        //     // if(response == 'q'){break;}
        //     // if(i != 0 && i % interval == 0)
        //     // {
        //     //     printf("%d %d %d\n",p,q,r);
        //     // }
        //     printf("%d %d %d\n",p,q,r);
        // }

    }
}
