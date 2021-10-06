#include "main.h"

void interruptcmd()
{
    char path[MAX] = "/proc/interrupts";
    char* temp;
    char final[MAX] = "";
    FILE* fp = fopen(path, "r");
    char *store = NULL;
    size_t len = 0;

    for(int i = 0; i < 3; i++)
    {
        getline(&store, &len, fp);
    }

    char *next = strtok_r(store, " \t", &temp);
    next = strtok_r(NULL, " \t", &temp);
    for(int i = 0; i < 8; i++)
    {
        strcat(final, next);
        strcat(final, "\t");
        next = strtok_r(NULL, " \t", &temp);
    }
    printf("%s\n", final);
}

void dirtycmd()
{
    printf("bye\n");
}

void newborncmd()
{
    printf("psy\n");
}

void baywatchcmd(char *command)
{
    char* temp;
    char *token = strtok_r(command, " \t", &temp);
    // printf("token:%s\n",token);
    token = strtok_r(NULL, " \t", &temp);
    void (*func)();
    // char temp[MAX] = "";
    int interval = 1;
    int i = 0;
    int p = 0, q = 0, r = 0;
    while (token != NULL)
    {
        if (strcmp(token, "-n") == 0)
        {
            token = strtok_r(NULL, " \t", &temp);
            if (token == NULL)
            {
                printf("error: no command given\n");
                return;
            }
            else
            {
                interval = atoi(token);
                token = strtok_r(NULL, " \t", &temp);
            }
        }
        else
        {
            if (strcmp(token,"interrupt") == 0){p = 1;func = &interruptcmd;printf("CPU0\tCPU1\tCPU2\tCPU3\tCPU4\tCPU5\tCPU6\tCPU7\n");}
            else if (strcmp(token,"newborn") == 0){q = 1;func = &newborncmd;}
            else if (strcmp(token,"dirty") == 0){r = 1;func = &dirtycmd;}
            else{printf("error: invalid command\n");return;}
            token = strtok_r(NULL, " \t", &temp);
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
                (*func)();
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
