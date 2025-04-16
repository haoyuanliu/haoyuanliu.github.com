---
title: 71. Simplify Path
categories: LeetCode
tags:
  - LeetCode
  - Stack
abbrlink: 55219
date: 2016-12-15 16:55:39
---

[题目链接！][1]

### 解题思路
> * 使用一个栈去存储每一条路径，如果是`..`就pop()； 
> * 注意处理边界`/`， `/.`， `/..`；

<!--more-->

### 代码
```
class Solution
{
    public:
        string simplifyPath(string path)
        {
            string res, temp;
            res = temp = "";
            stack<string> st;
            int len = path.size();
            for(int i = 0; i < len; ++i)
            {
                if(path[i] == '/')
                {
                    if(temp == "" || temp == ".")
                    {
                        temp = "";
                        continue;
                    }
                    else if(temp == "..")
                    {
                        temp = "";
                        if(!st.empty())
                            st.pop();
                    }
                    else
                    {
                        st.push(temp);
                        temp = "";
                    }
                }
                else
                {
                    temp += path[i];
                }
            }
            if(temp != "")
            {
                if(temp == "..")
                {
                    if(!st.empty())
                        st.pop();
                }
                else if(temp != ".")
                    st.push(temp);
            }
            if(st.empty())
                return "/";
            while(!st.empty())
            {
                res = "/" + st.top() + res;
                st.pop();
            }
            return res;
        }
};
```


  [1]: https://leetcode.com/problems/simplify-path/