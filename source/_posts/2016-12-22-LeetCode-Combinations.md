---
title: LeetCode Combinations
date: 2016-12-22 14:58:29
categories: LeetCode
tags: [LeetCode, Combination]
---

本文包含如下题目：
[17. Letter Combinations of a Phone Number][1]
[31. Next Permutation][2]
[39. Combination Sum][3]
[40. Combination Sum II][4]
[46. Permutations][5]
[47. Permutations II][6]
[60. Permutation Sequence][7]
[77. Combinations][8]
[216. Combination Sum III][9]
[377. Combination Sum IV][10]

<!--more-->

## 17. Letter Combinations of a Phone Number
### 解题思路
> * 加入现在输入是`23`，则首先把`2`对应的字符放到结果res中，结果res为`[a, b, c]`;
> * `3`所包含的字符有`d, e, f`则首先把res的首项取出来，分别和`d, e, f`组合之后再次放进res中，此时为`[b, c, ad, ae, af]`;
> * 不断地完成如上操作即可；

### 代码
```
class Solution
{
    public:
        vector<string> letterCombinations(string digits)
        {
            string str[10] = {" ", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
            int len[10] = {1, 1, 3, 3, 3, 3, 3, 4, 3, 4};
            vector<string> res;
            if(digits.size() == 0)
                return res;
            res.push_back("");
            for(int i = 0; i < digits.size(); ++i)
            {
                int sz = res.size();//注意这里要保存res的大小，以便下面循环的进行
                for(int j = 0; j < sz; ++j)
                {
                    string temp = res[0];
                    res.erase(res.begin());
                    for(int k = 0; k < len[digits[i] - '0']; ++k)
                    {
                        res.push_back(temp + str[digits[i] - '0'][k]);
                    }
                }
            }
            return res;
        }
};
```

## 31. Next Permutation
### 解题思路
> * 终极状态是`321`这种呈递减顺序排布的，也是数字组合的最大值；
> * 首先找到第一个破坏上述规则的数，其位置记为start；
> * 将start对应元素与从尾部开始第一个大于它的元素交换；
> * 对于start后面的元素进行一个逆序处理即可；
> * 详细分析可以参考[LeetCode的官方Solution][11]；

### 代码
```
class Solution
{
    public:
        void nextPermutation(vector<int> &nums)
        {
            int start = -1;
            for(int i = nums.size() - 2; i >= 0; --i)
            {
                if(nums[i] < nums[i+1])
                {
                    start = i;
                    break;
                }
            }
            if(start == -1)
            {
                reverse(nums.begin(), nums.end());
                return;
            }
            for(int i = nums.size()-1; i > start; --i)
            {
                if(nums[start] < nums[i])
                {
                    swap(nums[start], nums[i]);
                    break;
                }
            }
            reverse(nums.begin()+start+1, nums.end());
        }
};
```

## 39. Combination Sum
### 解题思路
> * 使用回溯和递归，不断地去找就好；
> * 注意给出的数据均为正数，且没有重复的数值；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > combinationSum(vector<int>& candidates, int target)
        {
            vector<vector<int> > res;
            vector<int> temp;
            sort(candidates.begin(), candidates.end());
            solve(res, temp, candidates, 0, target, 0);
            return res;
        }
        void solve(vector<vector<int> > &res, vector<int> &temp, vector<int> candidates, int cur, int target, int sum)
        {
            if(sum == target)
            {
                res.push_back(temp);
                return;
            }
            for(int i = cur; i < candidates.size(); ++i)
            {
                if(sum + candidates[i] <= target)
                {
                    temp.push_back(candidates[i]);
                    solve(res, temp, candidates, i, target, sum+candidates[i]);
                    temp.pop_back();
                }
            }
        }
};
```

## 40. Combination Sum II
### 解题思路
> * 这一题跟上面39题类似，注意这里给出的数据中包含重复的数值；
> * 为了避免重复解，对candidates进行排序，重复数值只对第一个进行迭代求解，其余的跳过；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > combinationSum2(vector<int> &candidates, int target)
        {
            vector<vector<int> > res;
            vector<int> temp;
            sort(candidates.begin(), candidates.end());
            solve(res, temp, candidates, target, 0, 0, candidates.size());
            return res;
        }
        void solve(vector<vector<int> > &res, vector<int> &temp, vector<int> candidates, int target, int cur, int sum, int len)
        {
            if(sum == target)
            {
                res.push_back(temp);
                return;
            }
            for(int i = cur; i < len; ++i)
            {
                if(sum + candidates[i] <= target)
                {
                    temp.push_back(candidates[i]);
                    solve(res, temp, candidates, target, i+1, sum+candidates[i], len);
                    temp.pop_back();
                    while(i+1 < len && candidates[i] == candidates[i+1]) //如果下一个值等于当前值，则跳过，
                        i++;
                }
            }
        }
};
```


