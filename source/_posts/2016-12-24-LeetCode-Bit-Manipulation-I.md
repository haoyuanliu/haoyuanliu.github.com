---
title: LeetCode Bit Manipulation I
categories: LeetCode
tags:
  - LeetCode
  - Bit Manipulation
abbrlink: 25801
date: 2016-12-24 18:36:13
---

本文包含如下题目：
[78. Subsets][1]
[136. Single Number][2]
[137. Single Number II][3]
[169. Majority Element][4]
[187. Repeated DNA Sequences][5]
[190. Reverse Bits][6]
[191. Number of 1 Bits][7]
[201. Bitwise AND of Numbers Range][8]
[231. Power of Two][9]
[260. Single Number III][10]
[268. Missing Number][11]
[318. Maximum Product of Word Lengths][12]
[338. Counting Bits][13]

<!--more-->


## 78. Subsets
### 解题思路
> * 使用bitmap表示：
`000->[],  001->[1], 010->[2], 011->[1, 2], 100->[3],  101->[1, 3], 110->[2, 3], 111->[1, 2, 3]`

### 代码
```
class Solution
{
    public:
        vector<vector<int> > subsets(vector<int> &nums)
        {
            vector<vector<int> > res;
            vector<int> temp;
            int len = nums.size();
            for(int i = 0; i < (1<<len); ++i)
            {
                temp.clear();
                int index = 0;
                while(i >= (1<<index))
                {
                    if(i & (1<<index))
                        temp.push_back(nums[index]);
                    index++;
                }
                res.push_back(temp);
            }
            return res;
        }
};
```

## 136. Single Number
### 解题思路
> * 这道题用bitmap，使用异或操作，相同的数都会消去，最后只剩下Single Number；

### 代码
```
class Solution
{
    public:
        int singleNumber(vector<int> &nums)
        {
            int res = 0;
            for(int i = 0; i < nums.size(); i++)
            {
                res ^= nums[i];
            }
            return res;
        }
};
```

## 137. Single Number II
### 解题思路
> * 仍然使用位运算，使用ones、twos两位表示每一位的累加和；
> * 对应循环关系为：00->01->10->00 即 0->1->2->0;
> * 最后返回ones中的结果即可；
> * 如果重复的个数是5的话，就需要三位数来表示：000->001->010->011->100->000;


### 代码
```
class Solution
{
    public:
        int singleNumber(vector<int> &nums)
        {
            int ones = 0, twos = 0;
            for(int i = 0; i < nums.size(); ++i)
            {
                ones = (ones ^ nums[i]) & ~twos;
                twos = (twos ^ nums[i]) & ~ones;
            }
            return ones;
        }
};
```

## 169. Majority Element
### 解题思路
> * 思路I：对数组进行排序，然后取中位数就可以了；
> * 思路II：遍历数组，初始化一个res，维持一个count计数变量，只有count减为零的时候才更新res，因为众数超过总数的一半，所以最后必然能够转换到res中；

### 代码
```
class Solution
{
    public:
        int majorityElement(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            int len = nums.size();
            return nums[len/2];
        }
};
```

```
class Solution
{
    public:
        int majorityElement(vector<int> &nums)
        {
            int res = nums[0];
            int count = 1;
            for(int i = 1; i < nums.size(); ++i)
            {
                if(count == 0)
                {
                    count++;
                    res = nums[i];
                }
                else if(nums[i] == res)
                    count++;
                else
                    count--;
            }
            return res;
        }
};
```

## 187. Repeated DNA Sequences
### 解题思路
> * 字符串中只包含了A, C, G, T四种字符，这四种字符的不同进制表示如下所示：
16进制：0X41, 0X43, 0X47, 0X54
10进制：65， 67， 71， 84
8进制：0101, 0103, 0107, 0124;
> * 观察上述进制规律，可以发现如果用二进制进行表示，其最后三位分别为001， 011， 111， 100；
> * 所以我们可以使用一个int类型整数保存包含10个字符的子串，一共需要30位，int有32位，正好满足要求；
> * 然后使用一个map进行映射保存，遍历所有的子串有重复的就进行保存即可；
> * 这里推荐使用`unordered_map`而不是map，`unordered_map`不会进行排序，效率更高；

### 代码
```
class Solution
{
    public:
        vector<string> findRepeatedDnaSequences(string s)
        {
            unordered_map<int, int> m;
            vector<string> res;
            int temp = 0;
            for(int i = 0; i < s.size(); ++i)
            {
                if(m[temp = temp << 3 & 0x3FFFFFFF | s[i] & 7]++ == 1)
                    res.push_back(s.substr(i-9, 10));
            }
            return res;
        }
};
```

## 190. Reverse Bits
### 解题思路
> * 这道题就简单了，移位操作32次就可以了；

### 代码
```
class Solution
{
    public:
        uint32_t reverseBits(uint32_t n)
        {
            uint32_t res = 0;
            for(int i = 0; i < 32; ++i)
            {
                res <<= 1;
                int temp = n & 1;
                res = res | temp;
                n >>= 1;       
            }
            return res;
        }
};
```

## 191. Number of 1 Bits
### 解题思路
> * 这道题不多说了；

### 代码
```
class Solution
{
    public:
        int hammingWeight(uint32_t n)
        {
            int res = 0;
            while(n)
            {
                if(n & 1)
                    res++;
                n >>= 1;
            }
            return res;
        }
};
```

## 201. Bitwise AND of Numbers Range
### 解题思路
> * 首先如果n > m，则最后一位必定是0，取fun(m>>1, n>>1)<<1作为最终结果；
> * 沿用这种思路，迭代去求取即可；

