#include "prompt.c"
#include "pwd.c"
#include "echo.c"
#include "cd.c"
#include "repeat.c"
#include "ls.c"
// #include "history.c"
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
        else if(strcmp(token,"echo") == 0) {echocmd(command);}
        else if(strcmp(token,"cd") == 0) {cdcmd(command);}
        else if(strcmp(token,"repeat") == 0){ repeatcmd(command);}
        else if(strcmp(token,"ls") == 0){ lscmd(command);}
        else { printf("Error: command not found\n"); }
    }
    
}

int main(int argc, char* argv[])
{
    getcwd(home,MAX);
    char command[MAX];
    // fd = open("history.txt", O_CREAT | O_RDWR | O_TRUNC, 0600);
    int size;
    // char* command;
    // size_t len;
    // getline(&command, &len, stdin);
    
    while(1)
    {
        prompt();
        scanf("%[^\n]%*c",command);
        // printf("command: %s\n",command);
        if(strcmp(command,"\0") == 0)   //// STILL NEED TO FIX EMPTY COMMAND BUG - INFINITE LOOP  
        {
            prompt();
            scanf("%[^\n]%*c",command);
            command[size] = '\0';
        }
        else if(strcmp(command,"exit") == 0)
        {
            // write(fd, "exit", 4);
            // write(fd,"\n",1);
            return 0;
        }
        else
        {
            // printf("command:%s\n",command);
            getcommand(command);
            
            // scanf("%[^\n]%*c",command);
        }
    }
}