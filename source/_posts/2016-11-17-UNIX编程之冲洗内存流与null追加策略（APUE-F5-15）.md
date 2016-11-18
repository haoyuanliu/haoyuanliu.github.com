layout: '[post]'
title: UNIX编程之冲洗内存流与null追加策略（APUE F5-15）
date: 2016-11-17 22:51:06
tags: [APUE, 5-15, UNIX, Linux]
categories: UNIX/Linux
---

最近一直在拜读APUE(Advanced Programming in the UNIX Environment)，在读到标准I/O库的时候，对于**图 5-15**的代码和内存流的写入方式发现冲洗内存流和`null`字节的追加策略书上没有说明白，到底是如何追加‘null`字节的，调用`fclose`为什么没有追加`null`字节等等，对于这一系列问题通过代码测试终于搞清楚整体的写入追加策略，特此记录一下。
解决问题的关键在于书上这一句话：
> * 任何时候需要增加流缓冲区中的数据量以及调用fclose、fflush、fseek、fseeko以及fsetpos时都会在当前位置写入一个`null`字节！

看似是一旦调用`fclose`就要追加`null`，可以书上给的例子可不是这样哦，下面随着文章我们来一步一步地分析。
<!--more-->
## 内存流写入代码
```
#include "apue.h"

#define BSZ 48

