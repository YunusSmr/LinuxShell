#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

int isNumber(char *prm)
{
    while (*prm != '\0')
    {
        if (*prm < '0' || *prm > '9')
            return 0;
        prm++;
    }
    return 1;
}
// 0       1 2 3       4 5
// execx -t 5 writef -f isim
int main(int argc, char **argv)
{

    if (argc != 6)
    {
        printf("Wrong number of parameters\n");
        printf("You entered  = %d \n", argc);
        exit(0);
    }

    if (strcmp(argv[1], "-t") != 0)
    {
        printf("2. parameter should be -t for times \n");
        exit(0);
    }

    if (isNumber(argv[2]) != 1)
    {
        printf("3. parameter should be a number for -t \n");
        exit(0);
    }


    char *arg[argc - 2];

    for (int i = 0; i < argc-2; i++)
    {
        arg[i] = argv[i+3];
    }

    arg[argc - 3] = NULL;

    
    for (size_t i = 0; i < atoi(argv[2]); i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            printf("\nFailed to fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execv(argv[3], arg) < 0)
            {
                printf("\nInvalid command..");
            }
        }
        else
        {
            // waiting for child to abort
            wait(&pid);
        }
        
    }
    /*


    int i;
    // int n = argv[3];
    //  for(i = 0;i < argv[];i++){

    printf("%s %s", argv[1], argv[2]);
    for (i = 0; i < atoi(argv[2]); i++)
    {
        pid_t pid;
        pid = fork();
        printf("fork\n");
        if (pid == -1){
            printf("anan öldü\n");
            exit(0);

        }else if ( pid == 0){
            printf("0\n");

            char* argArr[argc-2];
            for(i = 3; i < argc-2;i++){
                argArr[i-3] = argv[i];
                printf("%s",argArr[i-3]);
            }
            argArr[i-1]=NULL;
            //argumanlar yeni arraya atandı
            char *test[4] = {"writef", "-f", "isim", NULL};
            char *anan = "writef";
            execv(argv[3], argArr);

        }else {
            wait(&pid);
            printf("%d \n",i);

        }


}
*/
    return 0;
}