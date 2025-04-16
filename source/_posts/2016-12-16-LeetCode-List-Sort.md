---
title: LeetCode List Sort
categories: LeetCode
tags:
  - LeetCode
  - Sort
  - LinkList
abbrlink: 47956
date: 2016-12-16 22:02:22
---


本文包含如下题目：
[21. Merge Two Sorted Lists][1]
[75. Sort Colors][2]
[147. Insertion Sort List][3]
[148. Sort List][4]
[215. Kth Largest Element in an Array][5]
[324. Wiggle Sort II][6]

<!--more-->
## 21. Merge Two Sorted Lists
### 解题思路
> * 简单题，不多说了；

### 代码
```
class Solution
{
    public:
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
        {
            ListNode* head = new ListNode(0);
            ListNode* p = head;
            while(l1 && l2)
            {
                if(l1->val > l2->val)
                {
                    p->next = new ListNode(l2->val);
                    p = p->next;
                    l2 = l2->next;
                }
                else
                {
                    p->next = new ListNode(l1->val);
                    p = p->next;
                    l1 = l1->next;
                }
            }
            if(l1)
                p->next = l1;
            if(l2)
                p->next = l2;

            return head->next;
        }
};
```

## 75. Sort Colors
### 解题思路
> * 把0一次丢到数组左边，2丢到数组右边，1的话保持不动；
 
### 代码
```
class Solution
{
    public:
        void sortColors(vector<int> &nums)
        {
            int len = nums.size();
            int left = 0;
            int right = len - 1;
            for(int i = 0; i < len; ++i)
            {
                if(i > right)
                    break;
                if(nums[i] == 1)
                    continue;
                else if(nums[i] == 0)
                {
                    swap(nums[i], nums[left]);
                    left++;
                }
                else
                {
                    swap(nums[i], nums[right]);
                    right--;
                    i--;
                }
            }
        }
};
```

## 147. Insertion Sort List
### 解题思路
> * 需要新建一个链表头保存已排序的节点；

### 代码
```
class Solution
{
    public:
        ListNode *insertionSortList(ListNode *head)
        {
            if(head == NULL)
                return head;
            ListNode *root = new ListNode(0);
            ListNode *pre = root;
            ListNode *cur = head;
            ListNode *next = NULL;
            while(cur)
            {
                next = cur->next;
                while(pre->next && pre->next->val < cur->val)
                    pre = pre->next;
                cur->next = pre->next;
                pre->next = cur;

                cur = next;
                pre = root;
            }
            return root->next;
        }
};
```

## 148. Sort List
### 解题思路
> * 符合要求的排序算法有快排、堆排和归并，归并更适合用在链表中；
> * 使用一个单步遍历和一个两步遍历快速找到链表的中间结点；
> * 使用归并排序，最后通过merge函数将链表链接起来。

### 代码
```
class Solution
{
    public:
        ListNode *sortList(ListNode *head)
        {
            if(!head || !head->next)
                return head;
            ListNode *p = head;
            ListNode *p2 = head;
            while(p && p2->next->next)
            {
                p = p->next;
                p2 = p2->next->next;
                if(p2->next == NULL)
                    break;
            }
            ListNode *head2 = p->next;
            p->next = NULL;
            return merge(sortList(head), sortList(head2));
        }

        ListNode *merge(ListNode *a, ListNode *b)
        {
            ListNode *root = new ListNode(1);
            ListNode *p = root;
            while(a && b)
            {
                if(a->val > b->val)
                {
                    p->next = b;
                    b = b->next;
                    p = p->next;
                    p->next = NULL;
                }
                else
                {
                    p->next = a;
                    a = a->next;
                    p = p->next;
                    p->next = NULL;
                }
            }
            if(a)
                p->next = a;
            if(b)
                p->next = b;
            return root->next;
        }
};
```

## 215. Kth Largest Element in an Array
### 解题思路
> * 各种排序算法的讨论比较才是这一题的关键；

### 代码
```
class Solution
{
    public:
        int findKthLargest(vector<int> &nums, int k)
        {
            sort(nums.begin(), nums.end());
            return nums[nums.size() - k];
        }
};
```


## 324. Wiggle Sort II
### 解题思路
> * 首先进行排序，然后从中间位置分为两个部分，都按照降序进行重组；

### 代码
```
class Solution
{
    public:
        void wiggleSort(vector<int> &nums)
        {
            int len = nums.size();
            vector<int> temp(len, 0);
            sort(nums.begin(), nums.end());
            int mid = (len + 1) >> 1;
            int right = len;
            for(int i = 0; i < len; ++i)
                temp[i] = (i&1) ? nums[--right] : nums[--mid];
            for(int i = 0; i < len; ++i)
                nums[i] = temp[i];
        }
};
```



  [1]: https://leetcode.com/problems/merge-two-sorted-lists/
  [2]: https://leetcode.com/problems/sort-colors/
  [3]: https://leetcode.com/problems/insertion-sort-list/
  [4]: https://leetcode.com/problems/sort-liste.com/problems/sort-colors/
  [5]: https://leetcode.com/problems/kth-largest-element-in-an-arraye.com/problems/sort-colors/
  [6]: https://leetcode.com/problems/wiggle-sort-ii/