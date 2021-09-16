#include "main.h"

void cdcmd(char* command)
{
    char cur[MAX];
    getcwd(cur,MAX);
    char* token = strtok(command, " \t");
    token = strtok(NULL, " \t");
    if(token == NULL)
    {
        int r = chdir(home);
        if(r == -1){perror("path error");}
        else { strcpy(oldd,cur); }
    }
    else
    {
        char* token2 = strtok(NULL, " \t");
        if(token2 != NULL)
        {
            printf("Error: Too many arguments\n");
        }
        else
        {
            // printf("%s\n",token);
            if (strcmp(token,"-") == 0)
            {
                int q = chdir(oldd);
                if(q == -1){perror("path error");}
                else{ pwdcmd();strcpy(oldd,cur);}
            }
            else if(strcmp(token,"~") == 0)
            {
                int r = chdir(home);
                if(r == -1){perror("path error");}
                else { strcpy(oldd,cur); }
            }
            else
            {
                int r = chdir(token);
                if(r == -1){perror("path error");}
                else { strcpy(oldd,cur); }
            }
        }
    }
}