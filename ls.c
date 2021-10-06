#include "main.h"
char letters[3] = {'r', 'w', 'x'};

void fileperms(char *arg)
{
    char permissions[9];
    struct stat buf;
    stat(arg, &buf);
    if (S_ISDIR(buf.st_mode))
    {
        printf("d");
    }
    else
    {
        printf("-");
    }
    int perms[9] = {0};
    int x = buf.st_mode % 32768;

    for (int j = 0; x > 0; x /= 8)
    {
        int y = x % 8;

        for (int i = 0; i < 3; i++)
        {
            perms[j] = y % 2;
            y = y / 2;
            j++;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (perms[8 - (3 * i + j)] == 0)
            {
                permissions[3 * i + j] = '-';
            }
            else
            {
                permissions[3 * i + j] = letters[j];
            }
        }
    }
    printf("%s ", permissions);
}

void lscmd(char *command) 
{
    char* hello;
    int flagA = 0, flagL = 0, pathIndex = 0;
    char *token = strtok_r(command, " \t", &hello);
    char temp[MAX];
    token = strtok_r(NULL, " \t", &hello);
    char pathArray[MAX][MAX];
    char curPath[MAX];
    getcwd(curPath, MAX);
    strcpy(pathArray[0], curPath);
    while (token != NULL)
    {
        if (token[0] == '-')
        {
            for (int i = 1; i < strlen(token); i++)
            {
                if (token[i] == 'l')
                {
                    flagL = 1;
                }
                else if (token[i] == 'a')
                {
                    flagA = 1;
                }
            }
        }
        else if (token[0] == '~')
        {
            strcpy(pathArray[pathIndex],home);
            pathIndex++;
        }
        else
        {
            strcpy(pathArray[pathIndex], token);
            pathIndex++;
        }
        token = strtok_r(NULL, " \t", &hello);
    }
    // printf("PATHS:\n");
    // for(int i = 0; i < pathIndex; i++)
    // {
    //     printf("%s\n",pathArray[i]);
    // }
    // printf("A:%d\n",flagA);
    // printf("L:%d\n",flagL);
    // printf("patharray[0]: %s\n",pathArray[0]);
    struct dirent *d;
    struct stat buf;
    if (pathIndex == 0)
    {
        pathIndex++;
    }
    for (int i = 0; i < pathIndex; i++)
    {
        int r = stat(pathArray[i], &buf);
        if (r == -1)
        {
            perror("file error");
        }
        else
        {
            if (S_ISDIR(buf.st_mode))
            {
                if (pathIndex > 1)
                {
                    printf("%s:\n", pathArray[i]);
                }
                if (flagL)
                {
                    long total = 0;
                    DIR *dh = opendir(pathArray[i]);
                    if (!dh)
                    {
                        perror("error");
                    }
                    else
                    {
                        while ((d = readdir(dh)) != NULL) 
                        {
                            strcpy(temp, pathArray[i]);
                            strcat(temp, "/");
                            strcat(temp, d->d_name);
                            stat(temp, &buf);
                            total += buf.st_blocks;
                        }
                    }
                    printf("total %ld\n", total / 2);
                }
                DIR *dh = opendir(pathArray[i]);
                if (!dh)
                {
                    perror("error");
                }
                else
                {
                    while ((d = readdir(dh)) != NULL)
                    {
                        if (flagA == 0 && d->d_name[0] == '.')
                        {
                            continue;
                        }
                        if (flagL)
                        {
                            char datetime[MAX];
                            strcpy(temp, pathArray[i]);
                            strcat(temp, "/");
                            strcat(temp, d->d_name);
                            stat(temp, &buf);
                            stat(temp, &buf);
                            fileperms(temp);
                            printf("%ld ", buf.st_nlink);
                            printf("%s ", getpwuid(buf.st_uid)->pw_name);
                            printf("%s ", getgrgid(buf.st_gid)->gr_name);
                            printf("%5.ld ", buf.st_size);
                            strftime(datetime, 14, "%b %d %H:%M", localtime(&(buf.st_mtime)));
                            printf("%s ", datetime);
                        }
                        printf("%s  ", d->d_name);
                        if (flagL)
                            printf("\n");
                    }
                    if (flagL == 0)
                    {
                        printf("\n");
                    }
                    if (i < pathIndex - 1)
                    {
                        printf("\n");
                    }
                }
            }
            else
            {
                if (flagL)
                {
                    char datetime[MAX];
                    fileperms(pathArray[i]);
                    printf("%ld ", buf.st_nlink);
                    printf("%s ", getpwuid(buf.st_uid)->pw_name);
                    printf("%s ", getgrgid(buf.st_gid)->gr_name);
                    printf("%5.ld ", buf.st_size);
                    strftime(datetime, 14, "%b %d %H:%M", localtime(&(buf.st_mtime)));
                    printf("%s ", datetime);
                }
                printf("%s  ", pathArray[i]);
                printf("\n");
            }
        }
    }
}