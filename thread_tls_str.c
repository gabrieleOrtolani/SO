/*this program demonstrates how a tls variable is used by the thread, as a copy.*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TLS*/
__thread char stringa[256]="castello";

void *thread1(void* x){
        long int status;
        stringa[7]='\0';
        printf("string in  thread, delete the last char: %s\n",stringa);
        pthread_exit((void*)status);
}




int main(int argc, char **argv){
        long int status;
        printf("string in  main before thread jobs : %s\n",stringa);
        pthread_t t1;
        pthread_create(&t1,NULL,thread1,NULL);
        pthread_join(t1,&status);
        printf("string in  main after thread jobs :  %s\n",stringa);

}
