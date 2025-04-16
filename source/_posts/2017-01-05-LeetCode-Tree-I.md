---
title: LeetCode Tree I
categories: LeetCode
tags:
  - LeetCode
  - Tree
abbrlink: 25571
date: 2017-01-05 19:01:56
---

本文包含的题目有：

[94. Binary Tree Inorder Traversal][1]
[95. Unique Binary Search Trees II][2]
[96. Unique Binary Search Trees][3]
[98. Validate Binary Search Tree][4]
[99. Recover Binary Search Tree][5]
[100. Same Tree][6]
[101. Symmetric Tree][7]
[102. Binary Tree Level Order Traversal][8]
[103. Binary Tree Zigzag Level Order Traversal][9]
[104. Maximum Depth of Binary Tree][10]
[105. Construct Binary Tree from Preorder and Inorder Traversal][11]
[106. Construct Binary Tree from Inorder and Postorder Traversal][12]
[107. Binary Tree Level Order Traversal II][13]
[108. Convert Sorted Array to Binary Search Tree][14]
[110. Balanced Binary Tree][15]
[111. Minimum Depth of Binary Tree][16]
[112. Path Sum][17]
[113. Path Sum II][18]
[437. Path Sum III][19]


<!--more-->

## 94. Binary Tree Inorder Traversal
### 解题思路
> * 二叉树的中序遍历；

### 代码
```
class Solution
{
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> res;
        midOrder(res, root);
        return res;
    }

    void midOrder(vector<int> &res, TreeNode *root)
    {
        if(root)
        {
            midOrder(res, root->left);
            res.push_back(root->val);
            midOrder(res, root->right);
        }
    }
};
```
## 95. Unique Binary Search Trees II
### 解题思路
> * 使用分治的方法解决；

### 代码
```
class Solution
{
public:
    vector<TreeNode*> generateTrees(int n)
    {
        vector<TreeNode*> res;
        if(n == 0)
            return res;
        return getTree(1, n);
    }
    vector<TreeNode*> getTree(int start, int end)
    {
        vector<TreeNode*> res;
        if(start > end)
        {
            res.push_back(NULL);
            return res;
        }
        if(start == end)
        {
            res.push_back(new TreeNode(start));
            return res;
        }
        for(int i = start; i <= end; ++i)
        {
            vector<TreeNode*> left = getTree(start, i-1);
            vector<TreeNode*> right = getTree(i+1, end);
            for(const auto l : left)
            {
                for(const auto r : right)
                {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
```

## 96. Unique Binary Search Trees
### 解题思路I
> * 使用DP动态规划，每添加一个新节点，首先保持已有的树结构不变，则新节点只有两个位置可以放置，从而有：`res[i] += res[i-1] * 2`;
> * 如果将已有的树结构拆开，则只能拆成两个部分，前一部分的右子节点为新节点，新节点的左子节点为右半部分，从而有：`res[i] += res[j] * res[i-j-1]`；

### 代码
```
class Solution 
{
public:
    int numTrees(int n) 
    {
        vector<int> res(n+1, 0);
        res[0] = 1;
        res[1] = 1;
        res[2] = 2;
        for(int i = 3; i <= n; ++i)
        {
        	res[i] += res[i-1] * 2;
        	for(int j = 1; j < i-1; ++j)
        	{
        		res[i] += res[j] * res[i-j-1];
        	}
        }
        return res[n];
    }
};
```
### 解题思路II
> * 继续延续上述DP的思路，将`res[i-1] * 2`转变为`res[0] * res[i-1]` + `res[i-1] * res[0]`，然后更新原来的代码，更加简洁；

### 代码
```
class Solution 
{
public:
    int numTrees(int n) 
    {
        vector<int> res(n+1, 0);
        res[0] = 1;
        res[1] = 1;
        for(int i = 2; i <= n; ++i)
        {
        	for(int j = 0; j < i; ++j)
        	{
        		res[i] += res[j] * res[i-j-1];
        	}
        }
        return res[n];
    }
};
```

## 98. Validate Binary Search Tree
### 解题思路
> * 仍然是使用中序遍历，维持一个pre变量，确保每一个`cur > pre`即可；

