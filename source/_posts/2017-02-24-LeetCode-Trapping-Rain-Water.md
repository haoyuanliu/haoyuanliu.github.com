---
title: LeetCode Trapping Rain Water
date: 2017-02-24 16:47:46
categories: LeetCode
tags: [LeetCode, Algorithm]
---

本文包含如下两个题目：
[42. Trapping Rain Water][1]
[407. Trapping Rain Water II][2]

<!--more-->

## 42. Trapping Rain Water
### 解题思路
从两头开始向中间搜索，维持一个secondHeight的变量，记录已遍历的节点中第二高的点。遍历到的节点高度小于secondHeight的话，可以装水，如果大于secondHeight的话，则此时需要更新secondHeight。

### 代码
```
class Solution
{
    public:
        int trap(vector<int> &height)
        {
            int res = 0;
            int len = height.size();
            int l = 0;
            int r = len-1;
            int secondHeight = 0;
            while(l < r)
            {
                if(height[l] < height[r])
                {
                    if(secondHeight < height[l])
                        secondHeight = height[l];
                    else
                        res += secondHeight - height[l];
                    l++;
                }
                else
                {
                    if(secondHeight < height[r])
                        secondHeight = height[r];
                    else
                        res += secondHeight - height[r];
                    r--;
                }
            }
            return res;
        }
};
```

## 407. Trapping Rain Water II
### 解题思路
首先将边缘的高度全部统计，使用堆排序进行排序，建立最初的水池边框。然后取边框中高度最低的作为参照，取其上下左右四个相邻块的高度，如果高度小于参照高度，则可以储水，如果大于等于参照高度，则无法储水，就应该划归到边框中，置入堆中进行排序，然后循环如上操作。

### 代码
```
class Solution
{
public:
    int trapRainWater(vector<vector<int>>& heightMap)
    {
        int res = 0;
        if(heightMap.size() <= 2)
            return res;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
        int row = heightMap.size();
        int col = heightMap[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));

        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j)
            {
                if(!(i==0 || i==row-1 || j==0 || j==col-1))
                    continue;
                que.push(make_pair(heightMap[i][j], i*col+j));
                visited[i][j] = 1;
            }
        }

        vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int minHeight = 1<<31;

        while(!que.empty())
        {
            int height = que.top().first;
            int x = que.top().second / col;
            int y = que.top().second % col;
            que.pop();
            minHeight = max(minHeight, height);

            for(const auto d : dir)
            {
                int x2 = x + d[0];
                int y2 = y + d[1];
                if(x2 < 0 || x2 >= row || y2 < 0 || y2 >= col || visited[x2][y2])
                    continue;
                if(heightMap[x2][y2] < minHeight)
                    res += minHeight - heightMap[x2][y2];
                que.push(make_pair(heightMap[x2][y2], x2 * col + y2));
                visited[x2][y2] =  1;
            }
        }
        return res;
    }
};
```


  [1]: https://leetcode.com/problems/trapping-rain-water/
  [2]: https://leetcode.com/problems/trapping-rain-water-ii/