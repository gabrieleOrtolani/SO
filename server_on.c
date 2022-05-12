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
void *server_thread(void * arg){
        int fd, ret, wr;
	char request[1]="0";
         printf("server thread sta aprendo la fifo client in scrittura... \n");
         if((fd=open((char*)arg,O_WRONLY))==-1){
                 perror("error to open client fifo in server thread: ");
                 exit(-1);
         }
         printf("server thread scrive al client thread.. \n");
         if((wr=write(fd,request,sizeof(request)))==-1){
                 perror("error during read in client thread: ");
                 exit(-1);
         }
         printf("contatore: %s\n",request);
	 close(fd);
        int rd;
	char response[1];
         printf("server thread sta aprendo la fifo client in lettura... \n");
         if((fd=open((char*)arg,O_RDONLY))==-1){
                 perror("error to open client_fifo in server thread: ");
                 exit(-1);
         }
         printf("server thread aspetta la response..\n");
         if((rd=read(fd,response,sizeof(response)))==-1){
                 perror("error during read in server thread: ");
                 exit(-1);
         }
         close(fd);
        printf("contatore:%s\n",response);
        pthread_exit(NULL);
}

int main(void){
	
	int fd, rd, ret;
	char buffer[32];
	pthread_t tid;
	printf("main server mkfifo.. \n");
	if((ret=mkfifo(PUBLIC,0660))==-1){
		perror("mkfifo in server main error: ");
		exit(-1);
	}
	printf("main server open fifo... \n");
	if((fd=open(PUBLIC,O_RDONLY))==-1){
		perror("open server fifo error in server main: ");
		exit(-1);
	}
	printf("main server read from fifo..\n");
	if((rd=read(fd,buffer,sizeof(buffer)))==-1){
		perror("read from server fifo error in server main: ");
		exit(-1);
	}
	sleep(2);
	printf("main server delega un thread..\n");
	if(pthread_create(&tid, NULL, server_thread, (void*)buffer) != 0){
		perror("error to create server thread: ");
		exit(-1);
	}
	
	if(pthread_join(tid, NULL) != 0){
		perror("error to join server thread: ");
		exit(-1);
	}
	remove(PUBLIC);
	exit(1);
		


}