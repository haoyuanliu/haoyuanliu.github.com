---
title: Partition算法剖析
categories: Algorithm
tags:
  - Algorithm
  - partition
  - LeetCode
abbrlink: 23789
date: 2016-12-18 16:01:12
---

partition算法从字面上就非常好理解，就是分割算法嘛！简单讲就是可以把数组按照一定的分成几个部分，其中最常见的就是快速排序中使用的partition算法，这是一个二分partition算法，将整个数组分解为小于某个数和大于某个数的两个部分，然后递归进行排序算法。
上述只是二分partition算法，我们还会使用三分partition算法，三分partition也有这非常重要的应用。往往我们更多的关注点是快速排序算法等各种算法，以及时间复杂度等这些东西，今天我们专门讨论一下partition分割算法的一些应用。

<!--more-->

## 二分 Partition算法
二分partition算法是我们最常使用的，尤其在快速排序中使用最为常见。常见的partition算法有如下两种实现思路：

### 思路I

#### 算法思路
> * 使用第一个数组元素作为枢轴点，即为pivot；
> * 使用一个指针去扫描整个数组，凡是小于pivot的全部放到数组左端；
> * 最后讲pivot放到数组中间的位置，pivot左边全部都是小于他的数字，右边反之，最后返回pivot的位置信息；

#### 代码
```
int partition(vector<int> &nums, int begin, int end)
{
    int pivot = nums[begin];
    int pos = begin;
    for(int i = begin+1; i < end; ++i)
    {
        if(nums[i] <= pivot)
            swap(nums[++pos],nums[i]);
    }
    swap(nums[pos], nums[begin]);
    return pos;
}
```

### 思路II
#### 算法思路
> * 就如快速排序中最常使用的那样，使用两个指针分别从头部和尾部进行扫描，头部遇到大于pivot的数和尾部遇到小于pivot的数进行交换；
> * 使用了两个指针，效率更高一点；

#### 代码
```
int partition(vector<int> &nums, int begin, int end)
{
    int pivot = nums[begin];
    while(begin < end)
    {
        while(begin < end && nums[--end] >= pivot);
        nums[begin] = nums[end];
        while(begin < end && nums[++begin] <= pivot);
        nums[end] = nums[begin];
    }
    nums[begin] = pivot;
    return begin;
}
```

## 二分partition算法应用
### 快速排序算法
经典的快速排序算法，直接上代码：

#### 代码
```
void quickSort(vector<int> &nums, int begin, int end)
{
    if(end - begin <= 1)
        return;
    int mid = partition(nums, begin, end);

    quickSort(nums, begin, mid);
    quickSort(nums, mid, end);
}
```

### 数组第K大数值查询
这也是LeetCode中的一道例题，非常适合使用partition算法进行解决，问题链接[215. Kth Largest Element in an Array][1]！
#### 解题思路
> * 首先可以通过排序进行求解，简单暴力；
> * 不断使用partition算法进行迭代查找；

#### 代码
```
class Solution
{
    public:
        int findKthLargest(vector<int> &nums, int k)
        {
            int len = nums.size();
            int res = 0;
            int left = 0;
            int right = len;
            while(left < right)
            {
                int pos = partition(nums, left, right);
                if(pos == len-k)
                {
                    res = nums[pos];
                    break;
                }
                else if(pos < len-k)
                    left = pos+1;
                else
                    right = pos;
            }
            return res;
        }
        int partition(vector<int> &nums, int begin, int end)
        {
            int pivot = nums[begin];
            while(begin < end)
            {
                while(begin < end && nums[--end] >= pivot);
                nums[begin] = nums[end];
                while(begin < end && nums[++begin] <= pivot);
                nums[end] = nums[begin];
            }
            nums[begin] = pivot;
            return begin;
        }
};
```

## 三分paitition算法
三分partition算法，顾名思义，也就是将数组按照规则分为三个部分，比如非常经典的国旗问题[Dutch national flag problem][2]，就是要给定的红、白、蓝三色随机颜色小球按照红、白、蓝的顺序进行排序，利用partition算法，使用一个指针进行扫描，红色的小球就用swap()放到左边，白色的保持位置不变，蓝色的同样使用swap()放到右边，最后就得到要求的序列了。

### Dutch National Flag Problem
LeetCode中有恰好有这么一个题：[75. Sort Colors][3]！

#### 解题思路
> * 就使用三分partition算法进行求解就可以了！

#### 代码
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

### 进阶应用
#### LeetCode 324. Wiggle Sort II
LeetCode中的第324题中也同样可以使用三分partition算法，该题的discuss中，StefanPochmann大神提出一种O(n)+O(1)复杂度的高效算法，原链接为：
[324. Wiggle Sort II][4]
[Discuss][5]！

#### 解题思路
> * 使用partition算法获取数组的中位数，这个思路同找第k大的数，这里作者用了c++中的nth_element()函数；
> * 使用宏定义的方式`#define A(i) nums[(1+2*(i)) % (n|1)]`，`A()`的前半部分对应nums中下标为奇数的元素，后半部分为偶数，即`奇数` +　`偶数`；
> * 使用三分partition算法对A()进行排序，使其前半部分大于后半部分，即在nums中`奇数部分` > `偶数部分`；
> * 最终达到的效果为 `0` < `1` > `2` < `3` > `4` < `5` ...
> * 注意这里需要的是`奇数`>`偶数`，所以进行partition的时候大于pivot枢轴值的要放到前面；

`#define A(i) nums[(1+2*(i)) % (n|1)]`的作用如下所示：
假设有0, 1, 2, 3, 4, 5, 6, 7, 8, 9共10个数据，则使用`A()`进行映射之后的结果为：
`A(0)` -> `nums[1]`.
`A(1)` -> `nums[3]`.
`A(2)` -> `nums[5]`.
`A(3)` -> `nums[7]`.
`A(4)` -> `nums[9]`.
`A(5)` -> `nums[0]`.
`A(6)` -> `nums[2]`.
`A(7)` -> `nums[4]`.
`A(8)` -> `nums[6]`.
`A(9)` -> `nums[8]`.

#### 代码
```
class Solution
{
    public:
        void wiggleSort(vector<int>& nums) 
        {
            int n = nums.size();
    
            // Find a median.
            auto midptr = nums.begin() + n / 2;
            nth_element(nums.begin(), midptr, nums.end());
            int mid = *midptr;
    
            // Index-rewiring.
            #define A(i) nums[(1+2*(i)) % (n|1)]

            // 3-way-partition-to-wiggly in O(n) time with O(1) space.
            int i = 0, j = 0, k = n - 1;
            while (j <= k) 
            {
                if (A(j) > mid)
                    swap(A(i++), A(j++));
                else if (A(j) < mid)
                    swap(A(j), A(k--));
                else
                    j++;
            }
        }
};
```


  [1]: https://leetcode.com/problems/kth-largest-element-in-an-array/
  [2]: https://en.wikipedia.org/wiki/Dutch_national_flag_problem#Pseudocode
  [3]: https://leetcode.com/problems/sort-colors/
  [4]: https://leetcode.com/problems/wiggle-sort-ii/
  [5]: https://discuss.leetcode.com/topic/32929/o-n-o-1-after-median-virtual-indexing