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
    if(strchr(command,';'))
    {
        char allcomms[MAX][MAX];
        int i = 0;
        char* splitcom = strtok(command, ";\n");
        while (splitcom != NULL) // prints every token
        {
            // printf("%s\n", splitcom);
            // getcommand(splitcom);
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
    // strcpy(home,"/home");
    // strcpy(home,"/mnt/e");
    prompt();
    char command[MAX];
    
    int size;
    scanf("%[^\n]%n%*c",command,&size);
    command[size] = '\0';
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
            scanf("%[^\n]%n%*c",command,&size);
            command[size] = '\0';
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