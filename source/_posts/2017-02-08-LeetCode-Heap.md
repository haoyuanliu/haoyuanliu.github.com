---
title: LeetCode Heap
categories:
  - LeetCode
tags:
  - LeetCode
  - Heap
abbrlink: 55086
date: 2017-02-08 22:02:01
---

本文包含如下题目：

[264. Ugly Number II][1]
[295. Find Median from Data Stream][2]
[313. Super Ugly Number][3]
[347. Top K Frequent Elements][4]
[355. Design Twitter][5]
[373. Find K Pairs with Smallest Sums][6]
[378. Kth Smallest Element in a Sorted Matrix][7]
[451. Sort Characters By Frequency][8]

<!--more-->


## 264. Ugly Number II
### 解题思路
使用动态规划的思想，已知`res[0] = 1`，此时可以得到`res[1] = min(res[0]*2, res[0]*3, res[0]*5)`，然后可以求得`res[2] = min(res[1]*2, res[0]*3, res[0]*5`。

### 代码
```
class Solution
{
public:
    int nthUglyNumber(int n)
    {
		if(n < 0) return 0;
		vector<int> res(n, 1);
		int t2 = 0, t3 = 0, t5 = 0;
		for(int i = 1; i < n; ++i)
		{
			res[i] = min(res[t2]*2, min(res[t3]*3, res[t5]*5));
			if(res[i] == res[t2]*2) t2++;
			if(res[i] == res[t3]*3) t3++;
			if(res[i] == res[t5]*5) t5++;
		}
		return res[n-1];
    }
};
```

## 295. Find Median from Data Stream
### 解题思路
利用STL库函数中的`priority_queue`，维持一个大顶堆和一个小顶堆（利用负数实现），然后动态更新保持两个堆的元素数量的平衡，最后返回中位数。
### 代码
```
class MedianFinder
{
    priority_queue<int> small, large;
public:
    void addNum(int num)
    {
        if(!large.empty() && -large.top() < num)
            large.push(-num);
        else
            small.push(num);
        if(small.size() - large.size() == 2)
        {
            large.push(-small.top());
            small.pop();
        }
        else if(large.size() -  small.size() == 2)
        {
            small.push(-large.top());
            large.pop();
        }
    }

    double findMedian()
    {
        if(small.size() > large.size()) return small.top();
        else if(small.size() < large.size()) return -large.top();
        else return (small.top() - large.top()) / 2.0;
    }
};
```

## 313. Super Ugly Number
### 解题思路
使用动态规划的思路，使用一个`res`(vector)保存顺序排列的丑数，然后使用一个`idx`(vector)保存每个primes中元素所对应的乘法因子，然后每次取乘法结果的最小的值作为新的丑数，同时遍历`idx`进行去重操作。

### 代码
```
class Solution
{
public:
    int nthSuperUglyNumber(int n, vector<int>& primes)
    {
        vector<int> res(n, 1);
        vector<int> idx(primes.size(), 0);
        if(n == 1) return res[0];
        for(int i = 1; i < n; ++i)
        {
            res[i] = 0x7fffffff;
            for(int j = 0; j < primes.size(); ++j)
            {
                res[i] = min(res[i], primes[j] * res[idx[j]]);
            }
            for(int j = 0; j < primes.size(); ++j)
            {
                while(res[idx[j]] * primes[j] <= res[i])
                    idx[j]++;
            }
        }
        return res[n-1];
    }
};
```

## 347. Top K Frequent Elements
### 解题思路
使用`unordered_map`对输入的数字进行频率统计，然后使用`priority_queue`堆结构对之前得到的频率进行统计，最后将要求结果保存返回即可。

### 代码
```
class Solution
{
public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        vector<int> res;
        unordered_map<int, int> m;
        for(int i = 0; i < nums.size(); ++i)
        {
            m[nums[i]]++;
        }
        priority_queue<pair<int, int>> que;
        for(auto it = m.begin(); it != m.end(); ++it)
        {
            que.push(make_pair(it->second, it->first));
        }
        for(int i = 0; i < k; ++i)
        {
            res.push_back(que.top().second);
            que.pop();
        }
        return res;
    }
};

```

## 355. Design Twitter
### 解题思路
建立一个`tweet`结构，保存`tweet`的`userId`,`tweetId`和`tweetTime(发布时间)`使用`hashMap`建立`user`和`tweet`之间的联系，使用`hashMap`和`set`结构处理`user`之间的follow关系，收集`tweet`完成之后，使用`priority_queue`进行堆排序，获取最近的10个`tweet`。

