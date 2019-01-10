#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  /* netdb is necessary for struct hostent */

#define PORT 2222   /* server port */

#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int sockfd, num;    /* files descriptors */
    char buf[MAXDATASIZE];    /* buf will store received text */
    struct hostent *he;    /* structure that will get information about remote host */
    struct sockaddr_in server;
    char name[] = "127.0.0.1\n";
    char *server_ip = "127.0.0.1";//name; 
    if (argc == 2)
    {
        server_ip = argv[1];    
    }

    if((he=gethostbyname(server_ip))==NULL)
    {
        printf("gethostbyname() error\n");
        exit(1);
    }
    if((sockfd=socket(AF_INET,SOCK_STREAM, 0))==-1)
    {
        printf("socket() error\n");
        exit(1);
    }
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server))==-1)
    {
        printf("connect() error\n");
        exit(1);
    }
    printf("connect success\n"); 
    char str[] = "hello my babe!\n";

    if((num=send(sockfd,str,sizeof(str),0))==-1){
        printf("send() error\n");
        exit(1);
    }
    if((num=recv(sockfd,buf,MAXDATASIZE,0))==-1)
    {
        printf("recv() error\n");
        exit(1);
    }
    buf[num-1]='\0';
    printf("server message: %s\n",buf);
    sleep(3);
    close(sockfd);
    return 0;
}