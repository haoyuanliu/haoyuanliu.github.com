---
title: LeetCode Greedy
categories: LeetCode
tags:
  - LeetCode
  - Greedy
abbrlink: 54482
date: 2017-02-28 17:36:40
---

本篇文章的主要内容是LeetCode有关贪心算法的习题练习，主要包含如下题目：

[44. Wildcard Matching][1]
[45. Jump Game II][2]
[55. Jump Game][3]
[122. Best Time to Buy and Sell Stock II][4]
[134. Gas Station][5]
[135. Candy][6]
[316. Remove Duplicate Letters][7]
[321. Create Maximum Number][8]
[330. Patching Array][9]
[376. Wiggle Subsequence][10]
[392. Is Subsequence][11]
[402. Remove K Digits][12]
[406. Queue Reconstruction by Height][13]
[435. Non-overlapping Intervals][14]
[452. Minimum Number of Arrows to Burst Balloons][15]
[455. Assign Cookies][16]
[502. IPO][17]

<!--more-->


## 44. Wildcard Matching
### 解题思路
使用动态规划的思路，dp[i][j]表示字符串s的前i个字符与字符串p的前j个字符是否匹配，然后：
如果`p[j] == '*'`，则`dp[i][j+1] = dp[i][j] || dp[i-1][j]` ('*'匹配与不匹配)；
如果`p[j] != '*'`, 则只有`p[j] == s[i] || p[j] == '?'`的时候，`dp[i][j+1] = dp[i-1][j]`;

### 代码
```
class Solution
{
    public:
        bool isMatch(string s, string p)
        {
            int m = s.size();
            int n = p.size();
            int cnt = count(p.begin(), p.end(), '*');
            if(n - cnt > m)
                return false;
            vector<bool> dp(n+1, false);
            dp[0] = 1;
            for(int i = 0; i < n; ++i)
                if(p[i] == '*')
                    dp[i+1] = dp[i];
            for(int i = 1; i <= m; ++i)
            {
                vector<bool> cur(n+1, false);
                for(int j = 1; j <= n; ++j)
                {
                    if(p[j-1] == '*')
                        cur[j] = cur[j-1] || dp[j];
                    else
                    {
                        if(p[j-1] == s[i-1] || p[j-1] == '?')
                            cur[j] = dp[j-1];
                    }
                }
                dp = cur;
            }
            return dp[n];
        }
};
```

## 45. Jump Game II
### 解题思路
维持一个curJump变量，保存目前为止所能跳转到的最大下标，lastJump表示最近一次最大跳转到达的元素下标，遍历整个数组并更新curJump和lastJump变量，如果lastJump已经到达或者超过数组范围，返回跳转计数。

### 代码
```
class Solution
{
    public:
        int jump(vector<int> &nums)
        {
            int len = nums.size();
            int curJump = 0;
            int lastJump = 0;
            int count = 0;
            for(int i = 0; i < len; ++i)
            {
                if(lastJump < i)
                {
                    count++;
                    lastJump = curJump;
                }
                if(lastJump >= len-1)
                    return count;
                if(curJump >= i)
                    curJump = max(curJump, i + nums[i]);
            }
            return count;
        }
};
```

## 55. Jump Game
### 解题思路I
直接使用贪心的算法解决，每遍历一个节点，更新最大Jump的距离maxJump，如果maxJump为0则无法跳到最后节点。

### 代码
```
class Solution
{
public:
    bool canJump(vector<int>& nums)
    {
        int len = nums.size();
        int maxJump = nums[0];
        for(int i = 1; i < len; ++i)
        {
            if(maxJump == 0)
                return false;
            maxJump = max(--maxJump, nums[i]);
        }
        return true;
    }
};
```

### 解题思路II
对思路I的算法进行优化，维持一个cover变量，记录能够跳到的最大数组下标，每遍历一个节点，更新`cover = max(cover, i + nums[i])`，一旦`cover >= len - 1`则肯定能够跳到最后一个节点，直接返回true；

### 代码
```
class Solution
{
    public:
        bool canJump(vector<int> &nums)
        {
            int len = nums.size();
            int cover = 0;
            for(int i = 0; i < len; ++i)
            {
                if(cover >= len - 1)
                    return true;
                if(cover >= i)
                    cover = max(cover, i + nums[i]);
            }
            return false;
        }
};
```

## 122. Best Time to Buy and Sell Stock II
### 解题思路
股票的买入和抛售，原则就是最低价买入，然后最高价抛售，价格上升的区间就是获取利润的区间，直接遍历整个数组，将上升趋势的价格差额累加起来就得到最终的最大利润。

