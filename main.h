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
#include <termios.h>
#include <ctype.h>

#define MAX (int)1e3+5

struct termios orig_termios;

typedef struct processNode processnode;
typedef struct processNode * Ptrprocessnode;



Ptrprocessnode header;
char history[20][MAX];
char oldd[MAX];
char home[MAX];
int fd;
void die(const char *s);
void disableRawMode();
void enableRawMode();
void cdcmd(char* command);
void echocmd(char* command);
void handlechild();
void extcmd(char* command);
void historyget();
void historylog(char* command);
void historycmd(char* command);
void historysave();
void fileperms(char *arg);
void lscmd(char *command);
void getcommand(char* command);
void pinfocmd(char* command);
void prompt();
void pwdcmd();
void repeatcmd(char* command);