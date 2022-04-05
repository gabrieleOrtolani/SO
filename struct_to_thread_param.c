#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"

struct thread_args
 {
    char *filename;
    int count;
};

void* thread_foo(void *x){
        struct thread_args *args = (struct thread_args *)x;
        long int state;
        printf("%sI'm thread %d%s\n",KGRN,gettid(),KWHT);
        printf("%d\t",args->count);
        printf("message from thread i-1:%s\n",args->filename);
        //sleep(1);
        memset(args->filename,0,sizeof(char)*strlen(args->filename));
        printf("inserisci messaggio per il prossimo thread:");
        fgets(args->filename,sizeof(char)*1024,stdin);
        pthread_exit((void*)state);
}


int main(int argc, char** argv){
        int n=atoi(argv[1]);
        void * status;
        struct thread_args Structthread1;
        Structthread1.filename=malloc(sizeof(char)*1024);
        int i;
        for(i=1;i<=n;i++){
                pthread_t t[i];
                Structthread1.count=i;
                pthread_create(&t[i],NULL,thread_foo,(void*)&Structthread1);
                pthread_join(t[i],&status);
                sleep(1);

        }
        
        printf("%d\tmessagge from thread n:%s\n",i,Structthread1.filename);
        return 0;






}
