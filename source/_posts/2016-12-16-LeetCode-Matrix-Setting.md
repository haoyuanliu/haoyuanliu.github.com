---
title: LeetCode Matrix Setting
categories: LeetCode
tags:
  - LeetCode
  - Array
abbrlink: 46777
date: 2016-12-16 14:51:39
---

本文包含如下题目：
[73. Set Matrix Zeroes][1]
[289. Game of Life][2]

<!--more-->

## 73. Set Matrix Zeroes
### 解题思路I
> * 直接使用一个m长和n长的数组存储矩阵中0的位置；
> * 空间复杂度（m+n）；



### 代码
```
class Solution
{
    public:
        void setZeroes(vector<vector<int> > &matrix)
        {
            int m = matrix.size();
            int n = matrix[0].size();
            vector<int> row(m, 1);
            vector<int> col(n, 1);
            for(int i = 0; i < m; ++i)
            {
                for(int j = 0; j < n; ++j)
                {
                    if(matrix[i][j] == 0)
                    {
                        row[i] = 0;
                        col[j] = 0;
                    }
                }
            }
            for(int i = 0; i < m; ++i)
            {
                for(int j = 0; j < n; ++j)
                {
                    if(row[i] && col[j])
                        continue;
                    matrix[i][j] = 0;
                }
            }
        }
};
```

### 解题思路II
> * 将矩阵中０所在的位置信息保存在首行和首列中；
> * 空间复杂度为０；

### 代码
```
class Solution
{
    public:
        void setZeroes(vector<vector<int> > &matrix)
        {
            int m = matrix.size();
            int n = matrix[0].size();
            bool flag = false;

            for(int i = 0; i < m; ++i)
            {
                if(matrix[i][0] == 0)
                    flag = true;
                for(int j = 1; j < n; ++j)
                {
                    if(matrix[i][j] == 0)
                        matrix[i][0] = matrix[0][j] = 0;
                }
            }
            for(int i = m-1; i >= 0; --i)
            {
                for(int j = n-1; j > 0; --j)
                {
                    if(!matrix[i][0] || !matrix[0][j])
                        matrix[i][j] = 0;
                }
                if(flag)
                    matrix[i][0] = 0;
            }
        }
};
```

## 289. Game of Life

### 解题思路
> * [2nd bit, 1st bit] = [next state, current state]
- 00  dead (current) -> dead(next)
- 01  live (current) -> dead(next)
- 10  dead (current) -> live(next)
- 11  live (current) -> live(next)
> * discuss里面的思路，使用２bit的数据存储下一步和现在的状态，最后移位即可；


### 代码
```
class Solution
{
    public:
        void gameOfLife(vector<vector<int> > &board)
        {
            int m = board.size();
            int n = m ? board[0].size() : 0;
            int count;
            for(int i = 0; i < m; ++i)
            {
                for(int j = 0; j < n; ++j)
                {
                    count = board[i][j] ? -1 : 0;
                    for(int x = max(0, i-1); x < min(i+2, m); ++x)
                    {
                        for(int y = max(0, j-1); y < min(j+2, n); ++y)
                        {
                            if(board[x][y]&1)
                                count++;
                        }
                    }
                    if(count == 2)
                        board[i][j] += board[i][j]<<1;
                    else if(count == 3)
                        board[i][j] += 2;
                }
            }
            for(int i = 0; i < m ; ++i)
                for(int j = 0; j < n; ++j)
                    board[i][j] >>= 1;
        }
};
```


  [1]: https://leetcode.com/problems/set-matrix-zeroes/
  [2]: https://leetcode.com/problems/game-of-life/