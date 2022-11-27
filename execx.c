#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


// 0    1  2     3
// execve -t 5  execv -t 5  execv -t 5  execv -t 5 writef -f isim 
int main(int argc, char **argv)
{
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

    return 0;
}