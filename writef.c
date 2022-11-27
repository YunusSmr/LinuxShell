
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char ** argv)
{
    
    if (argc!=3)
    {
    printf("invalid number of paramter");
    exit(0);
    }
   
    if (strcmp(argv[1],"-f")==0)
    {
         
        FILE *fp;

   // Open file in write mode
   fp = fopen(argv[2],"a+");
  
   
   // If file opened successfully, then write the string to file
   if ( fp )
   {
        
	   fprintf(fp,"pid değeri :%d\n",getpid());
       fprintf(fp,"Ppid değeri :%d\n",getppid());
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

       // fputs(tm,fp);
       fputs("\n",fp);
        
    }
   else
    {
         printf("Failed to open the file\n");
    }
    //Close the file
   fclose(fp);

            
    }else{
        printf("Wrong input");
        exit(0);

    }
        
return(0);
}