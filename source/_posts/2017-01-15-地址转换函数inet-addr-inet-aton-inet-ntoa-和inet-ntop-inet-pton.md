---
title: '地址转换函数inet_addr(), inet_aton(), inet_ntoa()和inet_ntop(), inet_pton()'
categories: 网络编程
tags:
  - UNIX/Linux
  - 网络编程
abbrlink: 58114
date: 2017-01-15 16:43:01
---


对于地址转换函数，BSD网络软件包含inet_addr(), inet_aton()和inet_ntoa()三个函数用于二进制地址格式与点分十进制之间的相互转换，但是仅仅适用于IPv4，两个新函数inet_ntop()和inet_pton()具有相似的功能，并且同时支持IPv4和IPv6。

<!--more-->

## inet_addr(), inet_aton()和inet_ntoa()函数
### inet_addr()函数

**功能**：inet_addr()函数用于将点分十进制IP地址转换成网络字节序IP地址;
**原型**：`in_addr_t inet_addr(const char *cp)`;
**返回值**：如果正确执行将返回一个无符号长整数型数。如果传入的字符串不是一个合法的IP地址，将返回INADDR_NONE;
**头文件**：arpa/inet.h (Linux) 

### inet_aton()函数

**功能**：inet_aton()函数用于将点分十进制IP地址转换成网络字节序IP地址;
**原型**：`int inet_aton(const char *string, struct in_addr *addr)`;
**返回值**：如果这个函数成功，函数的返回值非零，如果输入地址不正确则会返回零;
**头文件**：sys/socket.h (Linux)

### inet_ntoa()函数

**功能**inet_ntoa()函数用于网络字节序IP转化点分十进制IP;
**原型**：`char *inet_ntoa (struct in_addr)`;
**返回值**：若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL。其中的数据应在下一个WINDOWS套接口调用前复制出来;
**头文件**：arpa/inet.h (Linux)

### 应用实例
代码
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int i;
    char lo[] = "127.0.0.1";
    struct in_addr netAddr;
    netAddr.s_addr = inet_addr(lo);
    printf("NetIP: 0x%x\n", netAddr.s_addr);
    char *strAddr = inet_ntoa(netAddr);
    printf("StrIP: %s\n", strAddr);
    int ret = inet_aton(strAddr, &netAddr);
    printf("NetIP: 0x%x\n", netAddr.s_addr);
    return 0;
}
```
输出结果：
```
NetIP: 0x100007f(网络序)
StrIP: 127.0.0.1
NetIP: 0x100007f(网络序)
```

## inet_ntop()和inet_pton()函数
### inet_ntop()函数

**功能**：inet_ntop()函数用于将网络字节序的二进制地址转换成文本字符串;
**原型**：`const char *inet_pton(int domain, const void *restrict addr, char *restrict str, socklen_t size)`;
**返回值**：若成功，返回地址字符串指针；若出错，返回NULL;
**头文件**：arpa/inet.h (Linux)

### inet_pton()函数

**功能**：inet_pton()函数用于将文本字符串格式转换成网络字节序二进制地址;
**原型**：`int inet_pton(int domain, const char *restrict str, void *restrict addr)`;
**返回值**：若成功，返回1；若格式无效，返回0；若出错，返回-1;
**头文件**：arpa/inet.h (Linux)

### 应用实例
代码
```
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    struct in_addr addr;
    if(inet_pton(AF_INET, "127.0.0.1", &addr.s_addr) == 1)
        printf("NetIP: %x\n", addr.s_addr);
    char str[20];
    if(inet_ntop(AF_INET, &addr.s_addr, str, sizeof str))
        printf("StrIP: %s\n", str);
    return 0;
}
```

输出结果：
```
NetIP: 100007f
StrIP: 127.0.0.1
```


