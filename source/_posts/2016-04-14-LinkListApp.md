layout: '[post]'
title: 链表功能函数总结
date: 2016-04-14 00:40:17
tags: [LinkList, 链表]
categories: 数据结构
---

最近在学习数据结构的内容，链表（LinkList）就是数据结构中最基本的一种数据类型，链表本身的构造特性也特别有意思，这里就构造了一个链表的功能函数，包含了链表的**创建初始化、打印输出、计算长度、查找中间结点和清除链表**等功能，在今后的学习中会不断扩充添加不同的功能！
函数运行如下图所示：

![LinkList][1]

<!--more-->

## 功能函数

### 链表创建函数
```c
//声明链表创建函数（尾插法）
void ListCreat(LinkList *L, int n)
{
    LinkList *p, *r;
    int i;
    srand(time(0));
    p = L;
    for(i = 0; i < n; i++)
    {
        r = (LinkList *)malloc(sizeof(LinkList));
        p->data = rand() % 100 + 1;
        p->next = r;
        p = r;
    }
    p->next = NULL;
}
```
这里使用了尾插法对链表进行生成操作，使用`rand()`函数生成随机数对链表进行初始化。

### 链表打印函数
```c
//打印链表函数
ListPrint(LinkList *L)
{
    LinkList *p;
    p = L;
    while(p->next != NULL)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}
```
通过判定`p->next`是否为`NULL`为条件对链表进行遍历打印。

### 获取链表长度
```c
//声明一个函数，获取链表长度
int ListLength(LinkList *L)
{
    LinkList *p;
    p = L;
    int count = 0;
    while(p->next != NULL)
    {
        p = p->next;
        count++;
    }
    return count;
}
```
同上，通过判定`p->next`是否为`NULL`为条件对链表进行遍历计算链表的长度。

### 获取中间结点
```c
//声明一个函数，获取链表中间结点
int ListMid(LinkList *L)
{
    LinkList *cur, *mid;
    cur = mid = L;
    while(cur->next != NULL)
    {
        if(cur->next->next != NULL)
        {
            mid = mid->next;
            cur = cur->next->next;
        }
        else
        {
            cur = cur->next;
        }
    }
    return mid->data;
}
```
设置`cur`的步长为2，`mid`的步长为1，同时对链表进行遍历，以`cur == NULL`为结束条件，可以以较高的效率得到链表的中间结点。

### 链表清除
```c
//声明链表清理函数
void ListClear(LinkList *L)
{
    LinkList *p;
    p = L;
    while(L->next != NULL)
    {
        L = p->next;
        free(p);
        p = L;
    }
    free(L);
}
```
使用`free()`函数对我们生成的链表空间进行遍历删除。

---
## 总体代码
```c
#include <stdio.h>
#include <stdlib.h>
//声明链表结构体
typedef struct node
{
    int data;
    struct node *next;
}LinkList;
//声明链表创建函数（尾插法）
void ListCreat(LinkList *L, int n)
{
    LinkList *p, *r;
    int i;
    srand(time(0));
    p = L;
    for(i = 0; i < n; i++)
    {
        r = (LinkList *)malloc(sizeof(LinkList));
        p->data = rand() % 100 + 1;
        p->next = r;
        p = r;
    }
    p->next = NULL;
}
//打印链表函数
ListPrint(LinkList *L)
{
    LinkList *p;
    p = L;
    while(p->next != NULL)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}
//声明一个函数，获取链表长度
int ListLength(LinkList *L)
{
    LinkList *p;
    p = L;
    int count = 0;
    while(p->next != NULL)
    {
        p = p->next;
        count++;
    }
    return count;
}
//声明一个函数，获取链表中间结点
int ListMid(LinkList *L)
{
    LinkList *cur, *mid;
    cur = mid = L;
    while(cur->next != NULL)
    {
        if(cur->next->next != NULL)
        {
            mid = mid->next;
            cur = cur->next->next;
        }
        else
        {
            cur = cur->next;
        }
    }
    return mid->data;
}
//声明链表清理函数
void ListClear(LinkList *L)
{
    LinkList *p;
    p = L;
    while(L->next != NULL)
    {
        L = p->next;
        free(p);
        p = L;
    }
    free(L);
}
//主函数
int main()
{
    printf("1.生成链表\n");
    printf("2.打印链表\n");
    printf("3.获取链表长度\n");
    printf("4.获取中间结点\n");
    printf("5.清楚链表\n");
    printf("0.退出\n");
    LinkList *L;
    L = (LinkList *)malloc(sizeof(LinkList));
    int length = 10;
    char operator;
    while(1)
    {
        scanf("%c", &operator);
        switch(operator)
        {
            case '1':
                printf("**********生成链表***********\n");
                ListCreat(L, length);
                break;
            case '2':
                printf("**********打印链表**********\n");
                ListPrint(L);
                break;
            case '3':
                printf("********获取链表长度********\n");
                printf("The length of this ListCreat is: %d\n", ListLength(L));
                break;
            case '4':
                printf("********获取中间结点********\n");
                printf("The value of the middle node is: %d\n", ListMid(L));
                break;
            case '5':
                ListClear(L);
                printf("**********清楚完毕**********\n");
                break;
            case '0':
                printf("************退出************\n");
                return 0;
        }
    }
    return 0;
}
```


---


  [1]: https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2016-04-14/LinkList.gif