## 46. Permutations
### 解题思路I
> * 这一题仍然是排列组合，但是不同的是这一次不看数值的大小，直接按照排列组合的顺序输出；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > permute(vector<int> &nums)
        {
            vector<vector<int> > res;
            vector<int> temp;
            int size = 1;
            int i, j;

            res.push_back(nums);
            int len = nums.size();
            if(len == 1)
                return res;

            for(int i = 0; i < len; ++i)
            {
                size = size * (i+1);
                temp.push_back(i+1);
            }
            size = size-1;
            while(size--)
            {
                i = j = len - 1;
                while(temp[i-1] >= temp[i])
                    i--;
                while(temp[j] <= temp[i-1])
                    j--;
                swap(temp[i-1], temp[j]);
                swap(nums[i-1], nums[j]);

                j = len - 1;
                while(i < j)
                {
                    swap(temp[i], temp[j]);
                    swap(nums[i++], nums[j--]);
                }

                res.push_back(nums);
            }
            return res;
        }
};
```
### 解题思路II
> * 也可以使用dfs进行求解，遍历每一种不同的组合方式；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > permute(vector<int> &nums)
        {
            vector<vector<int> > res;
            dfs(res, nums, 0);
            return res;
        }
        void dfs(vector<vector<int> > &res, vector<int> &nums, int cur)
        {
            if(cur >= nums.size())
            {
                res.push_back(nums);
                return;
            }
            for(int i = cur; i < nums.size(); ++i)
            {
                swap(nums[cur], nums[i]);
                dfs(res, nums, cur+1);
                swap(nums[cur], nums[i]);
            }
        }
};
```


## 47. Permutations II
### 解题思路I
> * 首先使用`sort`函数整理数据，然后按照next premutation的算法不断进行求取；
> * 这里需要注意的是，交换过程中，如果相等则不进行交换，使用`<=`过滤掉重复的答案；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > permuteUnique(vector<int> & nums)
        {
            vector<vector<int> > res;
            sort(nums.begin(), nums.end());
            res.push_back(nums);
            int len = nums.size();
            int i, j;
            if(len == 1)
                return res;
            while(1)
            {
                i = j = len - 1;
                while(nums[i] <= nums[i-1] && i >= 0)
                    i--;
                if(i == -1 || i == 0)
                    break;
                while(nums[j] <= nums[i-1])
                    j--;
                swap(nums[i-1], nums[j]);
                j = len - 1;
                while(i < j)
                    swap(nums[i++], nums[j--]);
                res.push_back(nums);
            }
            return res;
        }
};
```

### 解题思路II
> * 这里借鉴了[LeetCode Discuss][12]中的思路，仍然采用的是dfs搜索的方式去遍历每一种可能的结果；
> * 不同的是，针对本题没有回溯操作，nums作为参数前面并没有加`&`号；
> * 这个思路搞了好久没有弄清楚，有大神懂的求告知；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > permuteUnique(vector<int> & nums)
        {
            vector<vector<int> > res;
            sort(nums.begin(), nums.end());
            dfs(res, nums, 0);
            return res;
        }
        void dfs(vector<vector<int> > &res, vector<int> nums, int cur)
        {
            if(cur == nums.size()-1)
            {
                res.push_back(nums);
                return;
            }
            for(int i = cur; i < nums.size(); ++i)
            {
                if(i != cur && nums[cur] == nums[i])
                    continue;
                swap(nums[cur], nums[i]);
                dfs(res, nums, cur+1);
            }
        }
};
```

## 60. Permutation Sequence
### 解题思路
> * 如果不断调用next permutation算法，则肯定会超时；
> * 我们一位一位的计算，一共有`n!`种序列，第一位有`n`中选择，每种都对应`(n-1)!`种序列，利用这种关系不断计算每一位的选择即可；

### 代码
```
class Solution
{
    public:
        string getPermutation(int n, int k)
        {
            string res = "";
            int nums[n];
            nums[0] = 1;
            for(int i = 1; i < n; ++i)
                nums[i] = i * nums[i-1];
            vector<int> index;
            for(int i = 1; i <= n; ++i)
                index.push_back(i);
            k = k - 1;
            for(int i = n-1; i >= 0; --i)
            {
                int temp = k / nums[i];
                res += *(index.begin() + temp) + '0';
                index.erase(index.begin() + temp);
                k = k % nums[i];
            }
            return res;
        }
};
```


