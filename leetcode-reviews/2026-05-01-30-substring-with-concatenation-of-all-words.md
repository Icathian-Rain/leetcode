# 题解点评 - 30. Substring with Concatenation of All Words

## 基本信息

- 日期：2026-05-01
- 主题：数组与哈希 - 复杂哈希建模与模拟面试
- 难度：困难
- 本次结果：通过（用户反馈已完成，本地语法检查通过）
- 对应源码：`src/30.substring-with-concatenation-of-all-words.cpp`
- 资料来源：LeetCode 官方题页（题号和题名）+ LeetCode Wiki（题意、约束、难度与典型解法）
- 查询日期：2026-05-01

## 用户思路概述

你先按单词长度 `n` 把字符串切成若干组对齐的 token 流。对每个起点偏移 `i`，你重新建立目标词频 `cnt`，然后维护一个固定包含 `m` 个单词的窗口：进入窗口的 token 让 `cnt[tmp]--`，离开窗口的 token 让 `cnt[tmp]++`。当差分表被完全抵消，也就是 `cnt.size() == 0` 时，当前窗口刚好包含所有单词各一次，于是记录起点。

这是一种“目标词频 - 当前窗口词频”的差分写法，方向是对的。

## 主要问题

- 整体正确性是成立的，但窗口不变量不够直观。标准写法通常维护 `window[word]` 和左边界，遇到非法词直接清空，遇到某个词过量就收缩到合法；你的差分表可以工作，但负数 key 会让调试时更难看出窗口哪里失衡。
- 每个偏移都会重新构建一遍目标词频表。由于单词长度最多 30、`s.length <= 10^4`，这通常不会成为瓶颈；不过目标词频可以提前构建一次，减少重复工作。
- 末尾有几行空白，提交前可以顺手清理。算法题文件不需要追求很重的格式，但保持窗口代码紧凑会更方便复盘。

## 做得好的地方

- 抓住了所有单词长度相同这个关键约束，没有按字符滑动，而是按 `wordLen` 分组扫描。
- 使用差分频次后，重复词天然可处理；例如 `["good","good"]` 这类输入不会被误当成集合题。
- `i + m * n <= len` 的起点剪枝能避免不可能形成完整串联子串的偏移。

## 最优解法

推荐写法是哈希表 + 固定词长滑动窗口。关键不变量是：当前窗口只包含 `words` 中出现过的单词，并且每个单词的窗口频次不超过目标频次。按 `wordLen` 枚举偏移后，右边界每次加入一个单词；如果它不在目标词频表中，就清空窗口；如果它出现过多，就移动左边界直到频次恢复合法。当窗口内单词数等于 `words.size()` 时，左边界就是一个答案。

- 时间复杂度：`O(|s| * wordLen)`，主要来自切分子串
- 空间复杂度：`O(U)`，`U` 为不同单词数量

## 最优解代码

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> target;
        for (const string& word : words) {
            ++target[word];
        }

        int wordCount = words.size();
        int wordLen = words[0].size();
        int totalLen = wordCount * wordLen;
        vector<int> ans;

        if (static_cast<int>(s.size()) < totalLen) {
            return ans;
        }

        for (int offset = 0; offset < wordLen; ++offset) {
            unordered_map<string, int> window;
            int left = offset;
            int count = 0;

            for (int right = offset; right + wordLen <= static_cast<int>(s.size()); right += wordLen) {
                string word = s.substr(right, wordLen);

                if (!target.count(word)) {
                    window.clear();
                    count = 0;
                    left = right + wordLen;
                    continue;
                }

                ++window[word];
                ++count;

                while (window[word] > target[word]) {
                    string removed = s.substr(left, wordLen);
                    --window[removed];
                    --count;
                    left += wordLen;
                }

                if (count == wordCount) {
                    ans.push_back(left);

                    string removed = s.substr(left, wordLen);
                    --window[removed];
                    --count;
                    left += wordLen;
                }
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

你的差分写法已经能表达“窗口词频是否等于目标词频”，这是可用的；标准写法的优势在于窗口始终保持可解释：非法词清空、过量词收缩、合法窗口记录。困难滑窗题里，这种不变量更容易在白板或面试中讲清楚。

## 下一步建议

建议用标准窗口写法重写一遍本题，重点练“非法状态如何恢复合法”。你当前已经知道要按词长分组，下一步就是把收缩条件讲得更稳。

## 后续练习

1. `76. Minimum Window Substring` - 继续训练目标词频和窗口词频的差值关系。
2. `438. Find All Anagrams in a String` - 固定长度窗口的轻量版，适合巩固频次匹配。