### 代码
```
class Solution 
{
public:
    bool isValidBST(TreeNode* root) 
    {
    	TreeNode* pre = NULL;
    	return midOrder(root, pre);
    }
    bool midOrder(TreeNode* root, TreeNode* &pre)
    {
    	if(root)
    	{
    		if(!midOrder(root->left, pre))
    			return false;
    		if(pre && root->val <= pre->val) 
    			return false; 
    		pre = root;
    		if(!midOrder(root->right, pre))
    			return false;
    	}
    	return true;
    }
};
```
## 99. Recover Binary Search Tree
### 解题思路
> * 仍然是中序遍历，遍历一遍，找出乱序的两个节点即可；

### 代码
```
class Solution 
{
public:
	TreeNode* left = NULL;
    TreeNode* right = NULL;
    TreeNode* pre = new TreeNode((1<<31));
    void recoverTree(TreeNode* root) 
    {
    	
        midOrder(root);
        swap(left->val, right->val);
    }

    void midOrder(TreeNode* root)
    {
    	if(root)
    	{
    		midOrder(root->left);
    		if(!left && pre->val >= root->val)
    			left = pre;
    		if(left && pre->val >= root->val)
    			right = root;
    		pre = root;
    		midOrder(root->right);
    	}
    }
};
```

## 100. Same Tree
### 解题思路
> * 这道题就迭代去比较就可以了， 注意两个都是`NULL`的情况；

### 代码
```
class Solution 
{
public:
    bool isSameTree(TreeNode* p, TreeNode* q) 
    {
    	if(p == q)
    		return true;
		if(p && q && p->val == q->val)
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		else
			return false;        
    }
};
```

## 101. Symmetric Tree
### 解题思路
> * 按照对称的位置去比较；

### 代码
```
class Solution 
{
public:
    bool isSymmetric(TreeNode* root)
    {
    	if(root == NULL)
    		return true;
        return isTheSame(root->left, root->right);
    }
	bool isTheSame(TreeNode* left, TreeNode* right)
	{
		if(left == NULL || right == NULL)
			return left == right;
		if(left->val != right->val)
			return false;
		return isTheSame(left->left, right->right) && isTheSame(left->right, right->left);
	}
};
```

## 102. Binary Tree Level Order Traversal
### 解题思路
> * 使用一个`queue`进行广度优先搜索；

### 代码
```
class Solution 
{
public:
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        vector<vector<int>> res;
        vector<int> temp;
        if(root == NULL)
        	return res;
        queue<TreeNode*> que;
        que.push(root);

        while(!que.empty())
        {
        	temp.clear();
        	int len = que.size();
        	for(int i = 0; i < len; ++i)
        	{
        		temp.push_back(que.front()->val);
        		if(que.front()->left)
        			que.push(que.front()->left);
        		if(que.front()->right)
        			que.push(que.front()->right);
        		que.pop();
        	}
        	res.push_back(temp);
        }
        return res;
    }
};
```

## 103. Binary Tree Zigzag Level Order Traversal
### 解题思路
> * 仍然按照上述思路进行，使用一个`queue`保存每一层的数据，这里注意在偶数层进行翻转即可；

### 代码
```
class Solution 
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
    {
		vector<vector<int>> res;
		vector<int> temp;
		queue<TreeNode*> que;
		if(root == NULL)
			return res;
		int count = 0;
		que.push(root);
		while(!que.empty())
		{
			temp.clear();
			int len = que.size();
			for(int i = 0; i < len; ++i)
			{
				if(que.front()->left)
					que.push(que.front()->left);
				if(que.front()->right)
					que.push(que.front()->right);
				temp.push_back(que.front()->val);
				que.pop();
			}
			if((count++)&1)
				reverse(temp.begin(), temp.end());
			res.push_back(temp);
		}
		return res;        
    }
};
```

## 104. Maximum Depth of Binary Tree
### 解题思路
> * 使用一个递归来解决；

### 代码
```
class Solution 
{
public:
    int maxDepth(TreeNode* root) 
    {
        if(root)
    		return 1 + max(maxDepth(root->left), maxDepth(root->right));
    	return 0;
    }
};
```

## 105. Construct Binary Tree from Preorder and Inorder Traversal
### 解题思路
> * 由中序遍历和先序遍历来构建树结构；

