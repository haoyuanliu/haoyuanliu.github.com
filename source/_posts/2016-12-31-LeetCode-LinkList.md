---
title: LeetCode LinkList
date: 2016-12-31 19:43:29
categories: LeetCode
tags: [LeetCode, LinkList]
---

本文包含如下题目：
[2. Add Two Numbers][1]
[19. Remove Nth Node From End of List][2]
[21. Merge Two Sorted Lists][3]
[23. Merge k Sorted Lists][4]
[24. Swap Nodes in Pairs][5]
[25. Reverse Nodes in k-Group][6]
[61. Rotate List][7]
[82. Remove Duplicates from Sorted List II][8]
[83. Remove Duplicates from Sorted List][9]
[86. Partition List][10]
[92. Reverse Linked List II][11]
[109. Convert Sorted List to Binary Search Tree][12]
[138. Copy List with Random Pointer][13]
[141. Linked List Cycle][14]
[142. Linked List Cycle II][15]
[143. Reorder List][16]
[160. Intersection of Two Linked Lists][17]
[203. Remove Linked List Elements][18]
[206. Reverse Linked List][19]
[234. Palindrome Linked List][20]
[237. Delete Node in a Linked List][21]
[328. Odd Even Linked List][22]
[445. Add Two Numbers II][23]


<!--more-->

## 2. Add Two Numbers
### 解题思路
> * 直接新建一个链表，然后进行加法运算即可；

### 代码
```
class Solution 
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode *head = new ListNode(-1);
        ListNode *p = head;
        int carry = 0;
        int a, b, c;
        while(l1 || l2)
        {
            a = b = c = 0;
            if(l1)
            {
                a = l1->val;
                l1 = l1->next;
            }
            if(l2)
            {
                b = l2->val;
                l2 = l2->next;
            }
            c = a + b + carry;
            p->next = new ListNode(c % 10);
            carry = c / 10;
            p = p->next;
        }
        if(carry == 1)
        {
            p->next = new ListNode(1);
        }
        return head->next;
    }
};

```

## 19. Remove Nth Node From End of List
### 解题思路
> * 使用两个指针a, b，a先定位到从左边开始第n个，然后b在链表头部和a同时进行遍历，a到尾部的时候b也就正好取到了所求结果；

### 代码
```
class Solution
{
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n)
        {
            ListNode *root = new ListNode(0);
            root->next = head;
            ListNode *p, *c;
            p = c = root;
            for(int i = 0; i < n+1; ++i)
                c = c->next;
            while(c)
            {
                p = p->next;
                c = c->next;
            }
            p->next = p->next->next;
            return root->next;
        }
};
```

## 21. Merge Two Sorted Lists
### 解题思路
> * 归并排序的merge算法；

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

## 23. Merge k Sorted Lists
### 解题思路
> *  二分法进行排序；

### 代码
```
class Solution
{
    public:
        ListNode* mergeKLists(vector<ListNode*>& lists)
        {
            int len = lists.size();
            if(len == 0)
                return NULL;
            else if(len == 1)
                return lists[0];
            else if(len == 2)
                return mergeTwoLists(lists[0], lists[1]);
            vector<ListNode*> left(lists.begin(), lists.begin() + len/2);
            vector<ListNode*> right(lists.begin()+len/2, lists.end());
            return mergeTwoLists(mergeKLists(left), mergeKLists(right));
        }

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

## 24. Swap Nodes in Pairs
### 解题思路
> * 这个考的链表的基本操作吧；

### 代码
```
class Solution
{
    public:
        ListNode* swapPairs(ListNode* head)
        {
            if(!head && !head->next)
                return head;
            ListNode* root = new ListNode(0);
            root->next = head;
            ListNode *p, *c;
            p = root;
            c = root->next->next;
            while(c)
            {
                p->next->next = c->next;
                c->next = p->next;
                p->next = c;
                p = p->next->next;
                if(p->next)
                    c = p->next->next;
                else
                    break;
            }
            return root->next;
        }
};

```

## 25. Reverse Nodes in k-Group
### 解题思路
> * 首先维持一个len数值，通过len与k的比较判断是否需要reverse；
> * reverse就和上一题一样了，基本操作；

### 代码
```
class Solution
{
    public:
        ListNode* reverseKGroup(ListNode* head, int k)
        {
            int len = getLen(head);
            if(len < k || k == 1)
                return head;
            ListNode *root = new ListNode(-1);
            ListNode *p = root;
            ListNode *p1 = head;
            ListNode *p2 = head;
            while(len >= k)
            {
                for(int i = 0; i < k; ++i)
                {
                    p2 = p1->next;
                    p1->next = p->next;
                    p->next = p1;
                    p1 = p2;
                }
                while(p->next)
                    p = p->next;
                len -= k;
                if(len < k)
                {
                    p->next = p1;
                    return root->next;
                }
            }
            return root->next;
        }
        int getLen(ListNode *head)
        {
            ListNode *p = head;
            int count = 0;
            while(p)
            {
                count++;
                p = p->next;
            }
            return count;
        }
};
```

## 61. Rotate List
### 解题思路
> * 构建循环链表，然后rotate再断开，这里注意使用%求余进行计算；

### 代码
```
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

