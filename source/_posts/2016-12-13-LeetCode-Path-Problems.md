---
title: LeetCode Path Problems
date: 2016-12-13 11:28:50
categories: LeetCode
tags: [LeetCode]
---

本文包含如下题目：
[62. Unique Paths][1]
[63. Unique Paths II][2]
[64. Minimum Path Sum][3]
[174. Dungeon Game][4]

<!--more-->

## 62. Unique Paths

### 解题思路

> * 设m×n的表格有res[m][n]条路径；
> * 所有的res[m][26] = res[1][n] = 1;
> * 针对任意i×j有res[i][j] = res[i-1][j] + res[i][j-1];
> * 由状态公式可知，可以进行空间优化，使用两行数组即可DP完成。

如上，用DP就可以很快做出来。
### 代码
```
class Solution
{
    public:
        int uniquePaths(int m, int n)
        {
            int res[101][101] = {0};
            for(int i = 1; i <= m; ++i)
                res[i][27] = 1;
            for(int j = 1; j <= n; ++j)
                res[1][j] = 1;
            for(int i = 2; i <= m; ++i)
            {
                for(int j = 2; j <= n; ++j)
                {
                    res[i][j] = res[i-1][j] + res[i][j-1];
                }
            }
            return res[m][n];
        }
};
```
进行空间优化之后的代码为：
```
class Solution
{
    public:
        int uniquePaths(int m, int n)
        {
            int res[2][101] = {0};
            for(int i = 1; i <= n; ++i)
                res[0][i] = res[1][i] = 1;
            for(int i = 2; i <= m; ++i)
            {
                for(int j = 1; j <= n; ++j)
                {
                        res[1][j] = res[0][j] + res[1][j-1];
                }
                for(int k = 0; k <= n; ++k)
                    res[0][k] = res[1][k];
            }
            return res[0][n];
        }
};
```

## 63. Unique Paths II

### 解题思路

> * 设m×n的表格有res[m][n]条路径；
> * 所有的res[m][28] = res[1][n] = 1;
> * 如果(x, j)位置为1，则此时res[i][j] = 0;
> * 此外，任意i×j有res[i][j] = res[i-1][j] + res[i][j-1];
> * 根据上述公式，进行空间优化，使用两行数组进行DP即可。

### 代码
```
class Solution
{
    public:
        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)
        {
            int m = obstacleGrid.size();
            int n = obstacleGrid[0].size();
            if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1)
                return 0;
            int res[2][101] = {0};
            for(int i = 1; i <= n; ++i)
            {
                if(obstacleGrid[0][i-1])
                    break;
                res[0][i] = res[1][i] = 1;
            }

            for(int i = 2; i <= m; ++i)
            {
                for(int j = 1; j <= n; ++j)
                {
                    if(obstacleGrid[i-1][j-1] == 0)
                        res[1][j] = res[0][j] + res[1][j-1];
                    else
                        res[1][j] = 0;
                }
                for(int k = 0; k <= n; ++k)
                    res[0][k] = res[1][k];
            }
            return res[0][n];
        }
};
```

## 64. Minimum Path Sum
### 解题思路
> * grid[i][j]表示到(i, j)位置的最小距离；
> * grid[i][j] = min(grid[i][j-1] + grid[i][j], grid[i-1][j] + grid[i][j])；

### 代码
```
class Solution
{
    public:
        int minPathSum(vector<vector<int> > &grid)
        {
            int m = grid.size();
            int n = grid[0].size();
            for(int i = 1; i < m; ++i)
                grid[i][0] = grid[i-1][0] + grid[i][0];
            for(int j = 1; j < n; ++j)
                grid[0][j] = grid[0][j-1] + grid[0][j];
            for(int i = 1; i < m; ++i)
            {
                for(int j = 1; j < n; ++j)
                {
                    grid[i][j] = min(grid[i][j-1] + grid[i][j], grid[i-1][j] + grid[i][j]);
                }
            }
            return grid[m-1][n-1];
        }
};
```

## 174. Dungeon Game
### 解题思路
> * 设dp[i][j]表示到达(i, j)时的最小生命值；
> * dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dp[i][j])；
> * 减去dp[i][j]，如果为正，表示最小生命值可以少一点，但最小为1，为负，表示需要更多的生命值；
> * 从右下角开始进行计算，右下角的最小生命值为1，然后从右下到左上进行计算；
> * 如果从左上开始向右下计算，遇到一个很大的正数的时候就很难处理，会覆盖之前的信息；
> * DP的问题，如果正序计算不好解决，试一试逆序DP。

### 代码
```
class Solution
{
    public:
        int calculateMinimumHP(vector<vector<int> > &dumgeon)
        {
            int m = dumgeon.size();
            int n = dumgeon[0].size();
            dumgeon[m-1][n-1] = max(1, 1 - dumgeon[m-1][n-1]);
            for(int j = n-2; j >= 0; --j)
                dumgeon[m-1][j] = max(1, dumgeon[m-1][j+1] - dumgeon[m-1][j]);
            for(int i = m-2; i >= 0; --i)
                dumgeon[i][n-1] = max(1, dumgeon[i+1][n-1] - dumgeon[i][n-1]);
            for(int i = m-2; i >= 0; --i)
                for(int j = n-2; j >= 0; --j)
                    dumgeon[i][j] = max(1, min(dumgeon[i+1][j], dumgeon[i][j+1]) - dumgeon[i][j]);
            return dumgeon[0][0];
        }
};
```

  [1]: https://leetcode.com/problems/unique-paths/
  [2]: https://leetcode.com/problems/unique-paths-iie.com/problems/unique-paths/
  [3]: https://leetcode.com/problems/minimum-path-sume.com/problems/unique-paths/
  [4]: https://leetcode.com/problems/dungeon-game/