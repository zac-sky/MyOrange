#include <sys/socket.h>    // socket, bind ...
#include <netinet/in.h>    // (TCP/IP) sockaddr_in, htons...
#include <arpa/inet.h>     // inet_addr()...
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "database.h"

#define PORT 6666
#define BUFFER_SIZE 1024

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server_address, client_address;
    socklen_t addr_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];

    // 创建 socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket create error");
        close(sockfd);
        return -1;
    }

    // 初始化服务器地址结构体
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY:表示服务器将绑定到所有可用的网络接口上
    /* 在追溯这个s_addr... 
        typedef uint32_t in_addr_t;
        struct in_addr
        {  
            in_addr_t s_addr;
        };

        struct sockaddr_in {
            short sin_family;  // 地址族 (AF_INET)
            unsigned short sin_port;    // 端口号 (使用 htons() 来转换字节序)
            struct in_addr sin_addr;    // IP 地址
            char sin_zero[8];
        };
    */   
    // 绑定 socket
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind error");
        close(sockfd);
        return -1;
    }

    // 开始监听客户端连接
    listen(sockfd, 3);
    printf("Listening on port %d...\n", PORT);

    // 接受客户端连接
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&client_address, &addr_len)) < 0) {
        perror("Connection error");
        close(sockfd);
        return -1;
    }

    // 接收客户端数据
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);  // 给前 SIZE 个元素赋值 0
        int n = recv(newsockfd, buffer, BUFFER_SIZE - 1, 0);
        if (n <= 0) break;  // 检查接收的字节数

        buffer[n] = '\0';  // 添加字符串结束符
        printf("Received command: %s", buffer);
        process_command(buffer);  // 处理接收到的命令
    }

    close(newsockfd);  // 关闭客户端 socket
    close(sockfd);     // 关闭服务器 socket
    return 0;
}
