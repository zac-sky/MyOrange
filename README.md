## 10.1
安装Ubuntu虚拟机 ing  
简单进行了windows下服务端开发的尝试  
了解了一些socket语句  
learn了cerr和cout的区别：cerr用于错误的输出，会立即显示不会存储在缓存区  
了解了socket和端口的关系：SOCKET 表示连接，端口则用于标识通信的特定通道，socket相当于一个通信端点  
WSAStartup：Windows Sockets API中初始化Winsock库的函数  

sin:socket internet  (sin_family)    
fd:file descriper(文件描述符)  
AF_INET:常量，表示 Address Family (地址族)，用于指定 Internet 协议版本 4（IPv4）  
AF_INET6：表示 IPv6 地址族，用于支持 IPv6 网络协议。  
AF_UNIX：表示 Unix 域套接字，用于同一主机内的进程间通信。  
> Unix 域套接字:用于在同一台计算机上的不同进程之间进行通信，而不需要通过网络协议（如 TCP/IP）进行。它提供了高效且可靠的进程间通信（IPC）机制。
SOCK_STREAM :一个常量，用于指定在创建套接字时所需的 socket类型，它表示一个面向连接的流式套接字。主要用于 TCP（传输控制协议），它提供可靠的、双向的字节流通信。  

| 套接字类型         | 连接性   | 可靠性  | 数据边界  | 适用场景                       |
|-------------------|----------|---------|-----------|--------------------------------|
| `SOCK_STREAM`     | 面向连接 | 可靠    | 无        | Web 浏览器、文件传输、聊天应用 |
| `SOCK_DGRAM`      | 无连接   | 不可靠  | 有        | 实时应用、DNS 查询             |
| `SOCK_RAW`        | 无连接   | 不适用  | 无        | 网络监控、自定义协议           |

## 10.2
git的使用，换了clash  
在Ubuntu下进行了服务端和客户端的搭建  
简易的服务端：创建socket->端口复用->配置服务器地址->绑定(bind)socket->listen->accept连接->read请求->close  
简易的客户端：创建套接字-> 配置服务器地址->connect到服务端->send发送请求->read接收服务器的响应->close关闭套接字  
SDS实现：创建SDS类用char和长度来动态表示一个字符串  

htons(): Host TO Network Short 将主机字节序的 16 位端口号转换为网络字节序。  
htonl(): Host TO Network Long 将主机字节序的 32 位整数转换为网络字节序。  
ntohs(): Network TO Host Short 将网络字节序的 16 位端口号转换为主机字节序。  
ntohl(): Network TO Host Long 将网络字节序的 32 位整数转换为主机字节序。  

## 10.4

```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 5001

int main()
{
    int sockfd, newsockfd;
    char *message = "hello there, client!";
    char buffer[8000];

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.13");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Socket opening error");
        return -1;
    }

    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Binding error");
        return -1;
    }

    listen(sockfd, 3);

    int socksize = sizeof(struct sockaddr_in);
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&server_address, &socksize)) < 0)
    {
        perror("Connection accept error");
        return -1;
    }

    recv(newsockfd, &buffer, sizeof(buffer), 0);
    printf("Client message: %s\n", buffer);

    send(newsockfd, message, strlen(message), 0);

    close(newsockfd);
    close(sockfd);
    return 0;
}
```

头文件；
#include <sys/socket.h>: 这个头文件包含了 socket 编程相关的函数，如 socket()、connect() 等。  
#include <netinet/in.h>: 提供了 sockaddr_in 结构体及相关函数，用于定义 IPv4 地址和端口号。  
#include <arpa/inet.h>: 包含了函数 inet_addr()，用于处理 IP 地址的转换。  
#include <string.h>: 包含了字符串处理函数，如 strlen()。  
#include <unistd.h>: 提供了 POSIX 操作系统接口函数，如 close() 用于关闭文件描述符（这里是 socket）。  
#include <stdio.h>: 提供了标准输入输出函数，如 printf() 和 perror()。  


> POSIX（可移植操作系统接口）是一个标准，它定义了一组接口和行为，旨在使应用程序能够在不同的操作系统上进行移植。POSIX 接口主要是为 UNIX 系统及其衍生版本设计的，但许多现代操作系统（如 Linux、BSD、macOS 等）都支持这一标准。

