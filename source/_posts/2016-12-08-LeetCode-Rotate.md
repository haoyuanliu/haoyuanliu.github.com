---
title: LeetCode Rotate
date: 2016-12-08 20:32:13
categories: LeetCode
tags: [Leetcode]
---

本文包含如下题目：
[61. Rotate List][1]
[189. Rotate Array][2]

<!--more-->

## 61. Rotate List
### 解题思路
本题目是链表的翻转，先求链表长度，然后构建循环链表，最后找到所求头节点断开循环返回即可。
### 代码
```c++
class Solution
{
    public:
        ListNode* rotateRight(ListNode *head, int k)
        {
            if(head == NULL)
                return NULL;
            ListNode *res;
            ListNode *p = head;
            int len = 1;
            while(p->next)
            {
                len++;
                p = p->next;
            }
            
            k %= len;
            if(k == 0)
                return head;
            
            p->next = head;
            while(p)
            {
                p = p->next;
                len--;
                if(len == k)
                {
                    res = p->next;
                    p->next = NULL;
                    break;
                }
            }
            return res;
        }
};
```

## 189. Rotate Array
### 解题思路
数组的翻转，类似于链表的翻转，c++的vector容器有很多直接可以调用的函数，可以参考官方的[讲解][3]。

### 代码

#### Solution I
```
class Solution
{
    public:
        void rotate(vector<int> &nums, int k)
        {
            int len = nums.size();
            k %= len;
            for(int i = 0; i < k; ++i)
            {
                nums.insert(nums.begin(), nums[len-1]);
                nums.pop_back();
            }
        }
};
```

#### Solution II

```
class Solution
{
    public:
        void rotate(vector<int> &nums, int k)
        {
            int len = nums.size();
            k %= len;
            reverse(nums.begin(), nums.end());
            reverse(nums.begin(), nums.begin()+k);
            reverse(nums.begin()+k, nums.end());
        }
};
```


  [1]: https://leetcode.com/problems/rotate-list/
  [2]: https://leetcode.com/problems/rotate-array/
  [3]: https://leetcode.com/articles/rotate-array/
