#include "prompt.c"
#include "pwd.c"
#include "echo.c"
#include "cd.c"
#include "repeat.c"
#include "ls.c"
#include "pinfo.c"
#include "extcmd.c"
#include "history.c"
// typedef struct process
// {
//     int pid;
//     char name[MAX_SIZE];
// }process;

void getcommand(char* command)
{
    if(strchr(command,';'))
    {
        char allcomms[MAX][MAX];
        int i = 0;
        char* splitcom = strtok(command, ";\n");
        while (splitcom != NULL) // prints every token
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
        // write(fd, args, strlen(args));
        // write(fd,"\n",1);
        char* token = strtok(args, " \t");
        if(strcmp(token,"pwd") == 0){ pwdcmd(); }
        else if(strcmp(token,"exit") == 0) {exit(EXIT_SUCCESS);}
        else if(strcmp(token,"echo") == 0) {echocmd(command);}
        else if(strcmp(token,"cd") == 0) {cdcmd(command);}
        else if(strcmp(token,"repeat") == 0){ repeatcmd(command);}
        else if(strcmp(token,"ls") == 0){ lscmd(command);}
        else if(strcmp(token,"pinfo") == 0){ pinfocmd(command);}
        else if(strcmp(token,"history") == 0){ historycmd(command);}
        else { extcmd(command); }
    }
    
}

int main(int argc, char* argv[])
{
    getcwd(home,MAX);
    char command[MAX];
    historyget();
    int size;    
    while(1)
    {
        prompt();
        scanf("%[^\n]s",command);
        char x;
        scanf("%c",&x);
        historylog(command);
        historysave();
        getcommand(command);
    }
}