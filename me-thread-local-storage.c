#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


__thread int numero = 10;

void *thread1(void* x){
        long int status;
        numero++;
        printf("numero +1  nel thread: %d\n",numero);
        pthread_exit((void*)status);
}




int main(int argc, char **argv){
        long int status;
        printf("numero prima main: %d\n",numero);
        pthread_t t1;
        pthread_create(&t1,NULL,thread1,NULL);
        pthread_join(t1,&status);
        printf("numero dopo main: %d\n",numero);

}
