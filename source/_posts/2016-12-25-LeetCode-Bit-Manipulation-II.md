---
title: LeetCode Bit Manipulation II
categories: LeetCode
tags:
  - LeetCode
  - Bit Manipulation
abbrlink: 41061
date: 2016-12-25 22:37:04
---


本文包含如下题目：
[342. Power of Four][1]
[371. Sum of Two Integers][2]
[389. Find the Difference][3]
[393. UTF-8 Validation][4]
[397. Integer Replacement][5]
[401. Binary Watch][6]
[405. Convert a Number to Hexadecimal][7]
[421. Maximum XOR of Two Numbers in an Array][8]
[461. Hamming Distance][9]
[477. Total Hamming Distance][10]


<!--more-->


## 342. Power of Four
### 解题思路
> * 简单题，不多说了；

### 代码
```
class Solution
{
    public:
        bool isPowerOfFour(int num)
        {
            int temp = 1;
            if(num == 0 || num < 0)
                return false;
            for(int i = 0; i < 16; ++i)
            {
                if((num&temp) == num)
                    return true;
                temp <<= 2;
            }
            return false;
        }
};
```

## 371. Sum of Two Integers
### 解题思路
> * 使用`^`运算求取加和结果，使用`&`运算求取进位结果，循环调用即可；

### 代码
```
class Solution
{
    public:
        int getSum(int a, int b)
        {
            int carry = a&b;
            int res = a ^ b;
            int temp;
            while(carry)
            {
                carry <<= 1;
                temp = res & carry;
                res = res ^ carry;
                carry = temp;
            }
            return res;
        }
};
```

## 389. Find the Difference
### 解题思路
> * 简单题，不多说了；

### 代码
```
class Solution
{
    public:
        char findTheDifference(string s, string t)
        {
            char res;
            vector<int> c1(26, 0);
            vector<int> c2(26, 0);
            for(auto const c : s)
                c1[c - 'a']++;
            for(auto const c : t)
            {
                if(++c2[c - 'a'] > c1[c - 'a'])
                {
                    res = c;
                }
            }
            return res;
        }
};
```

## 393. UTF-8 Validation
### 解题思路
> * 这个题目的难点在于理解题目。。。

### 代码
```
class Solution
{
    public:
        bool validUtf8(vector<int> &data)
        {
            int len = data.size();
            int count = 0;
            for(int i = 0; i < len; ++i)
            {
                if(count == 0)
                {
                    if(data[i]>>5 == 0b110)
                        count = 1;
                    else if(data[i]>>4 == 0b1110)
                        count = 2;
                    else if(data[i]>>3 == 0b11110)
                        count = 3;
                    else if(data[i]>>7)
                        return false;
                }
                else
                {
                    if(data[i]>>6 != 0b10)
                        return false;
                    count--;
                }
            }
            return count == 0;
        }
};
```

## 397. Integer Replacement
### 解题思路
> * 如果最后两位是`11`，则加法操作比较好；反之则减法操作比较好；
> * 3是一个特例，如果是3的话，需要减法操作；
> * 如果是最大整数，则因为无法加法操作，所以需要在最前边进行设置判断；

### 代码
```
class Solution
{
    public:
        int integerReplacement(int n)
        {
            if(n == 0x7fffffff)
                return 32;
            int count = 0;
            while(n > 1)
            {
                count++;
                if(n & 1)
                {
                    if(n == 3 || (n&2) == 0)
                        n--;
                    else
                        n++;
                }
                else
                    n >>= 1;
            }
            return count;
        }
};
```

## 401. Binary Watch
### 结题思路
> * 这道题主要是一道递归的题目，递归解决即可；
> * 需要注意的是hours和minutes本身的范围，以及输出的格式；

