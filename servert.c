#define _GNU_SOURCE
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

char PUBLIC[9]="MY_FIFO";
char *fifos[]={"fifo_server_1","fifo_server_2","fifo_server_3","fifo_server_4","fifo_server_5"};

void *server_thread(void*x){
        int fd, rd, ret;
        int i = (int)x;
        char *buffer=malloc(sizeof(char)*32);
        if((ret = mkfifo(fifos[i],0660))==-1){
		perror("mkfifo error: \n");
		exit(-1);
	}


	if((fd=open(fifos[i],O_RDONLY))==-1){
		perror("open fifo error: \n");
		exit(-1);
	}

	if((rd=read(fd,buffer,sizeof(buffer)*4))==-1){
		perror("read from client error: ");
		exit(-1);
		
	}
	printf("I'm server thread %d, I read from client thread this line: %s\n",gettid(),buffer);
	close(fd);
	pthread_exit(NULL);


}
int main(int argc, char *argv[]){
	int fd,rd,ret;
        int tn = atoi(argv[1]);
	char *buffer=malloc(sizeof(char)*32);
        pthread_t tid[tn];
	

        for(int i=0;i<tn;i++){
                pthread_create(&tid[i],NULL,server_thread,(void*)i);
		
        }
	if((ret = mkfifo(PUBLIC,0660))==-1){
		perror("mkfifo error: \n");
		exit(-1);
	}


	if((fd=open(PUBLIC,O_RDONLY))==-1){
		perror("open fifo error: \n");
		exit(-1);
	}

	if((rd=read(fd,buffer,sizeof(buffer)*4))==-1){
		perror("read from client error: \n");
		exit(-1);
		
	}

	
        for(int i=0;i<tn;i++){
                pthread_join(tid[i],NULL);
        }
	printf("I'm server process %d , I read from client process this line: %s\n",getpid(),buffer);
	
	close(fd);
	for(int i=0;i<tn;i++){
		remove(fifos[i]);
		printf("------ %s was deleted\n",fifos[i]);
	}
	remove(PUBLIC);
	return 1;

}
