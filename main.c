#include "prompt.c"
#include "pwd.c"
#include "echo.c"
#include "cd.c"
#include "repeat.c"
#include "ls.c"
// typedef struct process
// {
//     int pid;
//     char name[MAX_SIZE];
// }process;

void getcommand(char* command)
{
    char args[MAX];
    strcpy(args,command);
    char* token = strtok(args, " \t");
    if(strcmp(token,"pwd") == 0){ pwdcmd(); }
    else if(strcmp(token,"echo") == 0) {echocmd(command);}
    else if(strcmp(token,"cd") == 0) {cdcmd(command);}
    else if(strcmp(token,"repeat") == 0){ repeatcmd(command);}
    else if(strcmp(token,"ls") == 0){ lscmd(command);}
    else { printf("Error: command not found\n"); }
}

int main(int argc, char* argv[])
{
    getcwd(home,MAX);
    // strcpy(home,"/home");
    // strcpy(home,"/mnt/e");
    prompt();
    char command[MAX];
    
    scanf("%[^\n]%*c",command);
    // char *command = NULL;
    // size_t len = 0;
    // getline(&command, &len, stdin);
    // command[strlen(s)-1] = '\0';
    // printf("%s\n",command);

    // char* command;
    // size_t len;
    // getline(&command, &len, stdin);
    
    while(strcmp(command,"exit") != 0)
    {
        // printf("command: %s\n",command);
        if(strcmp(command,"\0") == 0)   //// STILL NEED TO FIX EMPTY COMMAND BUG - INFINITE LOOP  
        {
            prompt();
            scanf("%[^\n]%*c",command);
        }
        else
        {
            // printf("command:%s\n",command);
            getcommand(command);
            prompt();
            scanf("%[^\n]%*c",command);
        }
    }
}