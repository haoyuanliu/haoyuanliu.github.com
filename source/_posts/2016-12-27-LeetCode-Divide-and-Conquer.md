---
title: LeetCode Divide and Conquer
date: 2016-12-27 21:06:45
categories: LeetCode
tags: [LeetCode, Divide and Conquer]
---

本文包含如下题目：

[218. The Skyline Problem][1]
[241. Different Ways to Add Parentheses][2]
[282. Expression Add Operators][3]
[312. Burst Balloons][4]
[315. Count of Smaller Numbers After Self][5]
[327. Count of Range Sum][6]

<!--more-->

## 218. The Skyline Problem
### 解题思路
> * 强烈推荐看这个分析，[文章链接][7]！！！！！！！
> * 只有矩阵的左右边界会对最后的结果产生影响，使用vector保存全部边界并进行排序；
> * 使用priority_queue的heap结构维持一个存储高度的堆，如果是左边界，则其高度数据push进去，如果是右边界，则将该高度标记为废弃，在后面访问到的时候删除；
> * 如果改边界获取的最大高度值与之前一样，则不操作，否则，将边界值和高度信息push进答案中去；
> * 这里使用了priority_queue的堆结构特性，可以很快的访问到最大值；
> * 使用unordered_map比map要快很多，因为它不排序；

### 代码
```
bool cmp(const pair<int, int> a, const pair<int, int> b)
{
    return a.first != b.first ? a.first < b.first : a.second < b.second;
}

class Solution 
{
    public:
        vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) 
        {
            vector<pair<int, int>> res;
            vector<pair<int, int>> heights;
            for(const auto build : buildings)
            {
                heights.push_back(make_pair(build[0], -build[2]));
                heights.push_back(make_pair(build[1], build[2]));
            }
            sort(heights.begin(), heights.end(), cmp);
            unordered_map<int, int> isEnd;
            priority_queue<int> que;
            int pre = 0;
            que.push(0);
            int cur;
            for(const auto height : heights)
            {
                if(height.second < 0)
                {
                    que.push(-height.second);
                }
                else
                {
                    ++isEnd[height.second];
                    while(!que.empty() && isEnd[que.top()] > 0)
                    {
                        --isEnd[que.top()];
                        que.pop();
                    }
                }
                cur = que.top();
                if(cur != pre)
                {
                    pre = cur;
                    res.push_back(make_pair(height.first, cur));
                }
            }
            return res;
        }
};
```
## 241. Different Ways to Add Parentheses
### 解题思路
> * 每个运算选项都有可能是最后一个运算，由此展开进行求算；
> * 使用递归来求解，要注意仔细观察原函数的输入和输出来确定递归的调用方式；

### 代码
```
class Solution
{
    public:
        vector<int> diffWaysToCompute(string input)
        {
            vector<int> res;
            int len = input.size();
            for(int i = 0; i < len; ++i)
            {
                if(input[i] == '+' || input[i] == '-' || input[i] == '*')
                {
                    vector<int> r1 = diffWaysToCompute(input.substr(0, i));
                    vector<int> r2 = diffWaysToCompute(input.substr(i+1));
                    for(const auto a : r1)
                    {
                        for(const auto b : r2)
                        {
                            if(input[i] == '+')
                                res.push_back(a + b);
                            else if(input[i] == '-')
                                res.push_back(a - b);
                            else if(input[i] == '*')
                                res.push_back(a * b);
                        }
                    }
                }
            }
            if(res.empty())
            {
                int temp = 0;
                for(const auto ch : input)
                {
                    temp = temp * 10 + ch - '0';
                }
                res.push_back(temp);
            }
            return res;
        }
};
```
## 282. Expression Add Operators
### 结题思路
> * 使用dfs进行深度搜索，用两个参数pre和val保持计算优先级；
> * pre表示已经计算的出的结果，val表示先阶段计算得出的结果但是不确定后面的运算符是+还是×，如果是×就需要考虑优先级；
> * +： pre = pre + val; val = temp;
    -:  pre = pre + val; val = -temp;
    *:  pre = pre; val = val * temp;
    
