#include "main.h"

void finishbg()
{
    Ptrprocessnode Q = header;
    int pid = 0, r, curpid;
    char processname[MAX];
    while ((pid = waitpid(-1, &r, WNOHANG | WUNTRACED)) > 0)
    {
        while (Q->next != NULL)
        {
            Q = Q->next;
            if (Q->pid == pid)
            {
                strcpy(processname, Q->processname);
                break;
            }
        }

        if (pid)
        {
            if (WIFEXITED(r))
                printf("\n%s with pid %d exited normally\n", processname, pid);
            else if (WIFSTOPPED(r))
                printf("\n%s with pid %d suspended normally\n", processname, pid);
            else
                printf("\n%s with pid %d exited abnormally\n", processname, pid);
            prompt();
            fflush(stdout);
        }
    }
}