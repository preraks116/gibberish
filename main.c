#include "prompt.c"
#include "pwd.c"
#include "echo.c"
#include "cd.c"
#include "repeat.c"
#include "ls.c"
#include "pinfo.c"
#include "extcmd.c"
#include "history.c"
#include "arrowkey.c"
#include "finishbg.c"
#include "replay.c"
#include "jobs.c"
#include "signalhandler.c"
#include "sig.c"

void getcommand(char* command)
{
    if(strcmp(command,"@") == 0)
    {
        return;
    }
    if(strchr(command,';'))
    {
        char allcomms[MAX][MAX];
        int i = 0;
        char* splitcom = strtok(command, ";\n");
        while (splitcom != NULL) 
        {
            strcpy(allcomms[i],splitcom);
            splitcom = strtok(NULL, ";");
            i++;
        }
        for(int j = 0; j < i; j++)
        {
            getcommand(allcomms[j]);
        }
    }
    else
    {
        char args[MAX];
        strcpy(args,command);
        char* token = strtok(args, " \t");
        if(strcmp(token,"pwd") == 0){ pwdcmd(); }
        else if(strcmp(token,"exit") == 0 || strcmp(token,"logout") == 0) {exit(EXIT_SUCCESS);}
        else if(strcmp(token,"echo") == 0) {echocmd(command);}
        else if(strcmp(token,"cd") == 0) {cdcmd(command);}
        else if(strcmp(token,"repeat") == 0){ repeatcmd(command);}
        else if(strcmp(token,"ls") == 0){ lscmd(command);}
        else if(strcmp(token,"pinfo") == 0){ pinfocmd(command);}
        else if(strcmp(token,"history") == 0){ historycmd(command);}
        else if(strcmp(token,"replay") == 0){replaycmd(command);}
        else if(strcmp(token,"jobs") == 0){jobscmd(command);}
        else if(strcmp(token,"sig") == 0){sigcmd(command);}
        else { extcmd(command); }
    }
    
}

int main() 
{
    char c;
    getcwd(home,MAX);
    historyget();
    int shellpid = tcgetpgrp(0);
    // printf("shellpid:%d\n",shellpid);
    header = InitProcessNode();
    while (1) 
    {
        signal(SIGCHLD,finishbg);
        signal(SIGINT,ctrlChandler);
        signal(SIGTSTP, ctrlZhandler);
        setbuf(stdout, NULL);
        enableRawMode();
        prompt();
        memset(command, '\0', MAX);
        strcpy(command,"@");
        int pt = 0;
        int i = historyIndex - 1;
        while (read(STDIN_FILENO, &c, 1) == 1) 
        {
            if (iscntrl(c)) 
            {
                if (c == 10) break;
                else if (c == 27) 
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2) 
                    { 
                        if(strcmp(buf,"[A") == 0)
                        {
                            printf("\r");
                            prompt();
                            for(int j = 0; j < 60; j++){printf(" ");}
                            printf("\r");
                            prompt();
                            memset(command, '\0', MAX);
                            pt = 0;
                            for(int j = 0; j < strlen(history[i]); j++)
                            {
                                command[pt++] = history[i][j];
                            }
                            printf("%s", history[i]);
                            if(i > 0){i--;}
                        }
                    }
                } 
                else if (c == 127) 
                { 
                    if (pt > 0) 
                    {
                        if (command[pt-1] == 9) 
                        {
                            for (int i = 0; i < 7; i++) {printf("\b");}
                        }
                        command[--pt] = '\0';
                        printf("\b \b");
                    }
                } 
                else if (c == 9) 
                { 
                    command[pt++] = c;
                    for (int i = 0; i < 8; i++) { printf(" ");}
                } 
                else if (c == 4) {ctrlDhandler(pt);} //ctrl + D handler
                else {printf("%d\n", c);} 
            } 
            else 
            {
                command[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();
        historylog(command);
        historysave();
        printf("\n");
        getcommand(command);
    }
}