## 82. Remove Duplicates from Sorted List II
### 解题思路
> * 第一次检测得到的节点`cur`可以保证其与前置节点不重复，此时将其设为待选节点置为`pre->next = cur`，再次循环，如果位置仍不改变`pre->next == cur`，则其后也没有重复节点，执行`pre = pre->next`即可；

### 代码
```
class Solution
{
    public:
        ListNode *deleteDuplicates(ListNode* head)
        {
            if(head == NULL)
                return head;
            ListNode *root = new ListNode((1<<31));
            root->next = head;
            ListNode *cur = head;
            ListNode *pre = root;
            while(cur)
            {
                while(cur->next && cur->val == cur->next->val)
                    cur = cur->next;
                if(pre->next == cur)
                    pre = pre->next;
                else
                    pre->next = cur->next;
                cur = cur->next;
            }
            return root->next;
        }
};
```

## 83. Remove Duplicates from Sorted List
### 解题思路
> * 简单题

### 代码
```
class Solution
{
    public:
        ListNode *deleteDuplicates(ListNode *head)
        {
            if(head == NULL)
                return head;
            ListNode * root = new ListNode(0);
            root->next = head;
            ListNode *pre = root;
            ListNode *cur = head;
            while(cur)
            {
                while(cur->next && cur->next->val == cur->val)
                    cur = cur->next;
                pre->next = cur;
                pre = pre->next;
                cur = cur->next;
            }
            return root->next;
        }
};
```

## 86. Partition List
### 解题思路
> * 建立左右两个链表，将小于x的数全部放入到左链表中，其他的都放到右链表中，最后连接起来就好；

### 代码
```
class Solution
{
    public:
        ListNode* partition(ListNode* head, int x)
        {
            if(head == NULL || head->next == NULL)
                return head;
            ListNode *left = new ListNode(0);
            ListNode *right = new ListNode(0);
            ListNode *l = left;
            ListNode *r = right;
            ListNode *p = head;
            while(p)
            {
                if(p->val < x)
                {
                    l->next = p;
                    l = l->next;
                }
                else
                {
                    r->next = p;
                    r = r->next;
                }
                p = p->next;
            }
            r->next = NULL;
            l->next = right->next;
            return left->next;
        }
};
```

## 92. Reverse Linked List II
### 解题思路
> * 这里其实是应用了链表的逆序算法；

### 代码
```
class Solution
{
    public:
        ListNode* reverseBetween(ListNode* head, int m, int n)
        {
            if(head == NULL || m == n)
                return head;
            ListNode *root = new ListNode(0);
            root->next = head;
            ListNode *pre, *cur, *left;
            left = root;
            for(int i = 1; i < m; ++i)
                left = left->next;
            pre = left->next;
            cur = pre->next;
            for(int i = 0; i < n - m; ++i)
            {
                pre->next = cur->next;
                cur->next = left->next;
                left->next = cur;
                cur = pre->next;
            }
            return root->next;
        }
};
```

## 109. Convert Sorted List to Binary Search Tree
### 解题思路
> * 由于链表是有序的，需要先从中间开始插入，从而来保证树结构的平衡；
> * 这里用到了slow和fast两个指针来快速求取链表中点；

### 代码
```
class Solution
{
    public:
        TreeNode *sortedListToBST(ListNode *head)
        {
            if(head == NULL)
                return NULL;
            return toTree(head, NULL);
        }
        TreeNode *toTree(ListNode *head, ListNode *tail)
        {
            if(head == tail)
                return NULL;
            ListNode *slow = head;
            ListNode *fast = head;
            while(fast != tail && fast->next != tail)
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            TreeNode *res = new TreeNode(slow->val);
            res->left = toTree(head, slow);
            res->right = toTree(slow->next, tail);
            return res;
        }
};
```

## 138. Copy List with Random Pointer
### 解题思路
> * 首先在每个链表节点后面复制一个该节点，加入到链表中；
> * 此时复制节点的random取值就变成：`cp->random = p->random->next`；
> * 然后再将两个链表区分开来就可以了；

