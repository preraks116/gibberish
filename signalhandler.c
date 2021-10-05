#include "main.h"

void ctrlChandler()
{
    printf("\n");
    prompt();
}

void ctrlZhandler() //doesnt work
{
    int curpid = tcgetpgrp(0);
    // printf("%d\n",curpid);
    // printf("%d\n",shellpid);
    if(curpid == shellpid)
    {
        return;
    }
    printf("hi\n");
    kill(curpid, SIGTSTP);
    printf("%s\n",command);
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

