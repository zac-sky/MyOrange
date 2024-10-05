#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>

#include "sds.h"
#include "db.h"


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
    server_address.sin_addr.s_addr = INADDR_ANY;

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
        memset(buffer, 0, BUFFER_SIZE);
        int n = recv(newsockfd, buffer, BUFFER_SIZE - 1, 0);
        if (n <= 0) break;

        buffer[n] = '\0';
        printf("Received command: %s", buffer);
        process_command(buffer);
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