### 代码
```
class Solution 
{
public:
    RandomListNode *copyRandomList(RandomListNode *head) 
    {
        if(head == NULL)
            return NULL;
        RandomListNode *p = head;
        RandomListNode *cp;
        RandomListNode *res;
        while(p)
        {
            cp = new RandomListNode(p->label);
            cp->next = p->next;
            p->next = cp;
            p = cp->next;
        }
        p = head;
        while(p)
        {
            cp = p->next;
            if(p->random)
                cp->random = p->random->next;
            p = cp->next;
        }
        res = head->next;
        p = head;
        while(p)
        {
            cp = p->next;
            p->next = cp->next;
            p = p->next;
            if(p)
                cp->next = p->next;
        }
        return res;
    }
};
```

## 141. Linked List Cycle
### 解题思路
> * 简单题，使用快慢指针解决，如果有循环则快慢指针会相遇；

### 代码
```
class Solution
{
    public:
        bool hasCycle(ListNode *head)
        {
            ListNode *slow = head;
            ListNode *fast = head;
            while(slow && fast)
            {
                slow = slow->next;
                if(fast->next)
                    fast = fast->next->next;
                else
                    return false;
                if(slow == fast)
                    return true;
            }
            return false;
        }
};
```

## 142. Linked List Cycle II
### 解题思路
> * 使用快慢指针，第一次相遇时结束；快指针比慢指针多走了一倍的距离；
> * 快指针多走了一个循环，通过画图分析，从相遇节点到`cycle begin`的距离正好等于从起始节点到`cycle begin`的距离；


### 代码
```
class Solution 
{
public:
    ListNode *detectCycle(ListNode *head) 
    {
        if(head == NULL || head->next == NULL)
        	return NULL;
        ListNode *slow = head;
        ListNode *fast = head;
        bool isCycle = false;
        while(slow && fast)
        {
        	slow = slow->next;
        	if(fast->next == NULL)
        		return NULL;
        	fast = fast->next->next;
        	if(slow == fast)
        	{
        		isCycle = true;
        		break;
        	}
        }
        if(!isCycle)
        	return NULL;
        slow = head;
        while(slow != fast)
        {
        	slow = slow->next;
        	fast = fast->next;
        }
        return slow;
    }
};
```

## 143. Reorder List
### 解题思路
> * 使用快慢指针将链表从中间分成两部分，将后半部分进行逆序处理最后merge合并即可；

### 代码
```
class Solution 
{
public:
    void reorderList(ListNode* head) 
    {
    	if(head == NULL || head->next == NULL)
    		return;
    	ListNode *p1 = head;
    	ListNode *p2 = head->next;
    	while(p2 && p2->next)
    	{
    		p1 = p1->next;
    		p2 = p2->next->next;
    	}

    	ListNode *head2 = p1->next;
    	p1->next = NULL;

    	p2 = head2->next;
    	head2->next = NULL;
    	while(p2)
    	{
    		p1 = p2->next;
    		p2->next = head2;
    		head2 = p2;
    		p2 = p1;
    	}

    	for(p1 = head, p2 = head2; p1; )
    	{
    		auto temp = p1->next;
    		p1 = p1->next = p2;
    		p2 = temp;
    	}
    }
};
```

## 160. Intersection of Two Linked Lists
### 解题思路
> * 如果两个链表有重复的部分，则`A+B`和`B+A`对齐就可以直接找到重复的部分；

### 代码
```
class Solution 
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        ListNode *p = headA;
        ListNode *q = headB;
        if(p == NULL || p == NULL)
            return NULL;
        while(p && q && p != q)
        {
        	p = p->next;
        	q = q->next;
            if(p == q)
                return p;  
            if(p == NULL)
                p = headB;
            if(q == NULL)
                q = headA;
        }
        return p;
    }
};
```

## 203. Remove Linked List Elements
### 解题思路
> *　简单题，不多说了；

### 代码
```
class Solution 
{
public:
    ListNode* removeElements(ListNode* head, int val) 
    {
        ListNode *root = new ListNode(0);
        root->next = head;
        ListNode *cur = root;
        while(cur->next)
        {
        	if(cur->next->val == val)
            {
                cur->next = cur->next->next;
            }
            else
                cur = cur->next;
        }
        return root->next;
    }
};
```

## 206. Reverse Linked List
### 解题思路
> * 链表的逆序处理；

