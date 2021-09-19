#include "main.h"

void finishbg()
{
    Ptrprocessnode Q = header;
    int curpid = 0, r;
    char processname[MAX];
    while ((curpid = waitpid(-1, &r, WNOHANG | WUNTRACED)) > 0)
    {
        while (Q->next != NULL)
        {
            Q = Q->next;
            if (Q->pid == curpid)
            {
                strcpy(processname, Q->processname);
                break;
            }
        }
        if(curpid)
        {
            printf("\n%s with pid %d ",processname,curpid);
            if (__WIFEXITED(r)){printf("exited normally\n");}
            else if (__WIFSTOPPED(r)){printf("suspended normally\n");}
            else{printf("exited abnormally\n");}
            prompt();
            printf("%s",command);
            fflush(stdout);
        }
    }
}