void log(char* command)
{
    write(fd,command,strlen(command));
    write(fd,"\n",1);
}