#include "main.h"

void cdcmd(char* command)
{
    char cur[MAX];
    char* temp;
    getcwd(cur,MAX);
    char* token = strtok_r(command, " \t",&temp);
    token = strtok_r(NULL, " \t", &temp);
    if(token == NULL)
    {
        int r = chdir(home);
        if(r == -1){perror("path error");}
        else { strcpy(oldd,cur); }
    }
    else
    {
        char* token2 = strtok_r(NULL, " \t", &temp);
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