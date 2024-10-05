#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define PORT 6666
#define BUFFER_SIZE 1024



int main(){
    int sockfd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    /*
    struct sockaddr_in {
        short sin_family;  // 地址族 (AF_INET)
        unsigned short sin_port;    // 端口号 (使用 htons() 来转换字节序)
        struct in_addr sin_addr;    // IP 地址
        char sin_zero[8];
    };
    */

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Socket create error");
        close(sockfd);
        return -1;
    }

    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(PORT);
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1"); 

    if(connect(sockfd,(struct sockaddr *)&server_address,sizeof(server_address))<0){
        perror("Connection error");
        close(sockfd);
        return -1;
        
    }

    while(1){
        printf("Please enter your command : ");
        fgets(buffer,BUFFER_SIZE-1,stdin);   //  -1: \0
        send(sockfd,buffer,strlen(buffer),0);
    }

    close(sockfd);
}