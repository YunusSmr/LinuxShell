
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void *get_time(char *strDate)
{

    time_t sysytime = time(NULL);
    char *time_str = ctime(&sysytime);
    time_str[strlen(time_str) - 1] = '\0';
    strcpy(strDate, time_str);
    strDate[strlen(strDate)] = '\0';
}
int main(int argc, char **argv)
{

    if (argc != 3)
    {
        printf("invalid number of paramter");
        exit(0);
    }

    if (strcmp(argv[1], "-f") == 0)
    {

        FILE *fp;
        char date[100];
        // Open file in write mode
        fp = fopen(argv[2], "a+");

        // If file opened successfully, then write the string to file
        if (fp)
        {

            fprintf(fp, "Pid değeri: %d\n", getpid());
            fprintf(fp, "Ppid değeri: %d\n", getppid());
            get_time(date);
            fprintf(fp, "System time: %s\n\n", date);
            // time_t t = time(NULL);
            // struct tm tm = *localtime(&t);
            // printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
            // fputs(tm,fp);
        }
        else
        {
            printf("Failed to open the file\n");
        }
        // Close the file
        fclose(fp);
    }
    else
    {
        printf("Wrong input");
        exit(0);
    }

    return (0);
}