### 代码
```
class Solution 
{
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {

     	  TreeNode* root = solve(preorder, inorder, 0, preorder.size(), 0, preorder.size());
     	  return root;
    }
    TreeNode* solve(vector<int> &preorder, vector<int> &inorder, int start, int end, int s, int e)
    {
    	if(end == start || end < start)
    		return NULL;
    	if(end - start == 1)
    	{
    		return new TreeNode(preorder[start]);
    	}
    	else
    	{
    		TreeNode* res = new TreeNode(preorder[start]);
    		int mid;
    		for(int i = s; i < e; ++i)
    		{
    			if(inorder[i] == preorder[start])
    			{
    				mid = i;
    				break;
    			}
    		}
    		res->left = solve(preorder, inorder, start+1, start+mid-s+1, s, mid);
    		res->right = solve(preorder, inorder, start+mid-s+1, end, mid+1, e);
    		return res;
    	}
    	return NULL;
    }
};
```

## 106. Construct Binary Tree from Inorder and Postorder Traversal
### 解题思路
> * 中序遍历和后序遍历构建树结构，使用`unordered_map`进行辅助存储；

### 代码
```
class Solution 
{
public:
    unordered_map<int, int> m;
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
    {
        for(int i = 0; i < inorder.size(); ++i)
        	m[inorder[i]] = i;
        return solve(inorder, postorder, 0, inorder.size(), 0, inorder.size());
    }
    TreeNode *solve(vector<int> &inorder, vector<int>& postorder, int s1, int e1, int s2, int e2)
    {
    	if(e1 == s1 || e1 < s1)
    		return NULL;
    	if(e1 - s1 == 1)
    		return new TreeNode(inorder[s1]);
    	int mid = m[postorder[e2-1]];
    	TreeNode* root = new TreeNode(postorder[e2-1]);
    	root->left = solve(inorder, postorder, s1, mid, s2, s2+mid-s1);
    	root->right = solve(inorder, postorder, mid+1, e1, s2+mid-s1, e2-1);
    	return root;
    }
};
```

## 107. Binary Tree Level Order Traversal II
### 解题思路
> * 跟之前的题目一样，最后进行一下翻转就可以了；

