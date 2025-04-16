---
title: 地址查询函数gethostbyname()和getaddrinfo()
categories: 网络编程
tags:
  - UNIX/Linux
  - 网络编程
abbrlink: 29843
date: 2017-01-16 11:08:20
---

地址查询函数的功能也就是通过主机名或者域名返回详细的主机信息，其中我们最常用的功能就是通过主机名获得主机的IP地址等信息。gethostbyname()和其可重入版本gethostbyname_r()是我们之前较多使用的函数，由于SUSv4已经删除了它们并认为它们已经是过时的了，现在我们更推荐使用getaddrinfo()来完成相应的功能。

<!--more-->

## gethostbyname()函数
### 函数原型
```
struct hostent *gethostbyname(const char *name);
```
**功能**：用域名或主机名获取IP地址
**头文件**：`<netdb.h>`, `<sys/socket.h>`

### hostent结构体
hostent的结构如下所示：
```
struct hostent
{
    char    *h_name;//主机的规范名               
    char    **h_aliases;//主机的别名
    int     h_addrtype;//主机ip地址的类型
    int     h_length;//主机ip地址的长度
    char    **h_addr_list;//主机的ip地址
    #define h_addr h_addr_list[0];
};
```
### 代码实例
代码
```
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("ERROR: usage %s\n", argv[0]);
        return 1;
    }

    char *ptr, **pptr;
    char buf[1024];
    struct hostent *hent;
    if((hent = gethostbyname(argv[1])) == NULL)
    {
        printf("ERROR: gethostbyname error for hostname: %s\n", argv[1]);
        return 0;
    }

    printf("Official hostname: %s\n", hent->h_name);
    for(pptr = hent->h_aliases; *pptr != NULL; pptr++)
        printf("Alias hostname: %s\n", *pptr);

    printf("Host Address Type: %d(AF_INET: %d)\n", hent->h_addrtype, (int)AF_INET);

    for(pptr = hent->h_addr_list; *pptr != NULL; pptr++)
    {
        printf("IP Address: %s\n", inet_ntop(hent->h_addrtype, *pptr, buf, sizeof buf));
    }
    return 0;
}
```

执行结果：
```
./a.out www.baidu.com

Official hostname: www.a.shifen.com
Alias hostname: www.baidu.com
Host Address Type: 2(AF_INET: 2)
IP Address: 61.135.169.125
IP Address: 61.135.169.121
```

## gethostbyname_r()函数
gethostbyname_r()函数是gethostbyname()函数的可重入版本，两个函数的功能是一样的。
### gethostbyname_r()函数原型
```
int gethostbyname_r(const char *name,
               struct hostent *ret, char *buf, size_t buflen,
               struct hostent **result, int *h_errnop);
```
**功能**：用域名或主机名获取IP地址
**头文件**：`<netdb.h>`, `<sys/socket.h>`

### 代码实例
代码
```
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("ERROR: usage %s\n", argv[0]);
        return 0;
    }
    char *ptr, **pptr;
    struct hostent hent, *hptr;
    char buf[1024];
    int ret;

    if(gethostbyname_r(argv[1], &hent, buf, sizeof(buf), &hptr, &ret))
    {
        printf("ERROR: gethostbyname_r(%s) ret: %d\n", argv[1], ret);
        return 0;
    }
    printf("Get host by name(%s) success!\n", argv[1]);
    printf("Official hostname: %s\n", hptr->h_name);
    for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
        printf("Alias hostname: %s\n", *pptr);
    printf("Host Address Type: %d(AF_INET: %d)\n", hptr->h_addrtype, (int)AF_INET);
    for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
        printf("IP Address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, buf, sizeof buf));
    return 0;
}
```

执行结果
```
./a.out www.baidu.com

Get host by name(www.baidu.com) success!
Official hostname: www.a.shifen.com
Alias hostname: www.baidu.com
Host Address Type: 2(AF_INET: 2)
IP Address: 61.135.169.125
IP Address: 61.135.169.121
```

## getaddrinfo()函数
getaddrinfo()函数是现在用来替代gethostbyname()功能的函数，他具有更加强大的功能。

