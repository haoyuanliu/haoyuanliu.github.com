---
title: LeetCode Tree II
date: 2017-01-12 11:53:09
categories: LeetCode
tags: [LeetCode, Tree]
---


本文包含如下题目：
[114. Flatten Binary Tree to Linked List][1]
[116. Populating Next Right Pointers in Each Node][2]
[117. Populating Next Right Pointers in Each Node II][3] 
[124. Binary Tree Maximum Path Sum][4]
[129. Sum Root to Leaf Numbers][5]
[144. Binary Tree Preorder Traversal][6]
[145. Binary Tree Postorder Traversal][7]
[173. Binary Search Tree Iterator][8]
[199. Binary Tree Right Side View][9]
[222. Count Complete Tree Nodes][10]
[226. Invert Binary Tree][11]
[230. Kth Smallest Element in a BST][12]
[235. Lowest Common Ancestor of a Binary Search Tree][13]
[236. Lowest Common Ancestor of a Binary Tree][14]
[257. Binary Tree Paths][15]
[297. Serialize and Deserialize Binary Tree][16]
[337. House Robber III][17]
[404. Sum of Left Leaves][18]
[449. Serialize and Deserialize BST][19]
[450. Delete Node in a BST][20]

<!--more-->


## 114. Flatten Binary Tree to Linked List
### 解题思路 I
> * 使用一个栈结构存储各个节点，通过出栈入栈操作重新搭建树结构；
> * 注意这里要先将右子节点入栈，保证先访问的是左子节点；

### 代码
```
class Solution 
{
public:
    void flatten(TreeNode* root) 
    {
        if(root == NULL)
        	return;
        stack<TreeNode*> st;
        TreeNode* p = root;
        if(p->right) st.push(p->right);
        if(p->left) st.push(p->left);
        while(!st.empty())
        {
        	p->left = NULL;
        	p->right = st.top();
        	p = p->right;
        	TreeNode* temp = st.top();
        	st.pop();
        	if(temp->right) st.push(temp->right);
        	if(temp->left) st.push(temp->left);
        }
    }
};
```
### 解题思路 II
> * 使用递归的方法，先对右子树进行转换操作，然后左子树，最后根节点，使用一个`pre`参数保存每次转换之后的根节点，不断进行递归即可；

### 代码
```
class Solution 
{
private:
	TreeNode* pre = NULL;
public:
    void flatten(TreeNode* root) 
    {
        if(root == NULL)
        	return;
   		flatten(root->right);
   		flatten(root->left);
   		root->right = pre;
   		root->left = NULL;
   		pre = root;
    }
};
```
### 解题思路 III
> * 将根节点右子树置于左子树叶子节点的右子树位置；
> * 将左子树置于根节点的右子树位置，根节点左子树置为NULL；
> * 不断循环上述操作；

### 代码
```
class Solution 
{
public:
    void flatten(TreeNode* root) 
    {
        while(root)
        {
        	if(root->left && root->right)
        	{
        		TreeNode* l = root->left;
        		while(l->right)
        			l = l->right;
        		l->right = root->right;
        	}
        	if(root->left)
        		root->right = root->left;
        	root->left = NULL;
        	root = root->right;
        }
    }
};
```

## 116. Populating Next Right Pointers in Each Node
### 解题思路 I
> * 使用一个`queue`进行BFS，然后依次进行连接构建；

### 代码
```
class Solution 
{
public:
    void connect(TreeLinkNode *root) 
    {
    	if(root == NULL)
    		return;
    	queue<TreeLinkNode*> que;
    	que.push(root);
    	while(!que.empty())
    	{
    		TreeLinkNode* p = que.front();
            int len = que.size();
    		for(int i = 0; i < len; ++i)
    		{

                if(que.front()->left) que.push(que.front()->left);
                if(que.front()->right) que.push(que.front()->right);
                que.pop();
    			if(i < len-1)
    			{
    				p->next = que.front();
                    p = p->next;
    			}     			
    		}
    		p->next = NULL;
    	}
    }
};
```
### 解题思路 II
> * 遍历每一层进行连接即可；

