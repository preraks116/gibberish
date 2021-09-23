#include "main.h"

void ctrlChandler()
{
    int curpid = tcgetpgrp(0);
    if(curpid == shellpid)
    {
        return;
    }
    printf("\n");
    prompt();
}

void ctrlZhandler()
{
    int curpid = tcgetpgrp(0);
    if(curpid == shellpid)
    {
        return;
    }
    printf("\n");
    prompt();
}

void ctrlDhandler(int pt)
{
    if(pt > 0){return;}
    printf("logout\n");
    getcommand("logout");
}


