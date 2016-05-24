layout: '[post]'
title: EightQueen
date: 2016-05-24 13:54:57
categories: Algorithm
tags: [数据结构, Algorithm, Eightqueen]
---

八皇后问题是一个以国际象棋为背景的问题：如何能够在`8×8`的国际象棋棋盘上放置八个皇后，使得任何一个皇后都无法直接吃掉其他的皇后。为了达到此目的，任两个皇后都不能处于同一条横行、纵行或斜线上。八皇后问题可以推广为更一般的n皇后摆放问题：这时棋盘的大小变为`n×n`，而皇后个数也变成`n`。当且仅当`n = 1`或`n ≥ 4`时问题有解。

### 解题思路

> * 首先观察可以发现，每一行或者每一列都有且只有一个皇后；
> * 使用一个数组`x[8]`存储每一行皇后位置所对应的列数。例如：`a[2] = 5`就表示第二行的皇后位于第五列；
> * 皇后不在一条直线上可以表示为条件`x[i] != x[j]`；
> * 皇后不在一条斜线上可以表示为条件`abs(x[i] - x[j]) != abs(i - j)`；

<!--more-->

### 代码

思路如上分析，代码如下：
```c++
#include <iostream>
using namespace std;

int sum = 0;
int x[8] = {0};

bool place(int k)
{
    for(int i = 0; i < k; ++i)
        if(abs(x[k] - x[i]) == abs(k - i) || x[k] == x[i])
            return false;
    return true;
}

void put_queen(int n)
{
    if( n >= 8)
    {
        sum++;
        cout << "This is the " << sum << "th time!" << endl;
        for(int i = 0; i < 8; ++i)
        {
            for(int j = 0; j < 8; ++j)
            {
                if(j == x[i])
                    cout << "* "; //"*" 表示皇后
                else
                    cout << "^ "; //"^" 表示空位
            }
            cout << endl;
        }

        //通过键盘控制每五个一组进行打印
        if(sum % 5 == 0)
        {
            getchar();
        }
    }
    else
    {
        for(int i = 0; i < 8; ++i)
        {
            x[n] = i;
            if(place(n))
                put_queen(n + 1);
        }
    }
}

int main()
{
    put_queen(0);
    return 0;
}
```