### 代码
```
class Solution 
{
public:
    void connect(TreeLinkNode *root) 
    {
        if(root == NULL) return;
        TreeLinkNode* pre = root;
        TreeLinkNode* cur = NULL;
        while(pre->left)
        {
            cur = pre;
            while(cur)
            {
                cur->left->next = cur->right;
                if(cur->next)
                    cur->right->next = cur->next->left;
                cur = cur->next;
            }
            pre = pre->left;
        }
    }
};
```


## 117. Populating Next Right Pointers in Each Node II 
### 解题思路 I
> * 如116题，使用`queue`可以AC；

### 代码
```
class Solution 
{
public:
    void connect(TreeLinkNode *root) 
    {
    	if(root == NULL)
    		return;
    	queue<TreeLinkNode*> que;
    	que.push(root);
    	while(!que.empty())
    	{
    		TreeLinkNode* p = que.front();
            int len = que.size();
    		for(int i = 0; i < len; ++i)
    		{

                if(que.front()->left) que.push(que.front()->left);
                if(que.front()->right) que.push(que.front()->right);
                que.pop();
    			if(i < len-1)
    			{
    				p->next = que.front();
                    p = p->next;
    			}     			
    		}
    		p->next = NULL;
    	}
    }
};
```

### 解题思路 II
> * 使用指针的方法，遍历每一层进行树结构的构建；
> * 使用一个指针`head`保存每一层头节点，使用指针`pre`保存上一个连接的节点，方便进行连接；
> * 仍然使用指针`cur`保存上层节点，实现遍历；

### 代码
```
class Solution 
{
public:
    void connect(TreeLinkNode *root) 
    {
        if(root == NULL)
            return;
        TreeLinkNode* head = NULL;
        TreeLinkNode* pre = NULL;
        TreeLinkNode* cur = root;
        while(cur)
        {
            while(cur)
            {
                if(cur->left)
                {
                    if(!head)
                        head = cur->left;
                    else
                        pre->next = cur->left;
                    pre = cur->left;
                }
                if(cur->right)
                {
                    if(!head)
                        head = cur->right;
                    else
                        pre->next = cur->right;
                    pre = cur->right;
                }
                cur = cur->next;
            }
            cur = head;
            head = pre = NULL;
        }
    }
};
```

## 124. Binary Tree Maximum Path Sum
### 解题思路
> 首先要维持一个最大值`res`，将其初始值设置为最小值；
> 使用辅助递归函数遍历所有的节点，返回以该节点为根节点的最大路径和，同时更新`res`的值；

### 代码
```
class Solution 
{
public:
    int maxPathSum(TreeNode* root) 
    {
    	int res = (1<<31);
        if(root == NULL) return 0;
        getMax(root, res);
        return res;
    }

    int getMax(TreeNode* root, int &res)
    {
    	if(root == NULL) return 0;
    	int left = max(0, getMax(root->left, res));
    	int right = max(0, getMax(root->right, res));
    	res = max(res, left + right + root->val);
    	return root->val + max(left, right);
    }
};
```

## 129. Sum Root to Leaf Numbers
### 解题思路

> 仍然是使用搜索递归，计算每一条支路的加和最后返回到主函数；

### 代码
```
class Solution 
{
public:
    int sumNumbers(TreeNode* root) 
    {
        if(root == NULL) return 0;
        return solve(root, 0);
    }
    int solve(TreeNode* root, int res)
    {
    	if(root == NULL)
    		return 0;
    	if(!root->left && !root->right)    		
    		return res * 10 + root->val;
    	return solve(root->left, res * 10 + root->val) + solve(root->right, res * 10  + root->val);
    }
};
```

