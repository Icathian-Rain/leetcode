# 题解点评 - 438. Find All Anagrams in a String

## 基本信息

- 日期：2026-05-05
- 主题：双指针与滑动窗口 - 固定窗口与频次窗口
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/438.find-all-anagrams-in-a-string.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-01 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `cnt` 记录模式串 `p` 中每个字符还需要多少个。
2. 用 `num` 记录当前还有多少种字符的需求差值不为 `0`。
3. 右指针把 `s[r]` 加入窗口时，对应 `cnt` 减一，并根据它从正到零或从零到负来调整 `num`。
4. 当窗口长度还没达到 `p` 的长度时，继续扩张。
5. 窗口长度达到固定大小后，如果 `num == 0`，说明当前窗口和 `p` 字符频次完全一致，记录左边界。
6. 记录后移出 `s[l]`，把窗口恢复成下一轮固定长度前的状态。

## 用户解法复杂度

- 时间复杂度：`O(|s| + |p|)`
- 空间复杂度：`O(1)`，只使用长度为 26 的频次数组。
- 复杂度来源：初始化扫描一次 `p`，随后每个 `s` 中字符最多进入窗口一次、离开窗口一次。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int m=s.length(), n=p.length();
        vector<int> cnt(26, 0);
        int num=0; // 当前有多少种字符的差值不为 0。
        for(auto ch: p) {
            if(cnt[ch-'a'] == 0) {
                num++; // 新出现一种需要匹配的字符。
            }
            cnt[ch-'a']++;
        }

        vector<int> ans;
        for(int l=0, r=0; r<m; r++) {
            cnt[s[r]-'a']--; // 当前字符进入窗口，抵消一个需求。
            if(cnt[s[r]-'a'] == 0) {
                num--;      // 这一类字符刚好匹配。
            } else if(cnt[s[r]-'a'] == -1) {
                num++;      // 这一类字符从刚好匹配变成窗口中过多。
            }
            if(r+1 < n) {
                continue;   // 固定窗口长度还不够，暂时不能判断。
            }

            if(num == 0) {
                ans.push_back(l);
            }
            cnt[s[l]-'a']++; // 移出左端字符，为下一轮固定窗口做准备。
            if(cnt[s[l]-'a'] == 0) {
                num--;      // 移出后这一类重新刚好匹配。
            } else if(cnt[s[l]-'a'] == 1) {
                num++;      // 移出后这一类变成缺少。
            }
            l++;
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 差值频次数组 | 用 `cnt` 同时表达模式串需求和当前窗口抵消情况。 | 能避免每个窗口都比较 26 个字符，达到线性复杂度。 | 复盘时把 `cnt[x] > 0 / == 0 / < 0` 的含义说清。 |
| 不匹配种类数 | 用 `num` 记录差值不为 0 的字符种类。 | 这是今天最核心的优化点，判断窗口匹配只需 `O(1)`。 | 可以抽成一个小的“更新差值前后状态”模板，减少分支记忆负担。 |
| 固定窗口长度 | 在 `r + 1 < n` 时跳过判断，之后每轮判断再移出左端。 | 能保持被判断的窗口长度正好等于 `p`。 | 推荐显式处理 `p.size() > s.size()`，让边界更直观。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 频次差值维护准确，判断窗口是否匹配为常数时间。 | `num` 的增减分支需要小心，读者要反推“变化前后是否为 0”。 | 很适合固定长度异位词匹配题。 |
| 推荐最优解 | 把差值更新封装成统一逻辑，减少进入和移出窗口时的重复分支。 | 使用 lambda 后代码抽象一点，需要理解 `different` 的含义。 | 适合作为 438/567 共用模板。 |

## 最优解法

1. 用 `diff[c]` 表示字符 `c` 在 `p` 中需要的数量减去当前窗口已有数量。
2. 用 `different` 表示有多少种字符的 `diff` 不为 `0`。
3. 每次修改某个字符差值时，只根据修改前后是否为 `0` 来调整 `different`。
4. 右端加入字符后，如果窗口超过 `p` 的长度，就移出最左端字符。
5. 当窗口长度达到 `p` 的长度且 `different == 0` 时，记录起点。

- 最优时间复杂度：`O(|s| + |p|)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (p.size() > s.size()) {
            return {};
        }

        vector<int> diff(26, 0);
        int different = 0;

        auto addDiff = [&](int idx, int delta) {
            int before = diff[idx];
            int after = before + delta;
            if (before == 0 && after != 0) {
                ++different;
            } else if (before != 0 && after == 0) {
                --different;
            }
            diff[idx] = after;
        };

        for (char ch : p) {
            addDiff(ch - 'a', 1);
        }

        vector<int> ans;
        int windowSize = p.size();
        for (int right = 0; right < (int)s.size(); ++right) {
            addDiff(s[right] - 'a', -1);
            if (right >= windowSize) {
                // 固定窗口超过 p 的长度时，移出最左侧字符。
                addDiff(s[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                ans.push_back(right - windowSize + 1);
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cnt` 是需求差值，`num` 是不匹配字符种类。 | `diff` 和 `different` 表达同一状态。 | 当前状态定义正确，命名可以更明确。 |
| 更新逻辑 | 加入和移出窗口各写一组分支。 | 用统一函数按修改前后是否为 0 更新。 | 抽出差值更新能降低漏改风险。 |
| 边界处理 | 窗口长度不足时跳过判断。 | 先处理 `p` 更长的情况，并用固定窗口下标移出左端。 | 两种都正确，推荐显式写出不可能匹配的边界。 |
| 复杂度 | `O(|s| + |p|)` / `O(1)` | `O(|s| + |p|)` / `O(1)` | 已达到最优。 |

## 下一步建议

进入下一题即可；这题值得重点复盘 `num` 的语义，因为它会直接迁移到 `567. Permutation in String`。

## 后续练习

1. `567. Permutation in String` - 同样判断固定长度窗口是否和目标串频次一致，但只需要返回是否存在。
2. `76. Minimum Window Substring` - 把频次需求从固定长度匹配扩展到覆盖需求。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/438.find-all-anagrams-in-a-string.cpp`
- 新函数名：`findAnagramsOpt`
- 保留用户原实现：是