### 代码
```
class Solution 
{
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) 
    {
        vector<vector<int>> res;
        vector<int> temp;
        if(root == NULL)
        	return res;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty())
        {
        	temp.clear();
        	int len = que.size();
        	for(int i = 0; i < len; ++i)
        	{
        		if(que.front()->left)
        			que.push(que.front()->left);
        		if(que.front()->right)
        			que.push(que.front()->right);
        		temp.push_back(que.front()->val);
        		que.pop();
        	}
        	res.push_back(temp);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

## 108. Convert Sorted Array to Binary Search Tree
### 解题思路
 >* 使用分治的思想去构建，每次首先构建中间节点即可；

### 代码
```
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) 
    {
        return solve(nums, 0, nums.size());
    }
    TreeNode* solve(vector<int> &nums, int start, int end)
    {
    	if(start == end || start > end)
    		return NULL;
    	if(end - start == 1)
    		return new TreeNode(nums[start]);
    	int mid = (start + end) / 2;
    	TreeNode* root = new TreeNode(nums[mid]);
    	root->left = solve(nums, start, mid);
    	root->right = solve(nums, mid+1, end);
    	return root;
    }
};
```

## 110. Balanced Binary Tree
### 解题思路I
> * 遍历每一个节点，检查是否平衡；

### 代码
```
class Solution 
{
public:
    bool isBalanced(TreeNode* root) 
    {
        if(root == NULL)
        	return true;
        if(abs(getHeight(root->left) - getHeight(root->right)) > 1)
        	return false;
        else
        	return isBalanced(root->left) &&  isBalanced(root->right);
    }
    int getHeight(TreeNode* root)
    {
    	if(root == NULL)
    		return 0;
    	return 1 + max(getHeight(root->left), getHeight(root->right));
    }
};
```

### 解题思路II
> * 使用DFS进行深度搜索，每次搜索返回树的高度，如果平衡就返回实际高度值，否则返回`-1`，最后进行判断即可；

### 代码
```
class Solution 
{
public:
    bool isBalanced(TreeNode* root) 
    {
    	return getHeight(root) != -1;
    }
    int getHeight(TreeNode* root)
    {
    	if(root == NULL)
    		return 0;
    	int left = getHeight(root->left);
    	if(left == -1) return -1;
    	int right = getHeight(root->right);
    	if(right == -1) return -1;

    	if(abs(left - right) > 1) return -1;

    	return max(left, right) + 1;
    }
};
```

## 111. Minimum Depth of Binary Tree
### 解题思路
> * 简单题，但是有点小麻烦，弄清楚边界问题，只有`!root->left && !root->right`才可以结束遍历，有一个子节点不为`NULL`就需要继续计算，两个均不为`NULL`则取较小的一个；

### 代码
```
class Solution 
{
public:
    int minDepth(TreeNode* root) 
    {
        if(root == NULL)
    	    return 0;
    	if(!root->left && !root->right)
    		return 1;
    	else if(root->left && !root->right)
    	    return 1 + minDepth(root->left);
    	else if(!root->left && root->right)
    	    return 1 + minDepth(root->right);
    	return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};
```

## 112. Path Sum
### 解题思路
> * 遍历每一条路径，检查是否有符合要求的结果；
> * 注意这里需要判断左右子树是不是为`NULL`，即当前节点是不是叶子节点，然后分情况进行讨论；


### 代码
```
class Solution 
{
public:
    bool hasPathSum(TreeNode* root, int sum) 
    {
    	if(root == NULL)
    		return false;
    	return solve(root, 0, sum);
    }
    bool solve(TreeNode* root, int sum, int target)
    {
    	if(!root->left && !root->right)
    		return sum+root->val == target;
    	else if(root->left && !root->right)
    		return solve(root->left, sum+root->val, target);
    	else if(!root->left && root->right)
    		return solve(root->right, sum+root->val, target);
    	return solve(root->left, sum+root->val, target) || solve(root->right, sum+root->val, target);
    }
};
```
## 113. Path Sum II
### 解题思路
> * 采用递归和回溯的方式，遍历各个分支，如果符合要求就保存；

### 代码
```
class Solution 
{
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) 
    {
        vector<vector<int>> res;
        vector<int> temp;
        if(root == NULL)
            return res;
        solve(res, temp, root, sum);
        return res;
    }
    void solve(vector<vector<int>> &res, vector<int> &temp, TreeNode* root, int sum)
    {
    	if(!root->left && !root->right)
    	{
    		if(root->val == sum)
    		{
	    		temp.push_back(root->val);
	    		res.push_back(temp);
	    		temp.erase(temp.end()-1);
	    	}
	    	return;
    	}
    	if(root->left)
    	{
    		temp.push_back(root->val);
    		solve(res, temp, root->left, sum-root->val);
    		temp.erase(temp.end()-1);
    	}
    	if(root->right)
    	{
    		temp.push_back(root->val);
    		solve(res, temp, root->right, sum-root->val);
    		temp.erase(temp.end()-1);
    	}
    }
};
```
## 437. Path Sum III
### 解题思路
> * 确定一个起始点，然后检查以该起始点开始有多少个分支符合要求，最后进行累加；
> * 确定起点之后，只能在后面一直追加，如果已经计算得到了所求的sum值，在其后继续追加节点，如果追加节点的和为0的话也满足要求，此时计数继续加一；

### 代码
```
class Solution
{
public:
    int pathSum(TreeNode* root, int sum)
    {
    	if(root == NULL)
    		return 0;
        return solve(root, sum, 0) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
    int solve(TreeNode* root, int target, int sum)
    {
    	if(root == NULL)
    		return 0;
    	if(sum + root->val == target)
    		return 1 + solve(root->left, 0, 0) + solve(root->right, 0, 0);
    	return solve(root->left, target, sum+root->val) + solve(root->right, target, sum+root->val);
    }
};
```

  [1]: https://leetcode.com/problems/binary-tree-inorder-traversal/
  [2]: https://leetcode.com/problems/unique-binary-search-trees-ii/
  [3]: https://leetcode.com/problems/unique-binary-search-trees/
  [4]: https://leetcode.com/problems/validate-binary-search-tree/
  [5]: https://leetcode.com/problems/recover-binary-search-tree/
  [6]: https://leetcode.com/problems/same-tree/
  [7]: https://leetcode.com/problems/symmetric-tree/
  [8]: https://leetcode.com/problems/binary-tree-level-order-traversal/
  [9]: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
  [10]: https://leetcode.com/problems/maximum-depth-of-binary-tree/
  [11]: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
  [12]: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
  [13]: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
  [14]: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
  [15]: https://leetcode.com/problems/balanced-binary-tree/
  [16]: https://leetcode.com/problems/minimum-depth-of-binary-tree/
  [17]: https://leetcode.com/problems/path-sum/
  [18]: https://leetcode.com/problems/path-sum-ii/
  [19]: https://leetcode.com/problems/path-sum-iii/