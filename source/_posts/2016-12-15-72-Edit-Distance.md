---
title: 72.Edit Distance
categories: LeetCode
tags:
  - LeetCode
  - DP
abbrlink: 658
date: 2016-12-15 20:33:19
---


[题目链接！][1]

### 解题思路
> * 使用DP动态规划，dp[i][j]表示word1中的前i个字符与word2中的前j个字符的距离；
> * dp[i][j]的可能取值如下：
> * word1插入一个字符：dp[i][j-1] + 1;
> * word1删掉一个字符：dp[i-1][j] + 1;
> * 两字符串最后一位不相同，则替换word1的最后一个：dp[i-1][j-1] + 1;
> * 如果相同，则不需要操作：dp[i][j];
> * DP取上述情形的最小值。

<!--more-->

### 代码
```
class Solution
{
    public:
        int minDistance(string word1, string word2)
        {
            int m = word1.size();
            int n = word2.size();
            vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
            for(int i = 1; i <= m; ++i)
                dp[i][0] = i;
            for(int j = 1; j <= n; ++j)
                dp[0][j] = j;
            for(int i = 1; i <= m; ++i)
            {
                for(int j = 1; j <= n; ++j)
                {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
                    if(word1[i-1] == word2[j-1])
                        dp[i][j] = min(dp[i-1][j-1], dp[i][j]);
                    else
                        dp[i][j] = min(dp[i-1][j-1]+1, dp[i][j]);
                }
            }
            return dp[m][n];
        }
};
```

  [1]: https://leetcode.com/problems/edit-distance/