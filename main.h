#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <sys/wait.h>
#include <signal.h>
#include <ncurses.h>
#include <errno.h>
#include <fcntl.h>


#define MAX (int)1e3+5
char oldd[MAX];
char home[MAX];
int fd;
void prompt();
void pwdcmd();
void echocmd(char* command);
void cdcmd(char* command);
void repeatcmd(char* command);
void getcommand(char* command);

