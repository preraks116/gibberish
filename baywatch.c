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
            if (strcmp(token,"interrupt") == 0){p = 1;}
            else if (strcmp(token,"newborn") == 0){q = 1;}
            else if (strcmp(token,"dirty") == 0){r = 1;}
            token = strtok(NULL, " \t");
        }
    }
    if(p+q+r<1){printf("error: too few arguments");return;}
    else if(p+q+r>1){printf("error: too many arguments");return;}
    else
    {

        int curpid = fork();
        if(curpid == 0)
        {
            while(1)
            {
                printf("hi\n");
                sleep(interval);
            }
        }
        else
        {
            
            char c;
            setbuf(stdout, NULL);
            enableRawMode();
            while(read(STDIN_FILENO, &c, 1) == 1)
            {
                if(c == 'q'){kill(curpid,SIGTERM);break;}
            }
            disableRawMode();
        }
    }
}