## 77. Combinations
### 解题思路
> * 这个题直接用递归和回溯就解决了； 

### 代码
```
class Solution
{
    public:
        vector<vector<int> > combine(int n, int k)
        {
            vector<vector<int> > res;
            vector<int> temp;
            pushBack(res, temp, 1, k, n, 0);
            return res;
        }

        void pushBack(vector<vector<int> > &res, vector<int> &temp, int next, int k, int n, int count)
        {
            if(count == k)
                res.push_back(temp);
            for(int i = next; i <= n; ++i)
            {
                temp.push_back(i);
                pushBack(res, temp, i+1, k, n, count+1);
                temp.erase(temp.end()-1);
            }
        }
};
```


## 216. Combination Sum III
### 解题思路
> * 这道题也是使用递归和回溯就可以解决了；

### 代码
```
class Solution
{
    public:
        vector<vector<int> > combinationSum3(int k, int n)
        {
            vector<vector<int> > res;
            vector<int> temp;
            dfs(res, temp, k, n, 1, 0, 0);
            return res;
        }
        void dfs(vector<vector<int> > &res, vector<int> &temp, int k, int n, int cur, int count, int sum)
        {
            if(count == k)
            {
                if(sum == n)
                {
                    res.push_back(temp);
                    return;
                }
                else
                    return;
            }

            if(cur > 9)
                return;

            for(int i = cur; i < 10; ++i)
            {
                temp.push_back(i);
                dfs(res, temp, k, n, i+1, count+1, sum+i);
                temp.erase(temp.end()-1);
            }
        }
};
```

## 377. Combination Sum IV
### 解题思路I
> * 使用搜索算法进行迭代，TLE超时！

### 代码
```
class Solution
{
    public:
        int combinationSum4(vector<int> &nums, int target)
        {
            int res = 0;
            dfs(res, nums, target, 0);
            return res;
        }
        void dfs(int &res, vector<int> &nums, int target, int sum)
        {
            if(sum == target)
            {
                res++;
                return;
            }
            for(int i = 0; i < nums.size(); ++i)
            {
                if(sum + nums[i] <= target)
                    dfs(res, nums, target, sum+nums[i]);
            }
        }
};
```

### 解题思路II
> * 如果nums包含`1， 2， 3`三个数字，`Sum(nums, 4) = Sum(nums, 4-1) + Sum(nums, 4-2) + Sum(nums, 4-3)`;
> * 如果根据上述等式进行递归迭代求解的话，超时TLE！
> * 根据公式的特性，使用DP进行求解，`dp[i] = Sum(nums, i)`，dp[0]=1初始化即可；

### 代码I
```
class Solution
{
    public:
        int combinationSum4(vector<int> &nums, int target)
        {
            vector<int> dp(target+1, -1);
            dp[0] = 1;
            return solve(dp, nums, target);
        }
        int solve(vector<int> &dp, vector<int> &nums, int target)
        {
            if(dp[target] != -1)
                return dp[target];
            int res = 0;
            for(int i = 0; i < nums.size(); ++i)
            {
                if(target >= nums[i])
                    res += solve(dp, nums, target - nums[i]);
            }
            return dp[target] = res;
        }
};
```
### 代码II
```
class Solution
{
    public:
        int combinationSum4(vector<int> &nums, int target)
        {
            vector<int> dp(target+1, 0);
            dp[0] = 1;
            for(int i = 1; i <= target; ++i)
            {
                for(int j = 0; j < nums.size(); ++j)
                {
                    if(i >= nums[j])
                        dp[i] += dp[i - nums[j]];
                }
            }
            return dp[target];
        }
};
```


  [1]: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
  [2]: https://leetcode.com/problems/next-permutation/
  [3]: https://leetcode.com/problems/combination-sum/
  [4]: https://leetcode.com/problems/combination-sum-ii/
  [5]: https://leetcode.com/problems/permutations/
  [6]: https://leetcode.com/problems/permutations-ii/
  [7]: https://leetcode.com/problems/permutation-sequence/
  [8]: https://leetcode.com/problems/combinations/
  [9]: https://leetcode.com/problems/combination-sum-iii/
  [10]: https://leetcode.com/problems/combination-sum-iv/
  [11]: https://leetcode.com/articles/next-permutation/
  [12]: https://discuss.leetcode.com/topic/8831/a-simple-c-solution-in-only-20-lines/65