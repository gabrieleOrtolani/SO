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

void *client_thread(void* arg){
        int fd, ret, rd;
        char request[1];
        printf("client thread sta creando la fifo client... \n");
         if((ret=mkfifo((char*)arg,0660))==-1){
                 perror("errot to make server_fifo: ");
                 exit(-1);
         }
         printf("client thread sta aprendo la fifo client in lettura... \n");
         if((fd=open((char*)arg,O_RDONLY))==-1){
                 perror("error to open server_fifo: ");
                 exit(-1);
         }
         printf("client thread sta in attesa.. \n");
         if((rd=read(fd,request,sizeof(request)))==-1){
                 perror("error during read in client thread: ");
                 exit(-1);
         }
         printf("contatore: %s\n",request);
        char response[1]="1";
        close(fd);
        sleep(1);
        int wr;
         printf("client thread sta aprendo la fifo client in scrittura... \n");
         if((fd=open((char*)arg,O_WRONLY))==-1){
                 perror("error to open server_fifo: ");
                 exit(-1);
         }
         printf("client thread invia la response..\n");
         if((wr=write(fd,response,sizeof(response)))==-1){
                 perror("error during read in client thread: ");
                 exit(-1);
         }
         close(fd);
        printf("contatore:%s\n",response);
        pthread_exit(NULL);
}



int main(int argc, char *argv[]){
        
        int client_number = atoi(argv[1]);
        int fd, wr;
        char client_fifo[12]="client_fifo";
        pthread_t tid;
        if((fd=open(PUBLIC,O_WRONLY))==-1){
                perror("client main errro open server_fifo: ");
                exit(-1);
        }
        printf("il client ha aperto la fifo del server...\n");

        if((wr=write(fd,client_fifo,sizeof(client_fifo)))==-1){
                perror("error during write in server fifo: ");
                exit(-1);
        }
        printf("il client manda al server il nome della fifo: %s, %d\n", client_fifo,wr);
      

        printf("il client passa il controllo al thread client...\n");
        if((pthread_create(&tid,NULL,client_thread,(void*)client_fifo))!=0){
                perror("error create client thread: ");
                exit(-1);
        }
        
        sleep(5);
        if((pthread_join(tid,NULL))!=0){
                perror("join thread in main error: ");
                exit(-1);
        }
        
        exit(1);




}
