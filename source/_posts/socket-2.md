# 原始套接字(2)
### 在原始套接字学习的过程中，也遇到了一系列的问题，其中不乏自己粗心大意，也有各种没有注意的错误，这里着重写出，并保持持续的更新。

## fgets()函数问题

　　在使用套接字搭建聊天程序的时候，我在这里使用了一个`fgets()`函数来保存键盘的输入，具体代码如下：

```c
char Buffer[100];
while(fgets(sendbuf,sizeof(sendbuf),stdin)!=0)
{
    sendto(sock,&Buffer,sizeof(Buffer),0,(struct sockaddr *)addr,sizeof(addr));
    bzero(Buffer,sizeof(Buffer));       
}
```

　　这里需要注意的问题是，由于`fgets()`函数是以回车键的输入来判定结束的，与此同时，回车键`\n`也会作为最后一个字符输入到Buffer中，所以这里在处理一些数据的时候需要注意。
## socket()建立问题

　　在`socket()`构建的过程中，往往跟随一个判定建立成功与否的`perror()`语句，这里建议的写法是：
```c
int sockfd;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
{
    perror("socket created error");   
}
```
不推荐的写法是：
```c
int sockfd;
if(sockfd=socket(AF_INET,SOCK_DGRAM,0)<0)
{
    perror("socket created error");   
}
```
　　这种写法很有可能会导致你的socket建立失败，而且程序还不会报错，所以小心一点这里尽量多写一句吧，养成良好的代码习惯。
## strlen()函数和sizeof()函数

　　`strlen()`：`strlen()`所作的仅仅是一个计数器的工作，它从内存的某个位置`(`可以是字符串开头，中间某个位置，甚至是某个不确定的内存区域`)`开始扫描，直到碰到第一个字符串结束符`\0`为止，然后返回计数器值(长度不包含`\0`)。

　　`sizeof()`：`sizeof()`是`C/C++`中的一个操作符`operator`，简单的说其作用就是返回一个对象或者类型所占的内存字节数。

　　这两个函数在使用过程中要注意，`strlen()`主要是计数功能，遇到`\0`后就停止计数返回数字，而`sizeof()`则返回该对象所占的内存字节数。

　　下面给出一个小测试程序供参考：

```c
#include<stdio.h>
#include<string.h>
int main()
{
    char s[22]="i love you!\0";
    printf("%s\n",s);
    printf("%d\n",strlen(s));
    return 0;
}
```

layout: '[post]'
title: socket_2
date: 2016-03-29 17:34:22
tags:
---
