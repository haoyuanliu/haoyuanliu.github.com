---
title: 70 Climbing Stairs
date: 2016-12-14 18:56:26
categories: LeetCode
tags: [LeetCode, DP]
---


题目链接：[70. Climbing Stairs][1]

### 解题思路
> * dp[i]表示从ｉ位置到达末尾的方法个数；
> * 只剩最后一步就只有一种选择，两步则有两个选择；
> * dp[m] = dp[m+1] + dp[m+2];

<!--more-->

### 代码
```
class Solution
{
    public:
        int climbStairs(int n)
        {
            if(n <= 0)
                return 0;
            else if(n == 1)
                return 1;
            else if(n == 2)
                return 2;
                
            int dp[n];
            dp[n-1] = 1;
            dp[n-2] = 2;
            for(int i = n-3; i >= 0; --i)
            {
                dp[i] = dp[i+1] + dp[i+2];
            }
            return dp[0];
        }
};
```


  [1]: https://leetcode.com/problems/climbing-stairs/