### 代码
```
class Twitter
{
    struct tweet
    {
        int userId;
        int tweetId;
        int tweetTime;
        tweet(int userId_, int tweetId_) : userId(userId_), tweetId(tweetId_) {}
    };

    int userId;
    int time = 0;
    unordered_map<int, vector<tweet>> userToTweet;
    unordered_map<int, unordered_set<int>> userToFollowee;

public:
    /** Initialize your data structure here. */
    Twitter()
    {
        userId = 0;
        time++;
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId)
    {
        tweet temp = tweet(userId, tweetId);
        temp.tweetTime = time++;
        userToTweet[userId].push_back(temp);
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId)
    {
        vector<int> res;
        priority_queue<pair<int, int>> que;
        int count = 0;
        for(auto const tweet : userToTweet[userId])
        {
            que.push(make_pair(tweet.tweetTime, tweet.tweetId));
        }
        for(auto const followee : userToFollowee[userId])
        {
            for(auto const tweet : userToTweet[followee])
            {
                que.push(make_pair(tweet.tweetTime, tweet.tweetId));
            }
        }
        while(!que.empty())
        {
            res.push_back(que.top().second);
            que.pop();
            if(++count >= 10)
                break;
        }
        return res;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId)
    {
        if(followerId != followeeId)
            userToFollowee[followerId].insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId)
    {
        userToFollowee[followerId].erase(followeeId);
    }
};
```

## 373. Find K Pairs with Smallest Sums
### 解题思路
遍历所有的可能情况，然后将其组合置入一个堆结构中，最后按照要求弹出返回结果。

### 代码
```
class Solution
{
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k)
    {
        vector<pair<int, int>> res;
        priority_queue<pair<int, pair<int, int>>> que;
        for(int i = 0; i < nums1.size(); ++i)
        {
            for(int j = 0; j < nums2.size(); ++j)
            {
                que.push(make_pair(-nums1[i]-nums2[j], make_pair(nums1[i], nums2[j])));
            }
        }
        for(int i = 0; i < k && !que.empty(); ++i)
        {
            res.push_back(make_pair(que.top().second.first, que.top().second.second));
            que.pop();
        }
        return res;
    }
};
```

## 378. Kth Smallest Element in a Sorted Matrix
### 解题思路I
这道题我直接用堆排序解决了。。。

### 代码
```
class Solution
{
public:
    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        int res;
        priority_queue<int> que;
        for(int i = 0; i < matrix.size(); i++)
        {
            for(int j = 0; j < matrix.size(); ++j)
            {
                que.push(-matrix[i][j]);
            }
        }
        for(int i = 0; i < k && !que.empty(); ++i)
        {
            res = -que.top();
            que.pop();
        }
        return res;
    }
};
```

### 解题思路II
充分利用矩阵每行每列有序的性质，维护一个最小堆，从左上角开始置入堆中，如果是首行元素，则将元素右边的元素置入堆中，这样能够避免重复，同是确保所有的可能结果都在堆中。

### 代码
```
class Solution
{
    struct Node
    {
        int idx;
        int idy;
        int val;
        Node(int x, int y, int v) : idx(x), idy(y), val(v) {}
        bool operator < (const Node &ref) const { return val > ref.val; }
    };
public:
    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        int res;
        int len = matrix.size();
        priority_queue<Node> que;
        int left = 0;
        int right = 0;
        que.push(Node(left, right, matrix[left][right]));
        for(int i = 1; i < k; ++i)
        {
            left = que.top().idx;
            right = que.top().idy;
            que.pop();
            if(left == 0 && right+1 < len) que.push(Node(left, right+1, matrix[left][right+1]));
            if(left+1 < len) que.push(Node(left+1, right, matrix[left+1][right]));
        }
        return que.top().val;
    }
};
```


## 451. Sort Characters By Frequency
### 解题思路
使用unordered_map和priority_que进行hash匹配和堆排序，最后输出结果即可；

### 代码
```
class Solution
{
public:
    string frequencySort(string s)
    {
        string res;
        if(s == "") return res;
        unordered_map<char, int> m;
        priority_queue<pair<int, char>> que;
        for(int i = 0; i < s.size(); ++i)
            m[s[i]]++;
        for(auto it = m.begin(); it != m.end(); ++it)
            que.push(make_pair((*it).second, (*it).first));
        while(!que.empty())
        {
            for(int i = 0; i < que.top().first; ++i)
            {
                res += que.top().second;
            }
            que.pop();
        }
        return res;
    }
};
```


  [1]: https://leetcode.com/problems/ugly-number-ii/
  [2]: https://leetcode.com/problems/find-median-from-data-stream/
  [3]: https://leetcode.com/problems/super-ugly-number/
  [4]: https://leetcode.com/problems/top-k-frequent-elements/
  [5]: https://leetcode.com/problems/design-twitter/
  [6]: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
  [7]: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
  [8]: https://leetcode.com/problems/sort-characters-by-frequency/
