#include "main.h"

void finishbg()
{
    Ptrprocessnode Q = header;
    int curpid = 0, r;
    char processname[MAX] = {'\0'};
    while ((curpid = waitpid(-1, &r, WNOHANG | WUNTRACED)) > 0)
    {
        while (Q->next != NULL)
        {
            Q = Q->next;
            if (Q->pid == curpid)
            {
                strcpy(processname, Q->processname);
                Q->status = 'S';
                break;
            }
        }
        if(processname[0] == '\0'){return;}
        if(curpid)
        {
            printf("\n%s with pid %d ",processname,curpid);
            if (__WIFEXITED(r)){printf("exited normally\n");}
            else if (__WIFSTOPPED(r)){printf("suspended normally\n");}
            else{printf("exited abnormally\n");}
            prompt();
            if(strcmp(command,"@") != 0)
            {
                printf("%s",command);
            }
            fflush(stdout);
        }
    }
}