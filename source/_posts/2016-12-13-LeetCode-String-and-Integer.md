---
title: LeetCode String and Integer
date: 2016-12-13 20:19:18
categories: LeetCode
tags: [LeetCode]
---

本文将包含如下题目：
[7. Reverse Integer][1]
[8. String to Integer (atoi)][2]
[65. Valid Number][3]

<!--more-->

## 7. Reverse Integer
### 解题思路
> * 这道题直接算就行；

### 代码
```
class Solution
{
    public:
        int reverse(int x)
        {
            int p = x;
            int res = 0;
            int temp;
            while(p)
            {
                if(res > (0x7FFFFFFF)/10 || res < (1<<31)/10)
                    return 0;
                temp = p % 10;
                p = p / 10;
                res = res * 10 + temp;
                cout << res << endl;
            }
            return res;
        }
};
```

## 8. String to Integer (atoi)

### 解题思路
 > * 各种测试样例，通过就好，这种题好麻烦；
 
### 代码
```
class Solution
{
    public:
        int myAtoi(string str)
        {
            int len = str.length();
            int res = 0;
            int temp = 0;
            bool neg = false;
            int count = 0;
            for(int i = 0; i < len; ++i)
            {
                if(res > (0x7fffffff)/10)
                {
                    temp = str[i] -  '0';
                    if(temp >= 10 || temp < 0)
                        if(neg)
                            return (-1)*res;
                        else
                            return res;
                    else
                        if(neg)
                            return (1<<31);
                        else
                            return (0x7fffffff);
                }
                else if(res == (0x7fffffff)/10)
                {
                    if(i != len -1)
                        return 0;
                    if(neg)
                    {
                        if(str[i] - '0' == 8)
                            return (1<<31);
                        else if(str[i] - '0' > 8)
                            return (1<<31);
                        else
                            return (-1)*((0x7fffffff)/10*10 + str[i] - '0');
                    }
                    else
                    {
                        if(str[i] - '0' > 8)
                            return (1<<31);
                        else if(str[i] - '0' == 8)
                            return (0x7fffffff);
                        else
                            return ((0x7fffffff)/10*10 + str[i] - '0');
                    }
                }
                if(str[i] == ' ' && !res && !count)
                    continue;
                else if(str[i] == '+')
                {
                    if(count == 0)
                    {
                        neg == false;
                        count++;
                    }
                    else
                        return 0;
                }
                else if(str[i] == '-')
                {
                    if(count == 0)
                    {
                        neg = true;
                        count++;
                    }
                    else
                        return 0;
                }
                else
                {
                    temp = str[i] - '0';
                    if(temp < 0 || temp >= 10)
                    {
                        break;
                    }
                    res =  res*10 + temp;
                }
            }
            if(neg)
                return (-1)*res;
            else
                return res;
        }
};
```
## 65. Valid Number
### 解题思路
> * 又是这种测试样例的题目，好无聊！（虽然我承认这个对于写代码尤其是测试工作非常重要！！） 
> * 详细思路请点击参考[hrwhisper大神][4]的博客！

### 代码
```
class Solution 
{
	public:
		bool isNumber(string s) 
		{
			int i = 0, n = s.length();
			while (n > 0 && s[n - 1] == ' ') 
				n--;
			if (!n) 
				return false;
			while (i < n && s[i] == ' ') 
				i++;
 
			if (s[i] == '-' || s[i] == '+') 
				i++;
			bool e = false, point = false;
			bool  numBeforeE = false, numAfterE = false;
			bool  numBeforeP = false, numAfterP = false;
			for (; i < n; i++)
			{
				if (s[i] > '9' || s[i] < '0')
				{
					if (s[i] == 'e' && !e && numBeforeE)
					{
						e = true;
						if (i + 1 < n && (s[i + 1] == '-' || s[i + 1] == '+')) 
							i++;
						continue;
					}
					if (s[i] == '.' && !point  &&!e)
					{
						point = true;
						continue;
					}
					return false;
				}
				numBeforeP = numBeforeE = true;
				if (e)		
					numAfterE = true;
				if (point)  
					numAfterP = true;
			}
			if (e && !numAfterE) 
				return false;
			if (point && !numAfterP && !numBeforeP) 
				return false;
			return true;
		}
};
```


  [1]: https://leetcode.com/problems/reverse-integer/
  [2]: https://leetcode.com/problems/string-to-integer-atoi/
  [3]: https://leetcode.com/problems/valid-number/
  [4]: https://www.hrwhisper.me/leetcode-math/