## 144. Binary Tree Preorder Traversal
### 解题思路

> 考察树的非递归遍历；

### 代码
```
class Solution 
{
public:
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int> res;
        if(root == NULL) return res;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while(p || !s.empty())
        {
        	while(p)
        	{
        		res.push_back(p->val);
        		s.push(p);
        		p = p->left;
        	}
        	if(!s.empty())
        	{
        		p = s.top();
        		s.pop();
        		p = p->right;
        	}
        }
        return res;
    }
};
```

## 145. Binary Tree Postorder Traversal
### 解题思路

> 二叉树的后序遍历，使用非递归方法； 

> **方法一**：设置`pre`和`cur`两个指针，通过判断`pre`和`cur`两个指针的属性和关系进行遍历；

> **方法二**：类似于先序遍历的非递归遍历，将节点按照`根节点->右子节点->左子节点`的顺序放到vector中，最后将vector逆序返回即可；

### 代码
**方法一：**
```
class Solution 
{
public:
    vector<int> postorderTraversal(TreeNode* root) 
    {
    	vector<int> res;
    	if(root == NULL) return res;
        stack<TreeNode*> s;
        TreeNode *pre = NULL;
        TreeNode *cur = NULL;
        s.push(root);
        while(!s.empty())
        {
        	cur = s.top();
        	if((!cur->left && !cur->right) 
        		|| (pre && (cur->left == pre || cur->right == pre)))
        	{
        		res.push_back(cur->val);
        		s.pop();
        		pre = cur;
        	}
        	else
        	{
        	    if(cur->right) s.push(cur->right);
        		if(cur->left) s.push(cur->left);
        	}
        }
        return res;
    }
};
```
**方法二：**
```
class Solution 
{
public:
    vector<int> postorderTraversal(TreeNode* root) 
    {
        vector<int> res;
        if(root == NULL) return res;
        stack<TreeNode*> s;
        TreeNode *cur = NULL;
        s.push(root);
        while(!s.empty())
        {
            cur = s.top();
            s.pop();
            res.push_back(cur->val);
            if(cur->left) s.push(cur->left);
            if(cur->right) s.push(cur->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

## 173. Binary Search Tree Iterator
### 解题思路

> 就是利用二叉树的中序遍历不断获取数据即可，二叉搜索树的中序遍历即为从小到大的有序遍历；

### 代码
```
class BSTIterator 
{
	stack<TreeNode*> s;
public:
    BSTIterator(TreeNode *root) 
    {
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() 
    {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() 
    {
     	TreeNode* temp = s.top();
     	s.pop();
     	pushAll(temp->right);
     	return temp->val;   
    }
private:
	void pushAll(TreeNode* node)
	{
		for(; node != NULL; s.push(node), node = node->left);
	}
};
```

## 199. Binary Tree Right Side View
### 解题思路

> **方法一**：使用一个`queue`去遍历每一层的节点，将最后一个节点保存到结果中；

> **方法二**：使用类似于先序遍历的方法，每次都先进行右子节点的操作，从而保证每一层最开始访问的节点必定是该层最右边的节点，且只将该节点保存到结果中；

### 代码
**方法一**
```
class Solution 
{
public:
    vector<int> rightSideView(TreeNode* root) 
    {
        vector<int> res;
        if(root == NULL) return res;
        queue<TreeNode*> que;
        TreeNode* cur = NULL;
        que.push(root);
        while(!que.empty())
        {
        	int len = que.size();
        	for(int i = 0; i < len; ++i)
        	{
        		cur = que.front();
        		que.pop();
        		if(cur->left) que.push(cur->left);
        		if(cur->right) que.push(cur->right);
        	}
        	res.push_back(cur->val);
        }
        return res;
    }
};
```
**方法二**
```
class Solution 
{
public:
    vector<int> rightSideView(TreeNode* root) 
    {
        vector<int> res;
        if(root == NULL) return res;
        solve(root, res, 0);
        return res;
    }
    void solve(TreeNode* root, vector<int> &res, int depth)
    {
    	if(root == NULL) return;
    	if(depth == res.size()) res.push_back(root->val);
    	solve(root->right, res, depth+1);
    	solve(root->left, res, depth+1);
    }
};
```

## 222. Count Complete Tree Nodes
### 解题思路

> 首先获取整个二叉树的高度为`h`，如果右子树的高度为`h-1`，则左子树是一个完全二叉树，反之右子树是一个完全二叉树。对于完全二叉树我们很容易计算他的节点数量，然后使用递归解决。

### 代码
```
class Solution 
{
public:
    int countNodes(TreeNode* root) 
    {
        int h = getHeight(root);
        return h < 0 ? 0 : getHeight(root->right) == h-1 ? (1<<h) + countNodes(root->right) : (1<<h-1) + countNodes(root->left);
    }
    int getHeight(TreeNode* root)
    {
    	return root == NULL ? -1 : 1 + getHeight(root->left);
    }
};
```
## 226. Invert Binary Tree
### 解题思路

> **方法一**：递归，分别计算左右子节点的invert，然后将左右子节点交换完成invert；

> **方法二**：使用栈结构，利用栈结构的FIFO性质，实现节点的反转，同时对每个节点都要交换左右子节点；

### 代码
**方法一**
```
class Solution 
{
public:
    TreeNode* invertTree(TreeNode* root) 
    {
        if(root == NULL) return NULL;
    	root->left = invertTree(root->left);
    	root->right = invertTree(root->right);
    	swap(root->left, root->right);
        return root;
    }
};
```
**方法二**
```
class Solution 
{
public:
    TreeNode* invertTree(TreeNode* root) 
    {
        if(root == NULL) return NULL;
    	stack<TreeNode*> s;
    	s.push(root);
    	while(!s.empty())
    	{
    		TreeNode* cur = s.top();
    		s.pop();
    		if(cur)
    		{
	    		s.push(cur->left);
	    		s.push(cur->right);
	    		swap(cur->left, cur->right);
	    	}
    	}
    	return root;
    }
};
```


## 230. Kth Smallest Element in a BST
### 解题思路

> 考察树的中序遍历，使用递归遍历和非递归遍历解决；

### 代码
**递归方法**
```
class Solution 
{
public:
	int count = 0;
	int res;
    int kthSmallest(TreeNode* root, int k) 
    {
    	inOrder(root, k);
    	return res;
    }
    void inOrder(TreeNode* root, int k)
    {
    	if(root == NULL) return;
    	inOrder(root->left, k);
    	if(++count == k)
    	{
    		res = root->val;
    		return;
    	}
    	inOrder(root->right, k);
    }
};
```
**非递归**
```
class Solution 
{
public:
    int kthSmallest(TreeNode* root, int k) 
    {
    	stack<TreeNode*> s;
    	int count = 0;
    	TreeNode* p = root;
    	while(!s.empty() || p)
    	{
    		while(p)
    		{
    			s.push(p);
    			p = p->left;
    		}
    		p = s.top();
    		s.pop();
    		if(++count == k)
    			return p->val;
    		p = p->right;
    	}
    	return 0;
    }
};
```

## 235. Lowest Common Ancestor of a Binary Search Tree
### 解题思路

> 因为是二叉搜索树，所以需要判断`p`和`q`两个节点的值与`root`节点的关系，如果在`root`两边或者直接等于`root`则祖先节点就是`root`，否则，祖先节点就有可能`root->left`和`root->right`两个中再次求取；

### 代码
```
class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
		while((root->val - p->val) * (root->val - q->val) > 0)
			root = p->val < root->val ? root->left : root->right;
        return root;
    }
};
```

## 236. Lowest Common Ancestor of a Binary Tree
### 解题思路

> 有点类似分治的思路，如果`root == p || root == q`直接返回`root`；

> 分别求取`lowestCommonAncestor(root->left, p, q)`和`lowestCommonAncestor(root->right, p, q);`，如果结果为`NULL`则证明`p`和`q`都不在该子树中，反之，则至少有一个在该子树中，然后继续讨论即可；

### 代码
```
class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
    	if(!root || root == p || root == q) return root;
    	TreeNode* left = lowestCommonAncestor(root->left, p, q);
    	TreeNode* right = lowestCommonAncestor(root->right, p, q);
    	return !left ? right : !right ? left : root;   
    }
};
```

## 257. Binary Tree Paths
### 解题思路

> 使用递归的思路，遍历每一条路径；

### 代码
```
class Solution 
{
public:
    vector<string> binaryTreePaths(TreeNode* root) 
    {
        vector<string> res;
        if(root == NULL) return res;
        dfs(res, root, "");
        return res;
    }
    void dfs(vector<string> &res, TreeNode* root, string str)
    {
    	if(!root->left && !root->right)
    	{
    		res.push_back(str+to_string(root->val));
    		return;
    	}
    	if(root->left) dfs(res, root->left, str+to_string(root->val)+"->");
    	if(root->right) dfs(res, root->right, str+to_string(root->val)+"->");
    }
};
```

## 297. Serialize and Deserialize Binary Tree
### 解题思路

> 详细思路请参考此[链接][21]！！

### 代码
```
class Codec 
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        ostringstream out;
        myserialize(root, out);
        return out.str();
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        istringstream is(data);
        return mydeserialize(is);
    }