### 代码
```
class Solution {
public:
    ListNode* reverseList(ListNode* head) 
    {
        if(head == NULL || head->next == NULL)
        	return head;
        ListNode *pre = head;
        ListNode *cur = head->next;
        ListNode *temp;
        pre->next = NULL;
        while(cur->next)
        {
        	temp = cur->next;
        	cur->next = pre;
        	pre = cur;
        	cur = temp;
        }
        cur->next = pre;
        return cur;
    }
};
```
## 234. Palindrome Linked List
### 解题思路
> * 使用快慢指针将链表分成两个部分，将后半部分进行逆序处理然后进行比较是否为回文；    

### 代码
```
class Solution 
{
public:
    bool isPalindrome(ListNode* head) 
    {
        if(head == NULL || head->next == NULL)
            return true;
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        ListNode *pre = slow->next;
        ListNode *cur = pre->next;
        slow->next = NULL;
        pre->next = NULL;
        
        while(cur)
        {
            ListNode *temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        ListNode *p = head;
        
        while(pre && p)
        {
            if(pre->val != p->val)
                return false;
            pre = pre->next;
            p = p->next;
        }
        return true;
    }
};
```

## 237. Delete Node in a Linked List
### 解题思路
> * 这个题，搞明白题意就可以，将要删除的节点数据替换成下一节点的数据；

### 代码
```
class Solution 
{
public:
    void deleteNode(ListNode* node) 
    {
        *node = *node->next;
    }
};
```

## 328. Odd Even Linked List
### 解题思路
> * 两个两个向后扫描即可，得到奇偶两条链表链接到一块；

### 代码
```
class Solution 
{
public:
    ListNode* oddEvenList(ListNode* head) 
    {
        if(head == NULL || head->next == NULL)
        	return head;
        ListNode *odd =  head;
        ListNode *even = head->next;
        ListNode *evenStart = even;
        while(even && even->next)
        {
        	odd->next = odd->next->next;
        	even->next = even->next->next;
        	odd = odd->next;
        	even = even->next;
        }
        odd->next = evenStart;
        return head;
    }
};
```

## 445. Add Two Numbers II
### 解题思路
> * 利用`l1+l2`和`l2+l1`实现对齐，利用两个bool标记何时数值有效；
> * 将结果保存到一个`vector`中，最后求取进位后构建链表；

### 代码
```
class Solution 
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
    	bool f1 = false;
    	bool f2 = false;
    	vector<int> sum;
        ListNode *res = new ListNode(0);
        ListNode *p = l1;
        ListNode *q = l2;
        while(p && q)
        {
        	if(f1 || f2)
        	{
        		int temp = (f1 ? p->val : 0) + (f2 ? q->val : 0);
        		sum.push_back(temp);
        	}
        	p = p->next;
        	q = q->next;
        	if(f1 && f2 && p == q)
        		break;
        	if(p == NULL){ p = l2; f1 = true; }
        	if(q == NULL){ q = l1; f2 = true; }
        }
        
        int carry = 0;
        for(int i = sum.size()-1; i >= 0; --i)
        {
        	sum[i] = sum[i] + carry;
        	carry = sum[i] / 10;
        	sum[i] %= 10;
        }
        if(carry)
        	sum.insert(sum.begin(), carry);

        ListNode *cur = res;
        for(int i = 0; i < sum.size(); ++i)
        {
        	cur->next = new ListNode(sum[i]);
        	cur = cur->next;
        }
        return res->next;
    }
};
```



  [1]: https://leetcode.com/problems/add-two-numbers/
  [2]: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
  [3]: https://leetcode.com/problems/merge-two-sorted-lists/
  [4]: https://leetcode.com/problems/merge-k-sorted-lists/
  [5]: https://leetcode.com/problems/swap-nodes-in-pairs/
  [6]: https://leetcode.com/problems/reverse-nodes-in-k-group/
  [7]: https://leetcode.com/problems/rotate-list/
  [8]: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
  [9]: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
  [10]: https://leetcode.com/problems/partition-list/
  [11]: https://leetcode.com/problems/reverse-linked-list-ii/
  [12]: https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
  [13]: https://leetcode.com/problems/copy-list-with-random-pointer/
  [14]: https://leetcode.com/problems/linked-list-cycle/
  [15]: https://leetcode.com/problems/linked-list-cycle-ii/
  [16]: https://leetcode.com/problems/reorder-list/
  [17]: https://leetcode.com/problems/intersection-of-two-linked-lists/
  [18]: https://leetcode.com/problems/remove-linked-list-elements/
  [19]: https://leetcode.com/problems/reverse-linked-list/
  [20]: https://leetcode.com/problems/palindrome-linked-list/
  [21]: https://leetcode.com/problems/delete-node-in-a-linked-list/
  [22]: https://leetcode.com/problems/odd-even-linked-list/
  [23]: https://leetcode.com/problems/add-two-numbers-ii/