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

Ptrprocessnode InitProcessNode();

Ptrprocessnode header;
char history[20][MAX];
char oldd[MAX];
char home[MAX];
char command[MAX];
int fd;
int shellpid;
int storage_in;
int storage_out;
int jobIndex;
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
void finishbg();
void addjob(char* command, int pid, char status);
void removejob(int pid);
void ctrlZhandler();
void ctrlChandler();
void redirect_output(char *filename);
void reset_stdio();
void redirect_input(char *filename);
void redirect_input_append(char *filename);
void redirect_output_append(char *filename);
char getstatus(int curpid);
void sigcmd(char* command);
void fgcmd(char* command);
void bgcmd(char* command);
void pipecmd(char* command);
int pipe_close(int *pipefd);
int pipe_create(int *pipefd);
void redirect_io(char *filename);
void inputredircmd(char *command);
void interruptcmd();
void dirtycmd();
void newborncmd();
void baywatchcmd(char *command);
void replaycmd(char* command);
void printjobs(char* status,Ptrprocessnode X);
void jobscmd(char* command);
void addjob(char* command, int pid, char status);