private:
    void myserialize(TreeNode *root, ostringstream &out)
    {
        if(root)
        {
            out << root->val << " ";
            myserialize(root->left, out);
            myserialize(root->right, out);
        }
        else out << "# ";
    }
    TreeNode* mydeserialize(istringstream &data)
    {
        string val;
        data >> val;
        if(val == "#") return NULL;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = mydeserialize(data);
        root->right = mydeserialize(data);
        return root;
    }
};
```
## 337. House Robber III
### 解题思路
详细解析请看这个[链接][22]！！

### 代码
```
class Solution 
{
public:
    int rob(TreeNode* root) 
    {
    	vector<int> res = robSub(root);
    	return max(res[0], res[1]);    
    }
    vector<int> robSub(TreeNode* root)
    {
    	if(root == NULL) return vector<int>(2, 0);
    	vector<int> left = robSub(root->left);
    	vector<int> right = robSub(root->right);
    	vector<int> res(2, 0);
    	res[0] = max(left[0], left[1]) + max(right[0], right[1]);
    	res[1] = root->val + left[0] + right[0];
    	return res;
    }
};
```

## 404. Sum of Left Leaves
### 解题思路

> **递归方法**：如果左子节点是左叶子节点，则加和保存，否则迭代计算左子节点的`sumOfLeftLeaves`，对于右子节点，直接迭代计算`sumOfLeftLeaves`；

> **非递归方法**：使用一个`stack`对二叉树进行遍历，对于每个节点，判断其左子节点是否是叶子节点，如果是就加和保存，否则入栈，对于右子节点，只要不是叶子节点就统统入栈。

### 代码
**递归**
```
class Solution 
{
public:
	int res = 0;
    int sumOfLeftLeaves(TreeNode* root) 
    {
    	if(root == NULL) return 0;
    	int res = 0;
    	if(root->left)
    	{
    		if(!root->left->left && !root->left->right)
    			res += root->left->val;
    		else
    			res += sumOfLeftLeaves(root->left);
    	}
    	res += sumOfLeftLeaves(root->right);
    	return res;
    }
};
```
**非递归**
```
class Solution 
{
public:
    int sumOfLeftLeaves(TreeNode* root) 
    {
    	int res = 0;
    	if(root == NULL) return res;
    	stack<TreeNode*> s;
    	s.push(root);
    	while(!s.empty())
    	{
    		TreeNode* p = s.top();
    		s.pop();
    		if(p->left)
    		{
    			if(!p->left->left && !p->left->right)
    				res += p->left->val;
    			else
    				s.push(p->left);
    		}
    		if(p->right)
    		{
    			if(p->right->left || p->right->right)
    				s.push(p->right);
    		}
    	}
    	return res;
    }
};
```

## 449. Serialize and Deserialize BST
### 解题思路

> 因为是一个二叉搜索树，所以通过获取其前序遍历的数值组合就可以唯一的重新构建出原来的树结构，这里使用了`iostringstream`，方便进行序列化和反序列化。

### 代码
```
class Codec 
{
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        ostringstream out;
        mySerialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        if(data == "") return NULL;
        istringstream in(data);
        return myDeserialize(in);
    }
