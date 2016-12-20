---
title: LeetCode Substring and Subarray
date: 2016-12-20 20:50:48
categories: LeetCode
tags: [LeetCode, Substring, Subarray]
---

本文包含如下题目：
[30. Substring with Concatenation of All Words][1]
[76. Minimum Window Substring][2]
[209. Minimum Size Subarray Sum][3]
[239. Sliding Window Maximum][4]


<!--more-->

## 30. Substring with Concatenation of All Words
### 解题思路
> * 首先构建一个`map<string, int>`保存words中字符串，每个对应int值为1；
> * 然后对搜索字符串进行遍历，将等长的子字符串保存在`map<string, int>`中；
> * 如果有新的子字符串或者相同的子字符串数量超过words所给出的数量，则判定失败。

### 代码
```
class Solution
{
    public:
        vector<int> findSubstring(string s, vector<string> &words)
        {
            int i, j;
            int wordNum = words.size();
            int wordLen = words[0].size();
            int startLen = s.size() - wordLen * wordNum;
            map<string, int> word;
            for(int i = 0; i < wordNum; ++i)
                ++word[words[i]];
            map<string, int> count;
            vector<int> res;
            string temp;
            for(i = 0; i <= startLen; ++i)
            {
                count.clear();
                for(j = 0; j < wordNum; ++j)
                {
                    temp = s.substr(i + wordLen * j, wordLen);
                    if(word.find(temp) == word.end() || ++count[temp] > word[temp])
                        break;
                }
                if(j == wordNum)
                    res.push_back(i);
            }
            return res;
        }
};
```

## 76. Minimum Window Substring
### 解题思路
> * 使用一个`vector<int> ch(128, 0)`保存字符的数据信息；
> * 正如题目描述，需要维持一个窗口，该窗口能够覆盖t中的字符；
> * 计算过程就是窗口的移动过程，需要不断地从窗口头部去掉字符元素，然后在尾部添加新的字符，迭代计算窗口的宽度等数值特征；

### 代码
```
class Solution
{
    public:
        string minWindow(string s, string t)
        {
            vector<int> ch(128, 0);
            for(int i = 0; i < t.size(); ++i)
                ch[t[i]]++;
            int count = t.size();
            int begin, end, head, resLen;
            begin = end = head = 0;
            resLen = s.size() + 1;
            while(end < s.size())
            {
                if(ch[s[end++]]-- > 0)
                    count--;
                while(count == 0)
                {
                    if(end - begin < resLen)
                    {
                        resLen = end - begin;
                        head = begin;
                    }
                    if(ch[s[begin++]]++ == 0)
                        count++;
                }
            }
            return resLen==s.size()+1 ? "" : s.substr(head, resLen);
        }
};
```

## 209. Minimum Size Subarray Sum
### 解题思路
> * 维持一个窗口，不断更新子数组的长度；

### 代码
```
class Solution
{
    public:
        int minSubArrayLen(int s, vector<int> &nums)
        {
            int res, count, begin, end;
            count = begin = end = 0;
            res = nums.size() + 1;
            while(end < nums.size())
            {
                count += nums[end++];
                while(count >= s)
                {
                    if(end - begin < res)
                    {
                        res = end - begin;
                    }
                    count -= nums[begin++];
                }
            }
            return res == nums.size()+1 ? 0 : res;
        }
};
```

## 239. Sliding Window Maximum
### 解题思路I
> * 为了维持窗口，每次向左添加一位，更新最大值；
> * temp[j] = max(nums[j-i], temp[j])其中i表示此时窗口的大小+1;
> * 这种方法效率较低，勉强AC；

### 代码
```
class Solution
{
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k)
        {
            if(k == 0)
                return nums;
            int len = nums.size();
            vector<int> temp = nums;
            for(int i = 1; i < k; ++i)
            {
                for(int j = i; j < len; ++j)
                {
                    temp[j] = max(nums[j-i], temp[j]);
                }
            }
            vector<int> res;
            for(int i = k-1; i < len; ++i)
                res.push_back(temp[i]);
            return res;
        }
};
```
### 解题思路II
> * 使用`deque`维持一个双向队列，保存加入其中数据的下标；
> * 对数组进行遍历，在`deque`不为空的情况下，当遍历到下标i的时候，删掉超出范围k的数据，即下标小于`i-k+1`的数据；
> * 每次加入一个数据nums[i]的时候，删除比他还要小的数据，因为在整个作用范围内，小于nums[i]的数都不可能成为最大的数据；
> * 上述操作维持`deque`是一个降序的队列，取窗口最大值只需要取`deque`的头部数据就可以了。

### 代码
```
class Solution
{
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k)
        {
            vector<int> res;
            if(k == 0)
                return res;
            deque<int> temp;
            for(int i = 0; i < nums.size(); ++i)
            {
                while(!temp.empty() && temp.front() < i-k+1)
                    temp.pop_front();
                while(!temp.empty() && nums[temp.back()] < nums[i])
                    temp.pop_back();
                temp.push_back(i);
                if(i >= k - 1)
                    res.push_back(nums[temp.front()]);
            }
            return res;
        }
};
```

  [1]: https://leetcode.com/problems/substring-with-concatenation-of-all-words/atenation-of-all-words/
  [2]: https://leetcode.com/problems/minimum-window-substring/atenation-of-all-words/
  [3]: https://leetcode.com/problems/minimum-size-subarray-sum/tenation-of-all-words/
  [4]: https://leetcode.com/problems/sliding-window-maximum/