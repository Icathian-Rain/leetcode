# 题解点评 - 767. Reorganize String

## 基本信息

- 日期：2026-07-09
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/767.reorganize-string.cpp`
- 资料来源：LeetCode 中国官方题目页标题与本地周计划；实现点评基于本地源码
- 查询日期：2026-07-09

## 用户思路概述

1. 先统计每个字符出现次数，并找到最高频字符。
2. 如果最高频次数超过 `(n + 1) / 2`，说明无论怎么排都会相邻，直接返回空串。
3. `s1` 使用大根堆，每次取出两个最高频字符交替放入答案。
4. `s2` 先把最高频字符填入偶数位，再把剩余字符继续按偶数位、奇数位填充。
5. 最终公开函数选择 `s2` 作为提交方案。

## 用户解法复杂度

- 时间复杂度：`O(n + 26)`，固定字符集下为 `O(n)`。
- 空间复杂度：`O(26 + n)`，其中输出字符串占 `O(n)`。
- 复杂度来源：统计频次、填充答案数组，各字符只被处理常数次。

## 用户代码注释版

```cpp
class Solution {
public:
    string s2(string s) {
        vector<int> cnt(26, 0);
        for(auto ch: s) {
            cnt[ch-'a']++; // 统计字符频次。
        }
        int maxCnt = 0;
        char maxch = 'a';
        for(int i=0; i<26; i++) {
            if(cnt[i] > maxCnt) {
                maxCnt = cnt[i];
                maxch = 'a'+i; // 找到最高频字符。
            }
        }

        int n=s.length();
        if(maxCnt > (n+1)/2) {
            return ""; // 最高频字符超过可用非相邻槽位，无法重构。
        }
        string ans(n, ' ');
        int idx = 0;
        while(cnt[maxch-'a'] > 0) {
            ans[idx] = maxch; // 先把最高频字符放在偶数位。
            idx+=2;
            cnt[maxch-'a']--;
        }
        for(int i=0; i<26; i++) {
            while(cnt[i] > 0) {
                if(idx >= n) {
                    idx = 1; // 偶数位用完后切到奇数位。
                }
                ans[idx] = char('a'+i);
                idx+=2;
                cnt[i]--;
            }
        }
        return ans;
    }

    string reorganizeString(string s) {
        return s2(s);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 可行性判断 | 使用 `maxCnt > (n + 1) / 2` | 正确提前排除必然相邻的情况 | 这类重排题先判断最高频上限 |
| 构造策略 | 最高频字符先填偶数位 | 能最大化隔开最危险的字符 | 复盘时画出偶数槽位数量为 `(n + 1) / 2` |
| 多方案意识 | 同时写了堆模拟和位置填充 | 很好地比较了模拟和直接构造 | 面试时说明为什么最终选择 `s2` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户 `s1` 堆解法 | 直观，每次取两个最高频字符 | 代码更长，仍需处理最后剩余字符 | 字符种类多或规则更动态时 |
| 用户 `s2` 填充解法 | 简洁，固定字符集下复杂度更好 | 需要理解最高频字符先占偶数位的正确性 | 本题小写字母固定且只限制相邻不同 |
| 推荐最优解 | 与 `s2` 同思路，命名和边界说明更清楚 | 不如堆模拟直观 | 本题最稳的提交写法 |

## 最优解法

1. 统计字符频次并找出最高频字符。
2. 若最高频超过 `(n + 1) / 2`，返回空串。
3. 先把最高频字符放入偶数下标。
4. 再把其他字符依次放入剩余偶数位，偶数位用完后切到奇数位。
5. 因为最高频字符已经被隔开，剩余字符按槽位填充不会破坏相邻限制。

- 最优时间复杂度：`O(n + 26)`
- 最优空间复杂度：`O(n + 26)`

### 最优解代码

```cpp
class Solution {
public:
    string reorganizeString(string s) {
        vector<int> freq(26, 0);
        for (char ch : s) {
            ++freq[ch - 'a'];
        }

        int maxFreq = 0;
        char maxChar = 'a';
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
                maxChar = static_cast<char>('a' + i);
            }
        }

        int n = static_cast<int>(s.size());
        if (maxFreq > (n + 1) / 2) {
            return "";
        }

        string ans(n, ' ');
        int index = 0;
        while (freq[maxChar - 'a'] > 0) {
            ans[index] = maxChar;
            index += 2;
            --freq[maxChar - 'a'];
        }

        for (int i = 0; i < 26; ++i) {
            while (freq[i] > 0) {
                if (index >= n) {
                    index = 1;
                }
                ans[index] = static_cast<char>('a' + i);
                index += 2;
                --freq[i];
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cnt`、`maxCnt`、`maxch` | `freq`、`maxFreq`、`maxChar` | 当前正确，命名可统一英文语义 |
| 更新逻辑 | 先填最高频，再填剩余字符 | 同样逻辑 | 当前稳定 |
| 边界处理 | 最高频超过上限返回空 | 同样覆盖 | 继续保持先判可行性 |
| 复杂度 | `O(n)` | `O(n)` | 已经很好 |

## 下一步建议

做跟练题。建议复做一次堆方案，专门观察“暂时不能立即再选刚用过的字符”这个状态如何表达。

## 后续练习

1. `621. Task Scheduler` - 回看只求最短时间时如何用频次公式。
2. `358. Rearrange String k Distance Apart` - 把相邻限制扩展到距离为 `k` 的冷却限制。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/767.reorganize-string.cpp`
- 新函数名：`reorganizeStringOpt`
- 保留用户原实现：是。