### 代码
```
class Solution
{
    public:
        int rangeBitwiseAnd(int m, int n)
        {
            return n > m ? rangeBitwiseAnd(m>>1, n>>1) << 1 : m;
        }
};
```
## 231. Power of Two
### 解题思路
> * 这里注意负数和零都返回false；

### 代码
```
class Solution
{
    public:
        bool isPowerOfTwo(int n)
        {
            if(n == 0 || n&(1<<31))
                return false;
            for(int i = 0; i < 32; ++i)
                if((n & (1<<i)) == n)
                    return true;
            return false;
        }
};
```

## 260. Single Number III
### 解题思路I
> * 首先对数组执行sort，然后两个两个地去找；

### 代码
```
class Solution
{
    public:
        vector<int> singleNumber(vector<int> &nums)
        {
            vector<int> res;
            if(nums.size() == 2)
            {
                res.push_back(nums[0]);
                res.push_back(nums[1]);
                return res;
            }
            sort(nums.begin(), nums.end());
            for(int i = 0; i < nums.size(); i++)
            {
                if(nums[i] == nums[i+1])
                    i++;
                else
                    res.push_back(nums[i]);
            }
            return res;
        }
};
```
### 解题思路II
> * 假设结果所求为a和b两个数，对数组中所有的数据执行异或操作，则可以得到所求两个数的异或结果，假设为a^b；
> * 利用位运算获取a^b中为1的设置位，表示a和b在这一设置位上一个是1，一个是0，可以把a和b区分开来，这里我们选择最右边为1的那位；
> * 再次对数组进行遍历异或，使用设置为进行区分，则可以得到所求结果；
> * 使用`diff &= -diff`可以获取diff中最右边为零的设置位，`diff &= ~(diff - 1)`同样也可以，这里mark学习一下！

### 代码
```
class Solution
{
    public:
        vector<int> singleNumber(vector<int> &nums)
        {
            vector<int> res(2, 0);
            int temp = 0;
            for(int i = 0; i < nums.size(); ++i)
                temp ^= nums[i];
            temp &= -temp;
            for(int i = 0; i < nums.size(); ++i)
            {
                if(temp & nums[i])
                    res[0] ^= nums[i];
                else
                    res[1] ^= nums[i];
            }
            return res;
        }
};
```

## 268. Missing Number
### 解题思路
> * 方法一：先sort然后用二分法去找；
> * 方法二：使用异或，同时异或下标和数组值，存在的就会消去；
> * 方法三：使用sum求和，然后作减法即可；

### 代码
```
//方法一
class Solution
{
    public:
        int missingNumber(vector<int> &nums)
        {
            sort(nums.begin(), nums.end());
            int left = 0;
            int right = nums.size();
            int mid = (left + right) / 2;
            while(left < right)
            {
                mid = (left + right) / 2;
                if(mid < nums[mid])
                    right = mid;
                else
                    left = mid+1;
            }
            return left;
        }
};
```
```
//方法二
class Solution
{
    public:
        int missingNumber(vector<int> &nums)
        {
            int res = nums.size();
            for(int i = 0; i < nums.size(); ++i)
            {
                res ^= nums[i];
                res ^= i;
            }
            return res;
        }
};
```
```
//方法三
class Solution
{
    public:
        int missingNumber(vector<int> &nums)
        {
            int res = 0;
            int len = nums.size();
            res = len * (len + 1) / 2;
            for(int i = 0; i < len; ++i)
                res -= nums[i];
            return res;
        }
};
```

## 318. Maximum Product of Word Lengths
### 解题思路
> * 对于每一个string，使用int的后26为记录string中字符的存在与否；
> * 建立一个vector<int>保存所有字符串的字符信息，使用`&`判断是否有重复的字符；  

### 代码
```
class Solution
{
    public:
        int maxProduct(vector<string> &words)
        {
            int res = 0;
            int len = words.size();
            vector<int> nums(len, 0);
            for(int i = 0; i < len; ++i)
            {
                for(int j = 0; j < words[i].size(); ++j)
                {
                    nums[i] |= 1<<(words[i][j] - 'a');
                }
            }
            for(int i = 0; i < len; ++i)
            {
                for(int j = i+1; j < len; ++j)
                {
                    if(nums[i] & nums[j])
                        continue;
                    else
                        res = max(res, int(words[i].size() * words[j].size()));
                }
            }
            return res;
        }
};
```

## 338. Counting Bits
### 解题思路
> * `Bit Counts: 0->01, 01->0112, 0112->01121223, 01121223->0112122312232334;`
> * 参照上述规律使用DP进行求解即可；

### 代码
```
class Solution
{
    public:
        vector<int> countBits(int num)
        {
            vector<int> res(num+1, 0);
            int start = 0;
            int end = 0;
            for(int i = 1; i < num+1; ++i)
            {
                if(start > end)
                {
                    start = 0;
                    end = i-1;
                }
                res[i] = res[start++] + 1;
            }
            return res;
        }
};
```


  [1]: https://leetcode.com/problems/subsets/
  [2]: https://leetcode.com/problems/single-number/
  [3]: https://leetcode.com/problems/single-number-ii/
  [4]: https://leetcode.com/problems/majority-element/
  [5]: https://leetcode.com/problems/repeated-dna-sequences/
  [6]: https://leetcode.com/problems/reverse-bits/
  [7]: https://leetcode.com/problems/number-of-1-bits/
  [8]: https://leetcode.com/problems/bitwise-and-of-numbers-range/
  [9]: https://leetcode.com/problems/power-of-two/
  [10]: https://leetcode.com/problems/single-number-iii/
  [11]: https://leetcode.com/problems/missing-number/
  [12]: https://leetcode.com/problems/maximum-product-of-word-lengths/
  [13]: https://leetcode.com/problems/counting-bits/