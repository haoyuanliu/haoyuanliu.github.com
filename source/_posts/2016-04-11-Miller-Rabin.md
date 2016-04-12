layout: '[post]'
title: Miller-Rabin质数测试
date: 2016-04-11 17:22:22
tags: [Miller-Rabin, 素数]
categories: Algorithm
---

本文主要讨论使用Miller-Rabin算法编写素数的判定算法，题目来源于[hihocoder][1]。

# 题目

## 题目要求
时间限制:10000ms
单点时限:1000ms
内存限制:256MB

## 描述
使用Miller-Rabin算法进行质数素数测试，要求输入一个数字，对其是否是素数进行判定，并打印出相对应的结果。

> 提示：[Miller-Rabin质数测试][2]

## 输入

第1行：1个正整数t，表示数字的个数，`10≤t≤50`
第2..t+1行：每行1个正整数，第`i+1`行表示正整数`a[i]`，`2≤a[i]≤10^18`

## 输出

第1..t行：每行1个字符串，若a[i]为质数，第i行输出"Yes"，否则输出"No"

## 样例输入
```
3
3
7
9
``
`
## 样例输出
```
Yes
Yes
No
```

<!--more-->
# 题目分析

## 费马小定理

>费马小定理：对于质数`p`和任意整数`a`，有`a^p ≡ a(mod p)(同余)`。反之，若满足`a^p ≡ a(mod p)`，`p`也有很大概率为质数。
将两边同时约去一个`a`，则有`a^(p-1) ≡ 1(mod p)`

也即是说：假设我们要测试`n`是否为质数。我们可以随机选取一个数`a`，然后计算`a^(n-1) mod n`，如果结果不为`1`，我们可以100%断定`n`不是质数。
否则我们再随机选取一个新的数a进行测试。如此反复多次，如果每次结果都是1，我们就假定n是质数。
该测试被称为Fermat测试。需要注意的是：Fermat测试不一定是准确的，有可能出现把合数误判为质数的情况。
Miller和Rabin在Fermat测试上，建立了Miller-Rabin质数测试算法。

## 二次探测定理

>如果`p`是奇素数，则 `x^2 ≡ 1(mod p)`的解为 `x ≡ 1` 或 `x ≡ p - 1(mod p)`
如果`a^(n-1) ≡ 1 (mod n)`成立，Miller-Rabin算法不是立即找另一个`a`进行测试，而是看`n-1`是不是偶数。如果`n-1`是偶数，另`u=(n-1)/2`，并检查是否满足二次探测定理即`a^u ≡ 1 `或 `a^u ≡ n - 1(mod n)`。

举个[Matrix67 Blog][3]上的例子，假设`n=341`，我们选取的`a=2`。则第一次测试时，`2^340 mod 341=1`。由于`340`是偶数，因此我们检查`2^170`，得到`2^170 mod 341=1`，满足二次探测定理。同时由于`170`还是偶数，因此我们进一步检查`2^85 mod 341=32`。此时不满足二次探测定理，因此可以判定`341`不为质数。

将这两条定理合起来，也就是最常见的Miller-Rabin测试。

## 加强版测试验证定理

> 尽可能提取因子`2`，把`n-1`表示成`d*2^r`,如果`n`是一个素数，那么或者`a^d mod n==1`，或者存在某个`i`使得`a^(d*2^i) mod n=n-1 (0<=i<r)`则我们认为n为素数。（注意`i`可以等于`0`，这就把`a^d mod n=n-1`的情况统一到后面去了）

这里需要注意的是，我们将该定理作为判定条件，仍然是一个不确定的概率判定条件。Miller-Rabin素性测试同样是不确定算法，我们把可以通过以`a`为底的Miller-Rabin测试的合数称作以a为底的强伪素数(strong pseudoprime)。第一个以2为底的强伪素数为2047。第一个以2和3为底的强伪素数则大到1 373 653。

所以我们在实际使用过程中，使用`rand()`函数生成随机数，或者进行多次检测判定，还是能够得到比较高的判定成功率，Miller-Rabin算法对于素数的研究判定有着巨大的辅助作用。

# 代码

## 整体代码