### 代码
```
class Solution
{
    public:
        vector<string> readBinaryWatch(int num)
        {
            vector<string> res;
            int hours = 0;
            int minutes = 0;
            solve(res, num, hours, minutes, 0);
            return res;
        }
        void solve(vector<string> &res, int count, int &hours, int &minutes, int cur)
        {
            if(hours > 11 || minutes > 59)
                return;
            if(count == 0)
            {
                string temp = "";
                if(hours < 10)
                {
                    temp += hours - 0 + '0';
                }
                else
                {
                    temp += hours / 10 + '0';
                    temp += hours % 10 + '0';
                }
                temp += ":";
                temp += minutes / 10 + '0';
                temp += minutes % 10 + '0';
                res.push_back(temp);
            }
            else
            {
                for(int i = cur; i < 10; ++i)
                {

                    if(i < 6 && (minutes&(1<<i)) == 0)
                    {
                        minutes += (1<<i);
                        solve(res, count-1, hours, minutes, i+1);
                        minutes -= (1<<i);
                    }
                    if(i >= 6 && (hours&(1<<(i-6))) == 0)
                    {
                        hours += (1<<(i-6));
                        solve(res, count-1, hours, minutes, i+1);
                        hours -= (1<<(i-6));
                    }
                }
            }
        }
};
```

## 405. Convert a Number to Hexadecimal
### 解题思路
> * 四位四位地去转换就可以了，注意`(-1>>4)`一直都是`-1`；

### 代码
```
class Solution {
public:
    string toHex(int num) 
    {
        if(num == 0)
            return "0";
        string res = "";
        vector<char> hex= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        while(num != 0 && res.size() < 8)
        {
            res = hex[num&15] + res;
            num >>= 4;
        }
        return res;
    }
};
```


## 421. Maximum XOR of Two Numbers in an Array
### 解题思路
> * 计算最大异或值，从最高位开始计算，使用`set`保存从高位开始前1,2,3...位的数据；
> * 每次使用左移`<<`更新res，使用`^`判断最后一位是0还是1；

### 代码
```
class Solution
{
    public:
        int findMaximumXOR(vector<int> &nums)
        {
            int res = 0;
            unordered_set<int> pre;
            for(int i = 31; i >= 0; --i)
            {
                res <<= 1;
                pre.clear();
                for(auto const num : nums)
                    pre.insert(num>>i);
                for(auto const p : pre)
                {
                    if(pre.find((res^1)^p) != pre.end())
                    {
                        res++;
                        break;
                    }
                }
            }
            return res;
        }
};
```

## 461. Hamming Distance
### 解题思路
> * 简单题，用到了`temp&(temp-1)`；

### 代码
```
class Solution
{
    public:
        int hammingDistance(int x, int y)
        {
            int res = 0;
            int temp = x^y;
            while(temp)
            {
                temp = temp&(temp-1);
                res++;
            }
            return res;
        }
};
```
## 477. Total Hamming Distance
### 解题思路
> * 每一位只有为1才会产生汉明距离，总的汉明距离和为1的个数×0的个数；

### 代码
```
class Solution
{
    public:
        int totalHammingDistance(vector<int> &nums)
        {
            int res = 0;
            int len = nums.size();
            int count = 0;
            for(int i = 0; i < 32; ++i)
            {
                count = 0;
                for(int j = 0; j < nums.size(); ++i)
                {
                    if((nums[j]>>i)&1)
                        count++;
                }
                res += (len - count) * count;
            }
            return res;
        }
};
```


  [1]: https://leetcode.com/problems/power-of-four/
  [2]: https://leetcode.com/problems/sum-of-two-integers/
  [3]: https://leetcode.com/problems/find-the-difference/
  [4]: https://leetcode.com/problems/utf-8-validation/
  [5]: https://leetcode.com/problems/integer-replacement/
  [6]: https://leetcode.com/problems/binary-watch/
  [7]: https://leetcode.com/problems/convert-a-number-to-hexadecimal/
  [8]: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
  [9]: https://leetcode.com/problems/hamming-distance/
  [10]: https://leetcode.com/problems/total-hamming-distance/