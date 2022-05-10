
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>



char *fifos[]={"fifo_server_1","fifo_server_2","fifo_server_3","fifo_server_4","fifo_server_5"};
char PUBLIC[9]="MY_FIFO";
void * client_thread(void*x){
        int fd,wr;
        int i = (int)x;
        if((fd=open(fifos[i],O_WRONLY))==-1){
		perror("open fifo error: \n");
		exit(-1);
	}
	char buffer[32];
	printf("\tenter the message to be sent to the server:");
	fgets(buffer,sizeof(buffer),stdin);
	if((wr=write(fd,buffer,strlen(buffer)))==-1){
		perror("read from client error: \n");
		exit(-1);
	}
        printf("\tI'm client thread %d I just write to server thread\n",gettid());
	close(fd);
	pthread_exit(NULL);
	
}
int main(int argc, char *argv[]){
	int fd,wr,ret;
	int tn = atoi(argv[1]);
	char buffer[32] = "client request";
	char fifo_name[9]="gabriele";
	pthread_t tid[tn];

	if((fd=open(PUBLIC,O_WRONLY))==-1){
		perror("open fifo error: \n");
		exit(-1);
	}
        for(int i=0;i<tn;i++){
                pthread_create(&tid[i],NULL,client_thread,(void*)i);
                pthread_join(tid[i],NULL);
                printf("------------------------------------------------------------------------\n");
		
        }
        


	if((wr=write(fd,buffer,strlen(buffer)))==-1){
		perror("read from client error: \n");
		exit(-1);
	}
	/*
        for(int i=0;i<tn;i++){
                pthread_join(tid[i],NULL);
        }
        */

	printf("I'm client process %d I just write to server process \n",getpid());
	return 1;
	close(fd);
	

}

