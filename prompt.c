#include "main.h"

void prompt()
{
    char sysname[MAX], curPath[MAX];
    char* username = getenv("LOGNAME");
    gethostname(sysname, MAX);
    char tilde[] = "~";
    getcwd(curPath, MAX);
    if(strstr(curPath,home))
    {
        printf("<%s@",username);
        printf("%s:",sysname);
        printf(" %s > ",strcat(tilde,&curPath[strlen(home)]));
    }
    else
    {
        printf("<%s@%s: %s > ",username,sysname,curPath);
    }
    //printf("<%s@%s: %s > ",username,sysname,strstr(curPath,home) ? strcat(tilde,&curPath[strlen(home)]) : curPath);
}