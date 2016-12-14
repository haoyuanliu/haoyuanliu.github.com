---
title: LeetCode Sqrt and Square
date: 2016-12-14 17:53:37
categories: LeetCode
tags: [LeetCode]
---

本文包含如下题目：
[50. Pow(x, n)][1]
[69. Sqrt(x)][2]
[367. Valid Perfect Square][3]
[372. Super Pow][4]

<!--more-->

## 50. Pow(x, n)
### 阶梯思路
> * 就直接算就好，考虑指数小于零就好；

### 代码
```
class Solution
{
    public:
        double myPow(double x, int n)
        {
            double res = 1;
            long long newn = n;
            if(newn < 0)
            {
                newn = -newn;
                x = 1.0 / x;
            }
            while(newn > 0)
            {
                if(newn&1)
                    res = res * x;
                x = x * x;
                newn = newn>>1;
            }
            return res;
        }
};
```
## 69. Sqrt(x)
### 解题思路
> * 二分查找去找就可以了，注意使用long long类型，防止溢出；

### 代码
```
class Solution
{
    public:
        int mySqrt(int x)
        {
            if(x == 0)
                return 0;
            else if(x < 0)
                return (1<<31);
            int res;
            long long left, right, mid;
            left = 1;
            right = x>>1;
            while(left < right)
            {
                if(left * left == x)
                    return (int)left;
                if(right * right == x)
                    return (int)right;
                mid = (left + right) / 2;
                if(mid * mid == x)
                    return (int)mid;
                else if(mid * mid < x)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return (left * left > x) ? (left - 1) : left;
        }
};
```
## 367. Valid Perfect Square
### 解题思路
> * 二分法去找根，找到就为true，否则返回false；
> * 如果是1，则直接判定为true；

### 代码
```
class Solution
{
    public:
        bool isPerfectSquare(int num)
        {
            if(num == 1)
                return true;
            long long left, right, mid;
            left = 1;
            right = num>>1;
            while(left < right)
            {
                if(left * left == num)
                    return true;
                if(right * right == num)
                    return true;
                mid = (left + right) / 2;
                if(mid * mid == num)
                    return true;
                else if(mid * mid < num)
                    left = mid+1;
                else
                    right = mid - 1;
            }
            return false;
        }
};
```

## 372. Super Pow
### 解题思路
> * 使用二进制进行快速求幂；
> * a的52次幂，就等于((a^2)%mode * ((a^10)^5)%mode)%mode;
> * 使用上述公式利用快速求幂不断求取((a^10)^10)...即可进行求解；

### 代码
```
class Solution
{
    private:
        int mode = 1337;
    public:
        int superPow(int a, vector<int> &b)
        {
            int res = 1;
            if(a == 0)
                return 0;
            for(int i = b.size()-1; i >= 0; --i)
            {
                res = res * quickPow(a, b[i]) % mode;
                a = quickPow(a, 10);
            }
            return res;
        }
        inline int quickPow(int a, int n)
        {
            int res = 1;
            a %= mode;
            while(n)
            {
                if(n & 1)
                    res = res * a % mode;
                a = a * a % mode;
                n >>= 1;
            }
            return res;
        }
};
```

  [1]: https://leetcode.com/problems/powx-n/
  [2]: https://leetcode.com/problems/sqrtx/
  [3]: https://leetcode.com/problems/valid-perfect-square/
  [4]: https://leetcode.com/problems/super-pow/