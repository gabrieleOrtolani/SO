#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
int status=0;
void *thread_function(void *stringa)
{
   printf ("sub thread, my job is to print: %s\n",*(char **)stringa);
   status=1;
   pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    char stringa[1024];
    if (argc != 2)
    {
        printf("argc error, missing argv\n");
        return 1;
    }
    strcpy(stringa, argv[1]);
    //printf("stringa: %s\n", stringa);
    int i;
    pthread_t thread1;
    void * p = &stringa;
    pthread_create(&thread1, NULL,thread_function,&p);
    sleep(2);
    if (status)
    {
         printf("main thread, my job is to print:%s\n",stringa);
    }

    return 0;
}


