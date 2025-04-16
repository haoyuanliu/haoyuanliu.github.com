---
title: LeetCode Search 2D Matrix
categories:
  - LeetCode
tags:
  - LeetCode
  - Binary Search
  - Divide and Conquer
abbrlink: 1416
date: 2016-12-16 15:49:24
---

本文包含如下题目：
[74. Search a 2D Matrix][1]
[240. Search a 2D Matrix II][2]

<!--more-->

## 74. Search a 2D Matrix
### 解题思路
> * 先找到target所在的行，然后对所在行进行二分查找，结果超时；
> * 将矩阵看做一个一维数组，然后整体使用二分查找；

### 代码
```
class Solution
{
    public:
        bool searchMatrix(vector<vector<int> > &matrix, int target)
        {
            if(matrix[0][0] == target)
                return true;
            int m = matrix.size();
            int n = m ? matrix[0].size() : 0;
            int total = n * m;
            int left = 0;
            int right = n * m - 1;
            int mid = 0;
            while(left < right)
            {
                if(matrix[left/n][left%n] == target)
                    return true;
                if(matrix[right/n][right%n] == target)
                    return true;
                mid = (left + right) / 2;
                if(matrix[mid/n][mid%n] == target)
                    return true;
                else if(matrix[mid/n][mid%n] < target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return false;
        }
};
```

## 240. Search a 2D Matrix II
### 解题思路
> * 从右上角开始查找；
> * 如果小于target，则这一行全部小于target；
> * 如果大于target，则这一列全部大于target；
> * 按照这个策略进行搜索即可；

### 代码
```
class Solution
{
    public:
        bool searchMatrix(vector<vector<int> > &matrix, int target)
        {
            int m = matrix.size();
            int n = m ? matrix[0].size() : 0;
            int x = 0;
            int y = n - 1;
            while(x < m && y >= 0)
            {
                if(matrix[x][y] == target)
                    return true;
                else if(matrix[x][y] < target)
                    x++;
                else
                    y--;
            }
            return false;
        }
};
```

  [1]: https://leetcode.com/problems/search-a-2d-matrix/ms/search-a-2d-matrix/
  [2]: https://leetcode.com/problems/search-a-2d-matrix-ii/