```C++
#include <iostream>
#include <cstdlib>
using namespace std;
typedef long long llong;
//求取(x * y) % n
llong mod(llong x, llong y,llong n)
{
    llong res = 0;
    llong temp = x % n;
    while(y)
    {
        if(y & 0x1)
            if((res += temp) > n)
                res -= n;
        if((temp <<= 1) >  n)
            temp -= n;
        y >>= 1;
    }
    return res;
}

//求取(x ^ y) % n
llong get_mod(llong x, llong y, llong n)
{
    llong res = 1;
    llong temp = x;
    while(y)
    {
        if(y & 0x1)
            res = mod(res, temp, n);
        temp = mod(temp, temp, n);
        y >>= 1;
    }
    return res;
}

//编写bool函数，判定是否为素数
bool is_prime(llong n, int t)
{
    if(n < 2)
        return false;
    if(n == 2)
        return true;
    if(!(n & 0x1))
        return false;
    llong k = 0, m, a, i;
    for(m = n -1; !(m & 0x1); m >>= 1, ++k);
    while(t--)
    {
        a = get_mod(rand() % (n - 2) + 2, m, n);
        if(a != 1)
        {
            for(i = 0; i < k && a != n-1; ++i)
            {
                cout << a << endl;
                a = mod(a, a, n);
            }
            //根据二次探测定理，只要不满足(a == 1) || (a == n - 1)，就会一直遍历下去，直到最后返回false
            if(i >= k)
                return false;
        }
    }
    return true;
}

//主函数
int main()
{
    int times;
    llong num;
    cin >> times;
    while(times--)
    {
        cin >> num;
        if(is_prime(num, 1))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
```

## 代码分解

### mod()函数

```C++
//求取(x * y) % n
llong mod(llong x, llong y,llong n)
{
    llong res = 0;
    llong temp = x % n;
    while(y)
    {
        if(y & 0x1)
            if((res += temp) > n)
                res -= n;
        if((temp <<= 1) >  n)
            temp -= n;
        y >>= 1;
    }
    return res;
}
```
这个函数使用移位运算，通过将y转换成二进制形式，十分高效地求取了两个数字乘积的余数。

### get_mod()函数

```C++
//求取(x ^ y) % n
llong get_mod(llong x, llong y, llong n)
{
    llong res = 1;
    llong temp = x;
    while(y)
    {
        if(y & 0x1)
            res = mod(res, temp, n);
        temp = mod(temp, temp, n);
        y >>= 1;
    }
    return res;
}
```
这个函数是经典的高次幂函数求余算法，即[蒙哥马利算法][4]，在上一篇博文中也有过介绍，[博文链接][5]。
其核心思想就是将幂指数转换成二进制，通过移位运算快速地求取余数，避免了数据溢出，而且效率非常高。

### is_prime()函数
```C++
//编写bool函数，判定是否为素数
bool is_prime(llong n, int t)
{
    if(n < 2)
        return false;
    if(n == 2)
        return true;
    if(!(n & 0x1))
        return false;
    llong k = 0, m, a, i;
    for(m = n -1; !(m & 0x1); m >>= 1, ++k);
    while(t--)
    {
        a = get_mod(rand() % (n - 2) + 2, m, n);
        if(a != 1)
        {
            for(i = 0; i < k && a != n-1; ++i)
            {
                cout << a << endl;
                a = mod(a, a, n);
            }
            //根据二次探测定理，只要不满足(a == 1) || (a == n - 1)，就会一直遍历下去，直到最后返回false
            if(i >= k)
                return false;
        }
    }
    return true;
}
```
即数字是否是素数的判定函数，依照我们在上文提出的加强定理，包含如下要点：

> * 对所需判定的奇数`n`进行`n-1`提取因子`2`，把`n-1`表示成`d*2^r`的形式；
> * 取随机数`a=rand()`，如果`a^d mod n == 1`则判定为素数；
> * 如果`a^d mod n ！= 1`，则通过循环查找是否有`i`满足`a^(d*2^i) mod n = n-1`，若有，则判定为素数；
> * 如果上述条件都不成立，则遍历结果得到`i == k`，此时返回`false`

---

> * **Tips：这里需要注意的是，Miller-Rabin算法是一个不确定算法，仍有一定的错误概率，正如上文所述的，第一个以2为底的强伪素数为2047。第一个以2和3为底的强伪素数则大到1 373 653。在一定的使用范围内仍然可以得到高效、准确的结果！**



  [1]: http://hihocoder.com/contest/hiho92/problem/1
  [2]: http://www.matrix67.com/blog/archives/234
  [3]: http://www.matrix67.com/blog/archives/234
  [4]: https://en.wikipedia.org/wiki/Peter_Montgomery_%28mathematician%29
  [5]: http://haoyuanliu.github.io/2016/04/04/get-mod/