int main()
{
	FILE *fp;
	char buf[BSZ];

	memset(buf, 'a', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
		err_sys("fmemopen failed");
	printf("Initial buffer contents: %s\n", buf);
	fprintf(fp, "hello, world"); //写进缓存
	printf("Before flush: %s\n\n", buf);
	fflush(fp); //调用fflush、fclose、、fseek、fseeko、fsetpos会在当前位置添加null
	printf("After fflush: %s\n", buf);
	printf("Len of string in buf = %ld\n\n", (long)strlen(buf));

	memset(buf, 'b', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello, world");
	fseek(fp, 0, SEEK_CUR); //保持偏移值冲洗之后的位置
	printf("After  fseek: %s\n", buf);
	printf("Len of string in buf = %ld\n\n", (long)strlen(buf));

	memset(buf, 'c', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello, world"); //继续写进去
	fseek(fp, 0, SEEK_SET); //偏移值设为缓冲区开始位置
	printf("After fseek: %s\n", buf);
	printf("Len of string in buf = %ld\n\n", (long)strlen(buf));

	memset(buf, 'd', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello, world"); //继续写进去
	fclose(fp); //然后fclose在当前位置也就是数据尾端添加一个null
	printf("After close: %s\n", buf);
	printf("Len of string in buf = %ld\n", (long)strlen(buf));

	return(0);
}
```

程序执行的结果为：
```
Initial buffer contents:
Before flush:

After fflush: hello, world
Len of string in buf = 12

After  fseek: bbbbbbbbbbbbhello, world
Len of string in buf = 24

After fseek: cccccccccccccccccccccccchello, world
Len of string in buf = 36

After close: hello, worlddddddddddddddddddddddddddddddddddd
Len of string in buf = 46
```

## 写入操作分析
首先是使用a字符修改缓冲区：
```
memset(buf, 'a', BSZ-2);
buf[BSZ-2] = '\0';
buf[BSZ-1] = 'X';
```
此时得到的`buf`应该是：
> * aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa0X
为了识别方便，这里每隔5个字符使用一个`+`隔开显示，如下所示：
> * aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + a0X
> * 此时偏移值指向数据末尾，即offset = 47

然后执行：
```
if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
		err_sys("fmemopen failed");
```
流控制参数为`w+`，`fmemopen`函数在缓冲区开始处放置了`null`字节，此时的`buf`应该是：
> * `null`+ aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + 0X
> * 因为首字符即为`null`，此时打印结果为空；
> * 此时偏移值指向缓冲区开始`null`字节处，即offset = 0

然后通过`fprintf`函数写入数据，并使用`fflush`函数冲洗缓冲区：
```
fprintf(fp, "hello, world"); //写进缓存
fflush(fp); //调用fflush、fclose、、fseek、fseeko、fsetpos会在当前位置添加null
```
利用`fflush`函数引起缓冲区冲洗，并在当前位置设置`null`，此时的`buf`为：
> * hello, world + `null` + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaaaa + aaa0X
> * 此时的打印结果为： "hello, world"
> * 此时的偏移值指向`null`，即offset = 12

然后继续执行：
```
memset(buf, 'b', BSZ-2);
buf[BSZ-2] = '\0';
buf[BSZ-1] = 'X';
```
用`b`字符改写缓冲区，此时的`buf`为：
> * bbbbb + bbbbb + bbbbb + bbbbb + bbbbb + bbbbb + bbbbb + bbbbb + bbbbb + b0X
> * 此时的偏移值仍旧指向原来的位置，即为offset = 12

然后继续想缓冲中写入数据：
```
fprintf(fp, "hello, world"); //继续写进
fseek(fp, 0, SEEK_CUR); //保持偏移值在冲洗之后位置
```
利用`fseek`函数引起缓冲区冲洗，并在当前位置设置`null`，此时`buf`为：
> * bbbbb + bbbbb + bb + hello, world + `null` + bbbbb + bbbbb + bbbbb + bbbbb + b0X
> * 打印结果为： bbbbbbbbbbbbhello, world
> * 偏移值位于`null`，即offset = 24

然后经过继续写入之后：
```
memset(buf, 'c', BSZ-2);
buf[BSZ-2] = '\0';
buf[BSZ-1] = 'X';
fprintf(fp, "hello, world"); //继续写进去
fseek(fp, 0, SEEK_SET); //偏移值设为缓冲区开始位置
```
利用`fseek`函数引起缓冲区冲洗，并在当前位置设置`null`，此时的`buf`为：
> * cccccccccccc + cccccccccccc + hello, world + `null` + ccccc + cccc0X
> * 打印结果为：cccccccccccccccccccccccchello, world
> * 此时由于`fseek`函数，偏移值设为了缓冲区的开始位置，即offset = 0

最后执行写入，注意此时的偏移值位于缓冲区开始：
```
memset(buf, 'd', BSZ-2);
buf[BSZ-2] = '\0';
buf[BSZ-1] = 'X';
fprintf(fp, "hello, world"); //继续写进去
fclose(fp); //然后fclose在当前位置也就是数据尾端添加一个null
```
直接使用`fclose`函数关闭流，没有追加`null`，此时的`buf`为：
> * hello, world + null + ddddd + ddddd + ddddd + ddddd + ddddd + ddddd + ddd0X
> * 打印结果为 hello, worlddddddddddddddddddddddddddddddddddd

**但是前面不是说了一旦调用`fclose`等函数，就会自动在当前位置写一个`null`字节嘛， 为什么这里没有追加呢？请看下面三个测试方案**

## `null`追加策略分析

### 测试代码
```
#include "apue.h"

#define BSZ 48

int main()
{
	FILE *fp1, *fp2, *fp3;
	char buf1[BSZ], buf2[BSZ], buf3[BSZ];

	//方案一
	memset(buf1, 'a', BSZ-2);
	buf1[BSZ-2] = '\0';
	buf1[BSZ-1] = 'X';
	if ((fp1 = fmemopen(buf1, BSZ, "w+")) == NULL)
		err_sys("fmemopen failed");
	fprintf(fp1, "hello, world");
	//调用fflush函数引起缓冲区冲洗
	fflush(fp1);
	printf("1.After fflush: %s\n", buf1);
	printf("1.Len of string in buf = %ld\n", (long)strlen(buf1));
	memset(buf1, 'b', BSZ-2);
	buf1[BSZ-2] = '\0';
	buf1[BSZ-1] = 'X';
	//二次输入数据为"nihao"，长度较短
	fprintf(fp1, "nihao");
	fclose(fp1);
	printf("1.After close: %s\n", buf1);
	printf("1.Len of string in buf = %ld\n\n", (long)strlen(buf1));

	//方案二
	memset(buf2, 'a', BSZ-2);
	buf2[BSZ-2] = '\0';
	buf2[BSZ-1] = 'X';
	if ((fp2 = fmemopen(buf2, BSZ, "w+")) == NULL)
		err_sys("fmemopen failed");
	fprintf(fp2, "hello, world");
	//调用fseek函数引起缓冲区冲洗，偏移值设为首部
	fseek(fp2, 0, SEEK_SET);
	printf("2.After fseek: %s\n", buf2);
	printf("2.Len of string in buf = %ld\n", (long)strlen(buf2));
	memset(buf2, 'b', BSZ-2);
	buf2[BSZ-2] = '\0';
	buf2[BSZ-1] = 'X';
	//二次输入数据为"nihao"，长度较短
	fprintf(fp2, "nihao");
	fclose(fp2);
	printf("2.After close: %s\n", buf2);
	printf("2.Len of string in buf = %ld\n\n", (long)strlen(buf2));

	//方案三
	memset(buf3, 'a', BSZ-2);
	buf3[BSZ-2] = '\0';
	buf3[BSZ-1] = 'X';
	if ((fp3 = fmemopen(buf3, BSZ, "w+")) == NULL)
		err_sys("fmemopen failed");
	fprintf(fp3, "hello, world");
	//调用fseek函数引起缓冲区冲洗，偏移值设为首部
	fseek(fp3, 0, SEEK_SET);
	printf("3.After fseek: %s\n", buf3);
	printf("3.Len of string in buf = %ld\n", (long)strlen(buf3));
	memset(buf2, 'b', BSZ-2);
	buf2[BSZ-2] = '\0';
	buf2[BSZ-1] = 'X';
	//二次输入数据为"hello, world! How are you?"，长度较长
	fprintf(fp3, "hello, world! How are you?");
	fclose(fp3);
	printf("3.After close: %s\n", buf3);
	printf("3.Len of string in buf = %ld\n\n", (long)strlen(buf3));

	return(0);
}
```
最后的输出结果为：
```
1.After fflush: hello, world
1.Len of string in buf = 12
1.After close: bbbbbbbbbbbbnihao
1.Len of string in buf = 17

2.After fseek: hello, world
2.Len of string in buf = 12
2.After close: nihaobbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
2.Len of string in buf = 46

3.After fseek: hello, world
3.Len of string in buf = 12
3.After close: hello, world! How are you?
3.Len of string in buf = 26
```

### 结果分析
> * 方案一：`fclose`函数冲洗内存流导致需要增加流缓冲区中数据量，在当前偏移值后面继续写入数据，由12增加到17，并且调用了`fclose`函数，所以追加`null`；
> * 方案二：`fclose`函数冲洗内存流时，偏移值在流缓冲区首部，此时"nihao"的长度小于原本流缓冲区中"hello, world"的长度，只会覆盖流缓冲区的前一部分，流缓冲区数据量并没有增加，仍未12，所以不追加`null`；
> * 方案三：同方案二，只是再次输入的数据"hello, world! How are you?"大于原本流缓冲区中的"hello, world"的长度，所以需要增加流缓冲区中数据量，调用了`fclose`函数，所以追加’null`；

### 总结
由上述测试可以发现，追加`null`的策略机制是必须同时满足以下两个条件：
> * 需要增加流缓冲区中的数据量
> * 调用fclose、fflush、fseek、fseeko以及fsetpos时

书上的图5-15就是因为输入数据太短没有增加流缓冲区所以才没有追加`null`的，看到这里应该可以明白了吧。这一部分书上也没有讲得很清楚，我看到这里困惑了好久，终于通过自己的测试一点一点搞明白了。
文章粗浅，有什么疏漏之处欢迎各位批评指正！
