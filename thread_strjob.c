#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KBLU  "\x1B[34m"


char buffer[256]="gabriele";

void *thread1(void * x){
   long int status;
   size_t len = strlen(buffer);
   int i=0;
   char temp;
   printf("%sI'm the thread %d\n\tinitial thread1 buffer %s; len buffer %ld\n%s",KRED,gettid(),buffer,strlen(buffer),KWHT);
for (i = 0; i < len/2; i++)  
    {  
        // temp variable use to temporary hold the string  
        temp = buffer[i];  
        buffer[i] = buffer[len - i - 1];  
        buffer[len - i - 1] = temp;  
        printf("%sinvert the characters at the edge of the string:%s\n%s",KBLU,buffer,KWHT);
    }  
   printf("%s-----------------------------------------------------------------%s\n",KGRN,KWHT);
   pthread_exit((void*)status);
}

void *thread2(void * x){
   long int status;
   size_t len = strlen(buffer);
   int i=0;
   char temp;
   printf("%sI'm the thread %d\n\tinitial thread2 buffer %s; len buffer %ld\n%s",KRED,gettid(),buffer,strlen(buffer),KWHT);
    while (len+1 != 0){
        buffer[len]='\0';
        len--;
        printf("%sdelete the last character of the string: %s\n%s",KBLU,buffer,KWHT);
    }
   printf("%s-----------------------------------------------------------------%s\n",KGRN,KWHT);
   pthread_exit((void*)status);
}
int main(int argc, char **argv){
   printf("%sI'm the main I pass the control to the threads %d \n\tinitial main buffer %s; len buffer %ld\n%s",KRED,getpid(),buffer,strlen(buffer),KWHT);
   printf("%s-----------------------------------------------------------------%s\n",KGRN,KWHT);
   void *status;
   void *status1;
   pthread_t t1;
   pthread_create(&t1,NULL,&thread1,NULL);  
   pthread_join(t1,&status);
   pthread_t t2;
   pthread_create(&t2,NULL,&thread2,NULL);  
   pthread_join(t2,&status1);   
   printf("%sI'm the main %d\n\tend main buffer %s; len buffer %ld\n%s",KRED,getpid(),buffer,strlen(buffer),KWHT);
   printf("%s\n",buffer);
}