> POSIX 接口函数的主要类别包括：
文件操作函数：
> open(): 打开文件。
> close(): 关闭文件。
> read(): 读取文件。
> write(): 写入文件。
> lseek(): 移动文件指针。
> unlink(): 删除文件。
> 进程控制函数：
> fork(): 创建新进程。
> exec(): 执行新程序。
> wait(): 等待子进程结束。
> exit(): 终止进程。
> 线程管理函数：
> pthread_create(): 创建线程。
> pthread_join(): 等待线程结束。
> pthread_mutex_lock(): 锁定互斥锁。
> pthread_cond_wait(): 等待条件变量。
> 信号处理函数：
> signal(): 设置信号处理函数。
> sigaction(): 更加复杂的信号处理设置。
> kill(): 发送信号给进程。
> 定时和延时函数：
> sleep(): 暂停进程执行。
> nanosleep(): 以纳秒为单位暂停进程执行。
> 网络编程函数：
> socket(): 创建套接字。
> bind(): 绑定套接字到地址。
> listen(): 监听连接请求。
> accept(): 接受连接请求。
> connect(): 发起连接。  
> POSIX 标准的意义  
>> 可移植性：使用 POSIX 标准的应用程序可以在符合该标准的操作系统上编译和运行，减少了因操作系统不同而导致的兼容性问题。
>> 一致性：提供了一致的接口，使得开发者在不同平台上开发时能减少学习成本。

<netinet/in.h> 头文件包含了处理网络地址的定义和一些网络协议的相关常量，用于支持基于 IP（特别是 IPv4 和 IPv6）的网络编程。它提供了一些关键的数据结构和宏  
> 常见的结构和宏：

struct sockaddr_in：用于表示 IPv4 地址的结构体，常用于定义套接字绑定或连接的地址。
```cpp
struct sockaddr_in {
    sa_family_t    sin_family;  // 地址族 (AF_INET)
    in_port_t      sin_port;    // 端口号 (使用 htons() 来转换字节序)
    struct in_addr sin_addr;    // IP 地址
};
```
struct sockaddr_in6：用于表示 IPv6 地址的结构体。

struct in_addr：用于存储 IPv4 地址。
```cpp
struct in_addr {
    uint32_t s_addr;  // 32 位 IPv4 地址 (使用 inet_addr() 等函数设置)
};

```
INADDR_ANY：表示通配的 IPv4 地址，通常用于服务器套接字，表示绑定到所有可用的网络接口。

htons() 和 ntohs()：用于在主机字节序和网络字节序之间转换 16 位短整数（通常用于端口号）。

inet_addr() 和 inet_ntoa()：用于在点分十进制的 IPv4 地址和二进制格式之间进行转换。

client_address.sin_port = htons(PORT): 设置客户端的端口号，htons() 函数将端口号转换为网络字节序（大端格式）。  
为什么需要转换：  
在网络通信中，不同的计算机系统可能使用不同的字节序来存储数据。为了确保在网络上传输的数据能够被接收方正确解析，使用 htons 函数将主机字节序的端口号转换为网络字节序是必需的。好处：  
跨平台兼容性：确保无论发送方和接收方使用什么类型的系统，数据都能正确解析。  
符合协议规范：网络协议通常要求使用特定的字节序（大端字节序），通过转换来符合这些要求。  

监听套接字 (sockfd) 和 连接套接字 (newsockfd)：
监听套接字是服务器端创建的用于接收客户端连接请求的套接字。监听套接字主要用于等待和接收来自客户端的连接请求。它会监听指定端口，直到有客户端请求连接。
连接套接字是服务器在接受客户端连接后创建的套接字，用于与特定客户端进行数据通信。连接套接字用于实际的数据传输，包括发送和接收消息。每个连接套接字与其相应的客户端保持独立，因此服务器可以处理多个客户端连接。




## 10.5
SDS优点：
1. 自动管理内存    
2. 预留额外空间以减少内存重分配    
3. 存储字符串长度  
4. 二进制安全  
5. 防止缓冲区溢出  
6. 更丰富的字符串操作  
7. 适合动态处理  

sockaddr和sockaddr_in类型
sockaddr  
定义: sockaddr 是一个通用的地址结构，适用于多种地址类型（例如 IPv4 和 IPv6）。  
用途: 用于创建一个可以处理不同类型地址的统一接口。  
sockaddr_in  
定义: sockaddr_in 是专门用于 IPv4 地址的结构体。  
用途: 主要用于 IPv4 网络编程，包含更多与 IPv4 地址相关的字段。  
sockaddr 是一个基础的通用结构，而 sockaddr_in 是它的一个特定实现，用于处理 IPv4 地址。   



编译命令：  
g++ -c sds.cpp -o sds.o  
g++ -c db.cpp -o db.o  
g++ server.cpp db.o sds.o -o server  
g++ client.cpp db.o sds.o -o client  