private:
	void mySerialize(TreeNode* root, ostringstream &out)
	{
		if(root == NULL) return;
		out << root->val << " ";
		mySerialize(root->left, out);
		mySerialize(root->right, out);
	}
	TreeNode* myDeserialize(istringstream &in)
	{
		string val;
		in >> val;
		TreeNode *root = new TreeNode(stoi(val));
		while(in >> val)
			buildTree(root, stoi(val));
		return root;
	}
	void buildTree(TreeNode* root, int n)
	{
		if(root->val > n)
		{
			if(root->left == NULL)
				root->left = new TreeNode(n);
			else
				buildTree(root->left, n);
		}
		else
		{
			if(root->right == NULL)
				root->right = new TreeNode(n);
			else
				buildTree(root->right, n);
		}
	}
};

```

## 450. Delete Node in a BST
### 解题思路

> 只有当`root->val == key`的时候才执行删除操作，否则根据`key`的大小在左右子树中执行删除操作。

> 删除过程中，如果是叶子节点则直接返回`NULL`，否则取其左右子节点中不为`NULL`的作为新的根节点返回。

### 代码
```
class Solution 
{
public:
    TreeNode* deleteNode(TreeNode* root, int key) 
    {
    	if(root == NULL) return NULL;

        if(root->val == key)
        {
        	if(root->right)
        	{
        		TreeNode* p = root->right;
        		while(p->left) p = p->left;
        		p->left = root->left;
        		return root->right;
        	}
        	else if(root->left)
        		return root->left;
        	else return NULL;
        }

        if(root->val > key)
        	root->left = deleteNode(root->left, key);
        if(root->val < key)
        	root->right = deleteNode(root->right, key);

        return root;
    }
};
```



  [1]: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
  [2]: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
  [3]: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
  [4]: https://leetcode.com/problems/binary-tree-maximum-path-sum/
  [5]: https://leetcode.com/problems/sum-root-to-leaf-numbers/
  [6]: https://leetcode.com/problems/binary-tree-preorder-traversal/
  [7]: https://leetcode.com/problems/binary-tree-postorder-traversal/
  [8]: https://leetcode.com/problems/binary-search-tree-iterator/
  [9]: https://leetcode.com/problems/binary-tree-right-side-view/
  [10]: https://leetcode.com/problems/count-complete-tree-nodes/
  [11]: https://leetcode.com/problems/invert-binary-tree/
  [12]: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
  [13]: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
  [14]: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
  [15]: https://leetcode.com/problems/binary-tree-paths/
  [16]: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
  [17]: https://leetcode.com/problems/house-robber-iii/
  [18]: https://leetcode.com/problems/sum-of-left-leaves/
  [19]: https://leetcode.com/problems/serialize-and-deserialize-bst/
  [20]: https://leetcode.com/problems/delete-node-in-a-bst/
  [21]: https://discuss.leetcode.com/category/375/serialize-and-deserialize-binary-tree
  [22]: https://discuss.leetcode.com/topic/39834/step-by-step-tackling-of-the-problem/3