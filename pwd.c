#include "main.h"

void pwdcmd() 
{
    char curPath[MAX];
    getcwd(curPath,MAX);
    printf("%s\n",curPath);
}