### 代码
```
class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
        int res = 0;
        for(int i = 1; i < prices.size(); ++i)
        {
            res += max(prices[i] - prices[i-1], 0);
        }
        return res;
    }
};
```
## 134. Gas Station
### 解题思路
1. 如果从A点无法到达B点，那么在A、B两点之间任意一点都无法到达B点，也就是说，如果判断得到从A点无法到达B点，那么A、B两点之间的任何一点都不能作为起始点，因为都到达不了B点。（证明：因为B点无法到达，所以B点的cost > gas; 假设A、B中间一点C，因为从A到B点无法到达，所以总体的cost > gas, A点是可以到达Ｃ点的，所以AC段cost < gas，那么CB段必定cost > gas，所以C点无法到达B点）
2. 对于全部路程，总体gas大于总体cost才有解，否则无解；

### 代码
```
class Solution 
{
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        int total = 0;
        int tank = 0;
        int start = 0;
        for(int i = 0; i < gas.size(); ++i)
        {
            if((tank = tank + gas[i] - cost[i]) < 0)
            {
                start = i+1;
                total += tank;
                tank = 0;
            }
        }
        return (total + tank >= 0) ? start : -1;
    }
};
```

## 135. Candy
### 解题思路
确保每个小孩至少一颗糖，初始化每个人一颗，同时观察发现，只有当存在等级差别的时候才需要增加糖的数量，向后向前遍历两遍数组，计算需要增加的糖果数量，最后加和给出结果。

### 代码
```
class Solution
{
public:
    int candy(vector<int>& ratings)
    {
        int res = 0;
        int len = ratings.size();
        if(len < 2) return len;
        vector<int> candies(len, 1);
        for(int i = 1; i < len; ++i)
        {
            if(ratings[i] > ratings[i-1])
                candies[i] = candies[i-1] + 1;
        }

        for(int i = len-2; i >= 0; --i)
        {
            if(ratings[i] > ratings[i+1])
                candies[i] = max(candies[i+1]+1, candies[i]);
        }
        for(int i = 0; i < len; ++i)
            res += candies[i];
        return res;
    }
};
```

## 316. Remove Duplicate Letters
### 解题思路
使用栈结构的性质，对于每一个字符，如果已经在栈中了，就跳过；
如果没有在栈中，如果该字符小于栈顶的字符，并且栈顶字符在后面字符串中还有（计数值大于0），则将栈顶元素出栈，然后继续循环判断新的栈顶元素是否需要出栈，循环判断结束后最后将新字符入栈。

### 代码
```
class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        string res = "0";
        int len = s.size();
        int m[256] = {0};
        int visited[256] = {0};
        for(int i = 0; i < len; ++i)
            m[s[i]]++;

        for(const auto c : s)
        {
            m[c]--;
            if(visited[c]) continue;
            while(c < res.back() && m[res.back()])
            {
                visited[res.back()] = 0;
                res.pop_back();
            }
            res += c;
            visited[c] = 1;
        }
        return res.substr(1);
    }
};
```

## 321. Create Maximum Number
### 解题思路
核心算法是遍历`k1`，`nums1`取`k1`个数字，`nums2`取`k-k1`个数字，都获得其最大值然后进行合并，最后比较大小返回最大的那一个。
这道题学习了`StefanPochmann`大神的代码，真的厉害，各种c++的技巧用得太巧妙了。`StefanPochmann`大神对于函数重载以及引用等技巧的使用太赞了！

### 代码
```
class Solution
{
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<int> res;
        for(int i = max(0, k - n2); i <= min(k, n1); ++i)
        {
            res = max(res, maxNumber(maxNumber(nums1, i), maxNumber(nums2, k-i)));
        }
        return res;
    }

    vector<int> maxNumber(vector<int> nums, int k)
    {
        int drop = nums.size() - k;
        vector<int> res;
        for(const auto n : nums)
        {
            while(drop && !res.empty() && n > res.back())
            {
                res.pop_back();
                drop--;
            }
            res.push_back(n);
        }
        res.resize(k);
        return res;
    }

    vector<int> maxNumber(vector<int> nums1, vector<int> nums2)
    {
        vector<int> res;
        while(nums1.size() + nums2.size())
        {
            vector<int> &temp = nums1 > nums2 ? nums1 : nums2;
            res.push_back(temp[0]);
            temp.erase(temp.begin());
        }
        return res;
    }
};
```

## 330. Patching Array
### 解题思路
miss表示[1,n]中我们无法得到的最小值，也就意味着我们可以得到小于miss的所有数字，取值区间为[1, miss)。如果nums数组中有元素`num < miss`，之前我们可以得到范围[1, miss)的数值，现在统一加上num就可以得到[1, miss+num)范围的数值；如果数组中没有小于miss的值，则此时我们需要加入一个新的值来达到要求，这里最好的选择是miss，同时结果计数进行累加计算；
`StefanPochmann`大神详细题解可以参考这个<[链接][18]>！

