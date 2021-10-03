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
    kill(curpid, SIGTSTP);
    addjob(command,curpid,'S');
    printf("\n");
    prompt();
}

void ctrlDhandler(int pt)
{
    if(pt > 0){return;}
    printf("logout\n");
    getcommand("logout");
}

//it should push any currently running foreground job into the background, and change its state from running to stopped. This should have no effect on the shell if there is no foreground process running