### getaddrinfo()函数原型
```
int getaddrinfo(const char *restrict host, 
                const char *restrict service,
                const struct addrinfo *restrict hint,
                struct addrinfo **restrict res);
                        返回值：若成功，返回0；若出错，返回非0错误码
```
**功能**：用主机名或服务名获取IP地址
**头文件**：`<netdb.h>`, `<sys/socket.h>`

### 代码实例
代码
```
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void print_family(struct addrinfo *aip)
{
    printf("Family:");
    switch (aip->ai_family) {
    case AF_INET:
        printf("inet");
        break;
    case AF_INET6:
        printf("inet6");
        break;
    case AF_UNIX:
        printf("unix");
        break;
    case AF_UNSPEC:
        printf("unspecified");
        break;
    default:
        printf("unknown");
    }
}

void print_type(struct addrinfo *aip)
{
    printf(" Type:");
    switch (aip->ai_socktype) {
    case SOCK_STREAM:
        printf("stream");
        break;
    case SOCK_DGRAM:
        printf("datagram");
        break;
    case SOCK_SEQPACKET:
        printf("seqpacket");
        break;
    case SOCK_RAW:
        printf("raw");
        break;
    default:
        printf("unknown (%d)", aip->ai_socktype);
    }
}

void print_protocol(struct addrinfo *aip)
{
    printf(" Protocol:");
    switch (aip->ai_protocol) {
    case 0:
        printf("default");
        break;
    case IPPROTO_TCP:
        printf("TCP");
        break;
    case IPPROTO_UDP:
        printf("UDP");
        break;
    case IPPROTO_RAW:
        printf("raw");
        break;
    default:
        printf("unknown (%d)", aip->ai_protocol);
    }
}

void print_flags(struct addrinfo *aip)
{
    printf(" Flags:");
    if (aip->ai_flags == 0) {
        printf(" 0");
    } else {
        if (aip->ai_flags & AI_PASSIVE)
            printf(" passive");
        if (aip->ai_flags & AI_CANONNAME)
            printf(" canon");
        if (aip->ai_flags & AI_NUMERICHOST)
            printf(" numhost");
        if (aip->ai_flags & AI_NUMERICSERV)
            printf(" numserv");
        if (aip->ai_flags & AI_V4MAPPED)
            printf(" v4mapped");
        if (aip->ai_flags & AI_ALL)
            printf(" all");
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("ERROR: usage %s\n", argv[0]);
        return 0;
    }
    struct addrinfo *ai, *aip;
    struct addrinfo hint;
    struct sockaddr_in *sinp;
    const char *addr;
    int err;
    char buf[1024];

    hint.ai_flags = AI_CANONNAME;
    hint.ai_family = 0;
    hint.ai_socktype = 0;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if((err = getaddrinfo(argv[1], NULL, &hint, &ai)) != 0)
        printf("ERROR: getaddrinfo error: %s\n", gai_strerror(err));
    for(aip = ai; aip != NULL; aip = aip->ai_next)
    {
        print_family(aip);
        print_type(aip);
        print_protocol(aip);
        print_flags(aip);
        printf("\n");
        printf("Canonical Name: %s\n", aip->ai_canonname);
        if(aip->ai_family == AF_INET)
        {
            sinp = (struct sockaddr_in *)aip->ai_addr;
            addr = inet_ntop(AF_INET, &sinp->sin_addr, buf, sizeof buf);
            printf("IP Address: %s ", addr);
            printf("Port: %d\n", ntohs(sinp->sin_port));
        }
        printf("\n");
    }
    return 0;
}
```

执行结果：
```
./a.out www.baidu.com


Family:inet Type:stream Protocol:TCP Flags: canon
Canonical Name: www.a.shifen.com
IP Address: 61.135.169.125 Port: 0

Family:inet Type:datagram Protocol:UDP Flags: canon
Canonical Name: (null)
IP Address: 61.135.169.125 Port: 0

Family:inet Type:raw Protocol:default Flags: canon
Canonical Name: (null)
IP Address: 61.135.169.125 Port: 0

Family:inet Type:stream Protocol:TCP Flags: canon
Canonical Name: (null)
IP Address: 61.135.169.121 Port: 0

Family:inet Type:datagram Protocol:UDP Flags: canon
Canonical Name: (null)
IP Address: 61.135.169.121 Port: 0

Family:inet Type:raw Protocol:default Flags: canon
Canonical Name: (null)
IP Address: 61.135.169.121 Port: 0
```
