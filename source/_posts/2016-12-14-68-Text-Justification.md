---
title: 68 Text Justification
categories: LeetCode
tags:
  - LeetCode
abbrlink: 23107
date: 2016-12-14 10:09:20
---

### 解题思路

> * 将单词分组打出，每组长度为L；
> * 除了最后一行，单词需要左右对齐，平铺效果，中间以空格均匀填充；
> * 最后一行，总长度也是L，但是要求左对齐，以一个空格隔开即可；

<!--more-->


### 代码
```
class Solution
{
    public:
        vector<string> fullJustify(vector<string> &words, int maxWidth)
        {
            int len = words.size();
            vector<string> res;
            vector<string> temp;
            string str;
            int count = 0;
            int totalLen = 0;
            for(int i = 0; i < len; ++i)
            {
                if(count + totalLen + words[i].size() > maxWidth)
                {
                    str = "";
                    str += temp[0];
                    if(count == 1)
                    {
                        str += string(maxWidth - totalLen, ' ');
                    }
                    else if(count == 2)
                    {
                        str += string(maxWidth - totalLen, ' ');
                        str += temp[1];
                    }
                    else
                    {
                        int block = (maxWidth - totalLen) / (count - 1);
                        int last = maxWidth - totalLen - block * (count - 1);
                        for(int j = 1; j < count; ++j)
                        {
                            str += string(block, ' ');
                            if(last-- > 0)
                                str += ' ';
                            str += temp[j];
                        }
                    }
                    res.push_back(str);
                    temp.clear();
                    temp.push_back(words[i]);
                    count = 1;
                    totalLen = words[i].size();
                }
                else
                {
                    temp.push_back(words[i]);
                    count++;
                    totalLen += words[i].size();
                }
            }
            if(count)
            {
                str = "";
                str += temp[0];
                for(int j = 1; j < temp.size(); ++j)
                {
                    str += ' ';
                    str += temp[j];
                }
                str += string(maxWidth - totalLen - count + 1, ' ');
                res.push_back(str);
            }
            return res;
        }
};

```