### 代码
```
typedef long long ll;

class Solution
{
    public:
        vector<string> addOperators(string num, int target)
        {
            vector<string> res;
            dfs(res, num.size(), num, target, 0, 0, 0, "");
            return res;
        }
        void dfs(vector<string> &res, int len, string num, ll target, int cur, ll pre, ll val, string path)
        {
            if(cur == len && pre + val == target)
            {
                res.push_back(path);
                return;
            }
            ll temp = 0;
            for(int i = cur; i < len; ++i)
            {
                temp = temp * 10 + num[i] - '0';
                string s = to_string(temp);
                if(cur != 0)
                {
                    dfs(res, len, num, target, i+1, pre+val, temp, path + '+' + s);
                    dfs(res, len, num, target, i+1, pre+val, -temp, path + '-' + s);
                    dfs(res, len, num, target, i+1, pre, temp * val, path + '*' + s);
                }
                else
                    dfs(res, len, num, target, i+1, 0, temp, s);
                if(num[cur] == '0')
                    break;
            }
        }
};
```

## 312. Burst Balloons
### 解题思路
> * 在nums两端各添加一个1；
> * 设DP[i][j]表示从i~j的计算结果，则整个计算结果为DP[1][N]，N表示nums添加1之前的长度；
> * 如果x是i~j中最后一个气球，则其结果为：`nums[i-1]*nums[x]*nums[j+1]`;
> * 则使用DP可以得到状态公式：
`dp[i][j] = max(dp[i][j], dp[i][x-1] + nums[i-1]*nums[x]*nums[j+1] + dp[x+1][j])`;

### 代码
```
class Solution
{
    public:
        int maxCoins(vector<int> &nums)
        {
            int len = nums.size();
            nums.insert(nums.begin(), 1);
            nums.insert(nums.end(), 1);
            vector<vector<int>> dp(len+2, vector<int>(len+2, 0));
            for(int k = 1; k <= len; ++k)
            {
                for(int i = 1; i <= len-k+1; ++i)
                {
                        for(int j = i; j < i+k; ++j)
                        {
                            dp[i][i+k-1] = max(dp[i][i+k-1], dp[i][j-1] + nums[i-1]*nums[j]*nums[i+k] + dp[j+1][i+k-1]); 
                        }
                }
            }
            return dp[1][len];
        }
};
```

## 315. Count of Smaller Numbers After Self
### 解题思路I
> * 使用归并排序，在归并排序的过程中一段一段地去计算结果；
> * 对于每一阶段归并排序的左右两部分，左半部分每个元素都去右半部分中找`Smaller Number`，由于是在归并排序之后再去找，所以只需要扫描一遍；
> * 具体分析可以看[这里][8]！

### 代码
```
class Solution
{
    public:
        vector<int> countSmaller(vector<int> &nums)
        {
            int len = nums.size();
            vector<int> res(len, 0);
            vector<int> index;
            for(int i = 0; i < len; ++i)
                index.push_back(i);
            vector<int> numUpdate = nums;
            vector<int> indexUpdate = index;
            solve(res, nums, index, 0, len, numUpdate, indexUpdate);
            return res;
        }
        void solve(vector<int> &res, vector<int> &nums, vector<int> &index, int start, int end, vector<int> &numUpdate, vector<int> &indexUpdate)
        {
            if(end - start <= 1)
                return;
            int mid = (start + end) / 2;
            solve(res, nums, index, mid, end, numUpdate, indexUpdate);
            solve(res, nums, index, start, mid, numUpdate, indexUpdate);
            int r = mid;
            int t = mid;
            int s = start;
            for(int l = start; l < mid; ++l)
            {
                while(nums[l] > nums[r] && r < end)
                    r++;
                while(t < end && nums[t] <= nums[l])
                {
                    numUpdate[s] = nums[t];
                    indexUpdate[s++] = index[t++];
                }
                numUpdate[s] = nums[l];
                indexUpdate[s++] = index[l];
                res[index[l]] += r - mid;
            }
            for(int i = start; i < end; ++i)
            {
                nums[i] = numUpdate[i];
                index[i] = indexUpdate[i];
            }
        }
};

```
### 解题思路II
> * 首先对数据进行拷贝排序，使用map保存其序列号值；
> * 使用了Fenwick树结构，保存数据的大小个数等信息；
> * 遍历数组结构，每次获得当前数值的结果后，将当前数值添加进树结构中，并进行树结构更新；

