#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define BUF_SIZE 30
#define TTL 64

void error_handling(char *message);
 
int main(int argc, char *argv[])
{
    int send_sock;
    struct sockaddr_in multi_addr;
    int time_live=TTL;
    FILE* fp;
    char buf[BUF_SIZE];

    if (argc != 3) {
        printf("Usage : %s <group IP> <port>\n", argv[0]);
        exit(1);
    }

    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&multi_addr, 0, sizeof(multi_addr));
    multi_addr.sin_family = AF_INET;
    multi_addr.sin_addr.s_addr = inet(argv[1]);  //多播IP
    multi_addr.sin_port = htons(atoi(argv[2]));  //多播端口
 
    setsockopt(send_sock,IPPROTO_IP,IP_MULTICAST_TTL,(void*) &time_live,sizeof(time_alive));
    if((fp=fopen("news.txt","r"))==NULL)
	error_handling("fopen() error");

    while(!feof(fp)){
	fgets(buf,BUF_SIZE,fp);
	sendto(send_sock,buf,strlen(buf),0,(struct sockaddr*) &multi_addr,sizeof(multi_addr));
	sleep(2);
    }
    fclose(fp);
    close(send_sock);
    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
