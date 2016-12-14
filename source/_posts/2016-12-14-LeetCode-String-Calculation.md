---
title: LeetCode String Calculation
date: 2016-12-14 10:47:34
categories: LeetCode
tags: [LeetCode]
---


本文包含如下题目：

[43. Multiply Strings][1]
[66. Plus One][2]
[67. Add Binary][3]
[415. Add Strings][4]

<!--more-->

## 43. Multiply Strings

### 解题思路
> * 字符串乘法，大数乘法；
> * 使用一个vector<int>不断的累加每个位上的数值，最后统一进行进位操作；

### 代码
```
class Solution
{
    public:
        string multiply(string num1, string num2)
        {
            int m = num1.size();
            int n = num2.size();
            if(num1 == "0" || num2 == "0")
                return "0";
            reverse(num1.begin(), num1.end());
            reverse(num2.begin(), num2.end());
            vector<int> res(m+n, 0);
            for(int i = 0; i < m; ++i)
                for(int j = 0, id = i; j < n; ++j)
                    res[id++] += (num1[i] - '0') * (num2[j] - '0');
            int carry = 0;
            for(int i = 0; i < m+n; ++i)
            {
                int temp = res[i];
                res[i] = (temp + carry) % 10;
                carry = (temp + carry) / 10;
            }
            string ans(m+n, '0');
            for(int i = m+n-1, id = 0; i >= 0; --i)
                ans[id++] = res[i] + '0';
            int start;
            for(int i = 0; i < m+n; ++i)
                if(ans[i] != '0')
                {
                    start = i;
                    break;
                }
            return ans.substr(start);
        }
};
```

## 66. Plus One
### 解题思路
> * 字符串加一，carry初始化为1就好；
### 代码
```
class Solution
{
    public:
        vector<int> plusOne(vector<int> & digits)
        {
            int carry = 1;
            int len = digits.size();
            reverse(digits.begin(), digits.end());

            vector<int> res(len, 0);
            for(int i = 0; i < len; ++i)
            {
                res[i] = (carry + digits[i]) % 10;
                carry = (carry + digits[i]) / 10;
            }
            if(carry)
                res.push_back(1);
            reverse(res.begin(), res.end());
            return res;
        }
};
```

## 67. Add Binary
### 解题思路
> * 也就是mod2就好了；

### 代码
```
class Solution
{
    public:
        string addBinary(string a, string b)
        {
            int m = a.size();
            int n = b.size();
            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            int carry = 0;
            string res = "";
            int x, y;
            for(int i = 0; i < max(m, n); ++i)
            {
                if(i >= m)
                    x = 0;
                else
                    x = a[i] - '0';
                if(i >= n)
                    y = 0;
                else
                    y = b[i] - '0';
                res += ((x + y + carry) % 2 + '0');
                carry = (x + y + carry) / 2;
            }
            if(carry)
                res += '1';
            reverse(res.begin(), res.end());
            return res;
        }
};
```

## 415. Add Strings
### 解题思路
> * 字符串相加，注意一下最后的进位就好；

### 代码
```
class Solution
{
    public:
        string addStrings(string num1, string num2)
        {
            int m = num1.size();
            int n = num2.size();
            string res = "";
            reverse(num1.begin(), num1.end());
            reverse(num2.begin(), num2.end());
            int carry = 0;
            int a, b;
            for(int i = 0; i < max(m, n); ++i)
            {
                if(i >= m)
                    a = 0;
                else
                    a = num1[i] - '0';

                if(i >= n)
                    b = 0;
                else
                    b = num2[i] - '0';

                res += (a + b + carry) % 10 + '0';
                carry = (a + b + carry) / 10;
            }
            if(carry)
                res += '1';
            reverse(res.begin(), res.end());
            return res;
        }
};
```


  [1]: https://leetcode.com/problems/multiply-strings/
  [2]: https://leetcode.com/problems/plus-one/
  [3]: https://leetcode.com/problems/add-binary/
  [4]: https://leetcode.com/problems/add-strings/