### 代码
```
class Solution
{
public:
    int minPatches(vector<int>& nums, int n)
    {
        int len = nums.size();
        int res = 0;
        int cur = 0;
        long miss = 1;
        while(miss <= n)
        {
            if(cur < len && nums[cur] <= miss)
            {
                miss += nums[cur++];
            }
            else
            {
                miss <<= 1;
                res++;
            }
        }
        return res;
    }
};
```

## 376. Wiggle Subsequence
### 解题思路
使用贪心算法解决，遍历整个数组，使用pos表示已遍历数组中符合要求的连续数列长度，且最后的difference是正值，neg就表示最后difference是复制的连续数列长度。如此以来，如果`nums[i] > nums[i-1]`，则difference是正值，此时`pos = neg + 1`，反之`neg = pos + 1`；

### 代码
```
class Solution
{
public:
    int wiggleMaxLength(vector<int>& nums)
    {
        int len = nums.size();
        int pos = 1;
        int neg = 1;
        for(int i = 1; i < len; ++i)
        {
            if(nums[i] > nums[i-1])
                pos = neg + 1;
            else if(nums[i] < nums[i-1])
                neg = pos + 1;
        }
        return min(len, max(neg, pos));
    }
};
```

## 392. Is Subsequence
### 解题思路
这道题按照顺序去比较每一个字符是否相同即可；

### 代码
```
class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int i = 0;
        int len = s.size();
        if(len == 0)
            return true;
        for(const auto x : t)
        {
            if(x == s[i])
            {
                if(++i == len)
                    return true;
            }
        }
        return false;
    }
};
```

## 402. Remove K Digits
### 解题思路
利用string的栈结构特性，保证位于高位的数字达到最小即可，最后进行字符串的整理和特例处理。

### 代码
```
class Solution
{
public:
    string removeKdigits(string num, int k)
    {
        int len = num.size();
        string res = "";
        int drop = k;
        for(int i = 0; i < len; ++i)
        {
            while(drop && res.size() && num[i] < res.back())
            {
                res.pop_back();
                drop--;
            }
            res += num[i];
        }
        while(drop && res.size())
        {
            res.pop_back();
            drop--;
        }
        while(res[0] == '0')
            res.erase(res.begin());
        return res.empty() ? "0" : res;
    }
};
```

## 406. Queue Reconstruction by Height
### 解题思路I
将people数组元素进行排序，然后按照身高从矮到高的顺序置入结果队列中，通过遍历结果队列更新计数值来决定应该置入的位置。

### 代码
```
class Solution
{
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people)
    {
        int len = people.size();
        vector<pair<int, int>> res(len, {-1, -1});
        sort(people.begin(), people.end());
        int count, i;
        for(const auto p : people)
        {
            count = 0;
            i = 0;
            for(i = 0; i < len; ++i)
            {
                if(res[i].first == -1 || res[i].first >= p.first)
                    count++;
                if(count > p.second)
                    break;
            }
            res[i].first = p.first;
            res[i].second = p.second;
        }
        return res;
    }
};
```

### 解题思路II
首先还是对people数组排序，身高高的排在前面，身高一样的，前面人少的排在前面。
简单来说就是按照身高从高到低进行排序，然后高个子先置入结果数组中。这样每一个people数组元素置入的时候，由于比他高的全都已经在结果数组中了，所以此时他的位置也就直接确定了，使用insert执行置入操作即可；

### 代码
```
class Solution
{
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people)
    {
        auto comp = [](const pair<int, int> &a, const pair<int, int> &b)
        {
            return a.first > b.first || (a.first == b.first && a.second < b.second);
        };

        vector<pair<int, int>> res;
        sort(people.begin(), people.end(), comp);
        for(auto p : people)
            res.insert(res.begin()+p.second, p);
        return res;
    }
};
```

## 435. Non-overlapping Intervals
### 解题思路
首先对数组进行排序，按照start从小到大进行排序，如果start相同，按照包含区间从小到大进行排序。
遍历整个数组，如果当前interval的start小于前一个interval的end，即`cur.start < pre.end`，则此时必定发生overlapping，结果计数加一，如果`cur.end < pre.end`时，cur包含在pre中，此时应该舍弃pre并更新cur为新的pre。
反之，如果一开始就`cur.start >= pre.end`的话，区间没有overlapping，更新cur为新的pre，继续遍历即可。