### 代码
```
class FenwickTree
{
    vector<int> sumArray;
    int n;
    inline int lowBit(int x)
    {
        return x & -x;
    }

public:
    FenwickTree(int n) : n(n), sumArray(n+1, 0) {}

    void add(int x, int d)
    {
        while(x <= n)
        {
            sumArray[x] += d;
            x += lowBit(x);
        }
    }

    int sum(int x)
    {
        int res = 0;
        while(x > 0)
        {
            res += sumArray[x];
            x -= lowBit(x);
        }
        return res;
    }
};

class Solution
{
    public:
        vector<int> countSmaller(vector<int> &nums)
        {
            vector<int> temp = nums;
            sort(temp.begin(), temp.end());
            unordered_map<int, int> dic;
            for(int i = 0; i < temp.size(); ++i)
                dic[temp[i]] = i+1;
            FenwickTree tree(nums.size());
            vector<int> res(nums.size(), 0);
            for(int i = nums.size()-1; i >= 0; --i)
            {
                res[i] = tree.sum(dic[nums[i]] - 1);
                tree.add(dic[nums[i]], 1);
            }
            return res;
        }
};
```

## 327. Count of Range Sum
### 解题思路
> * 详细讲解看[这里][9]！

### 代码
```
class Solution
{
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        int size=nums.size();
        if(size==0)  
            return 0;
        vector<long> sums(size+1, 0);
        for(int i=0; i<size; i++)  
            sums[i+1]=sums[i]+nums[i];
        return solve(sums, 0, size+1, lower, upper);
    }
   
    int solve(vector<long>& sums, int start, int end, int lower, int upper)
    {
        if(end-start<=1)  return 0;
        int mid=(start+end)/2;
        int count=solve(sums, start, mid, lower, upper) + solve(sums, mid, end, lower, upper);
        int m=mid, n=mid, t=mid, len=0;
        vector<long> cache(end-start, 0);
        for(int i=start, s=0; i<mid; i++, s++)
        {
            while(m<end && sums[m]-sums[i]<lower) 
                m++;
            while(n<end && sums[n]-sums[i]<=upper) 
                n++;
            count+=n-m;
            while(t<end && sums[t]<sums[i]) 
                cache[s++]=sums[t++];
            cache[s]=sums[i];
            len=s;
        }
        
        for(int i=0; i<=len; i++)  
            sums[start+i]=cache[i];
        return count;
    }
};
```


  [1]: https://leetcode.com/problems/the-skyline-problem/
  [2]: https://leetcode.com/problems/different-ways-to-add-parentheses/
  [3]: https://leetcode.com/problems/expression-add-operators/
  [4]: https://leetcode.com/problems/burst-balloons/
  [5]: https://leetcode.com/problems/count-of-smaller-numbers-after-self/
  [6]: https://leetcode.com/problems/count-of-range-sum/
  [7]: https://briangordon.github.io/2014/08/the-skyline-problem.html
  [8]: https://discuss.leetcode.com/topic/73300/share-my-c-mergesort-solution
  [9]: https://discuss.leetcode.com/topic/33738/share-my-solution