### 代码
```
class Solution
{
public:
    int eraseOverlapIntervals(vector<Interval>& intervals)
    {
        int res = 0;
        int len = intervals.size();
        if(len < 2) return res;
        auto cmp = [](const Interval &a, const Interval &b)
        {
            return a.start < b.start || (a.start == b.start && a.end - a.start < b.end - b.start);
        };

        sort(intervals.begin(), intervals.end(), cmp);
        int pre = 0;
        for(int i = 1; i < len; ++i)
        {
            if(intervals[i].start < intervals[pre].end)
            {
                res++;
                if(intervals[i].end < intervals[pre].end)
                    pre = i;
            }
            else
                pre = i;
        }
        return res;
    }
};
```

## 452. Minimum Number of Arrows to Burst Balloons
### 解题思路
首先对points数组进行排序，维持left和right代表公共区间的左右边界，遍历整个数组，如果气球范围出了公共区间，则此时应该射一箭，反之，则应该继续更新公共区间，如此遍历全部气球数组。
注意这里公共区间边界如果left==right也是可以的；遍历过程中最后一箭是没有射出去的，所以res初始化为1。

### 代码
```
class Solution
{
public:
    int findMinArrowShots(vector<pair<int, int>>& points)
    {
        if(points.size() == 0)
            return 0;
        auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
        {
            return a.first < b.first;
        };
        sort(points.begin(), points.end(), cmp);

        int res = 1;
        int left = points[0].first;
        int right = points[0].second;
        for(int i = 1; i < points.size(); ++i)
        {
            if(points[i].first > right)
            {
                res++;
                left = points[i].first;
                right = points[i].second;
            }
            else
            {
                left = max(left, points[i].first);
                right = min(right, points[i].second);
            }
        }
        return res;
    }
};
```

## 455. Assign Cookies
### 解题思路
对两个数组进行排序，首先用最大的饼干来满足要求最高的孩子，如果无法满足，则换下一个要求小一点的孩子，如果能够满足，则执行`--`操作继续进行匹配遍历。

### 代码
```
class Solution
{
public:
    int findContentChildren(vector<int>& g, vector<int>& s)
    {
        int res = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int x = g.size() - 1;
        int y = s.size() - 1;
        while(x >= 0 && y >= 0)
        {
            if(g[x] > s[y]) x--;
            else if(g[x--] <= s[y--]) res++;
        }
        return res;
    }
};
```
## 502. IPO
### 解题思路
使用一个大顶堆结构保存现阶段可以进行的项目，使用vector保存那些不能进行的项目，每次都只执行堆顶的利益最大的项目，执行完毕之后，将已执行的项目pop删除，遍历vector更新可执行的项目，置入到堆中并从vector中删除。

### 代码
```
class Solution
{
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital)
    {
        int res = W;
        priority_queue<int> doable;
        vector<pair<int, int>> notdoable;

        for(int i = 0; i < Profits.size(); ++i)
        {
            if(Profits[i])
            {
                if(Capital[i] <= W)
                    doable.push(Profits[i]);
                else
                    notdoable.push_back(make_pair(Profits[i], Capital[i]));
            }
        }
        while(k-- && doable.size())
        {
            res += doable.top();
            doable.pop();
            for(auto it = notdoable.begin(); it != notdoable.end(); )
            {
                if(it->second <= res)
                {
                    doable.push(it->first);
                    it = notdoable.erase(it);
                }
                else
                    it++;
            }
        }
        return res;
    }
};
```


  [1]: https://leetcode.com/problems/wildcard-matching/?tab=Description
  [2]: https://leetcode.com/problems/jump-game-ii/?tab=Description
  [3]: https://leetcode.com/problems/jump-game/?tab=Description
  [4]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/?tab=Description
  [5]: https://leetcode.com/problems/gas-station/?tab=Description
  [6]: https://leetcode.com/problems/candy/?tab=Description
  [7]: https://leetcode.com/problems/remove-duplicate-letters/?tab=Description
  [8]: https://leetcode.com/problems/create-maximum-number/?tab=Description
  [9]: https://leetcode.com/problems/patching-array/?tab=Description
  [10]: https://leetcode.com/problems/wiggle-subsequence/?tab=Description
  [11]: https://leetcode.com/problems/is-subsequence/?tab=Description
  [12]: https://leetcode.com/problems/remove-k-digits/?tab=Description
  [13]: https://leetcode.com/problems/queue-reconstruction-by-height/?tab=Description
  [14]: https://leetcode.com/problems/non-overlapping-intervals/?tab=Description
  [15]: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/?tab=Description
  [16]: https://leetcode.com/problems/assign-cookies/?tab=Description
  [17]: https://leetcode.com/problems/ipo/?tab=Description
  [18]: https://discuss.leetcode.com/topic/35494/solution-explanation