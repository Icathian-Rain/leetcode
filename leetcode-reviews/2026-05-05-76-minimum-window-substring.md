# 题解点评 - 76. Minimum Window Substring

## 基本信息

- 日期：2026-05-05
- 主题：双指针与滑动窗口 - 覆盖需求与窗口收缩加练
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/76.minimum-window-substring.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-01 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `diff` 表示目标串 `t` 的需求数量减去当前窗口已有数量。
2. 用 `different` 记录还有多少种字符的需求没有被满足。
3. 先把 `t` 中字符加入 `diff`，建立覆盖需求。
4. 右指针扫描 `s`，每加入一个字符就减少对应需求。
5. 当 `different == 0` 时，当前窗口已经覆盖 `t`，记录更短答案并不断移出左端，直到窗口刚好失效。
6. 最后根据是否记录过答案返回最小覆盖子串或空串。

## 用户解法复杂度

- 时间复杂度：`O(|s| + |t|)`
- 空间复杂度：`O(1)`，使用固定大小为 256 的频次数组。
- 复杂度来源：初始化扫描一次 `t`，随后 `s` 中每个字符最多进入窗口一次、离开窗口一次。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int m=s.length(), n=t.length();
        vector<int> diff(256, 0);
        int different = 0; // 仍有缺口的字符种类数。
        auto addDiff = [&](int idx, int delta) {
            int before = diff[idx];
            diff[idx] = diff[idx] + delta;
            int after = diff[idx];
            if(before == 0 && after > 0) {
                different++; // 从不缺变成缺少。
            } else if(before > 0 && after == 0) {
                different--; // 某一类字符刚好被满足。
            }
        };

        for(auto ch: t) {
            addDiff(ch, 1); // 建立 t 的覆盖需求。
        }

        int len=m+1;
        int ansL=-1;

        for(int l=0, r=0; r<m; r++) {
            addDiff(s[r], -1); // 右端字符进入窗口，抵消一个需求。
            while(different == 0) {
                // 当前窗口已经覆盖 t，先记录，再尝试缩短。
                if(r-l+1 < len) {
                    len = r-l+1;
                    ansL = l;
                }
                addDiff(s[l], 1); // 移出左端，可能让窗口重新缺少某个字符。
                l++;
            }
        }
        if(ansL == -1) return "";
        return s.substr(ansL, len);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 覆盖需求建模 | 用 `diff > 0` 表示当前窗口还缺该字符。 | 这是覆盖型窗口最稳的状态定义，能处理重复字符。 | 复盘时重点区分“缺少”和“多余”，`diff < 0` 只是窗口冗余。 |
| 满足条件 | 用 `different == 0` 判断所有需求都已覆盖。 | 避免每次扫描整张频次数组，复杂度最优。 | 可以把变量名换成 `missingTypes`，语义更贴近本题。 |
| 答案更新时机 | 在移出左端前记录候选答案。 | 正确，因为移出左端可能立刻破坏覆盖条件。 | 覆盖型最小窗口都要先记录、再收缩。 |
| 字符下标 | 使用 `vector<int>(256)` 支持更一般字符集。 | 比只开 52 或 128 更稳，但 `char` 符号性在 C++ 中有潜在坑。 | 推荐转成 `unsigned char` 后再作为下标。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 频次差值、满足种类数和收缩时机都正确，已经是线性最优思路。 | `n` 未使用；`char` 直接作为下标在非 ASCII 扩展场景下不够严谨。 | 适合覆盖型最小窗口，尤其是目标串可能包含重复字符的题。 |
| 推荐最优解 | 保留同一思路，改用更语义化命名，并用 `unsigned char` 规避下标风险。 | 与用户代码差别不大，主要提升表达和鲁棒性。 | 可作为本题直接提交写法。 |

## 最优解法

1. 用 `diff[c]` 表示字符 `c` 还缺多少个；小于等于 `0` 表示当前窗口已经不缺这个字符。
2. 用 `missingTypes` 记录 `diff[c] > 0` 的字符种类数。
3. 右端扩张时减少对应需求；如果某类需求从正数降到 `0`，说明它被满足。
4. 当 `missingTypes == 0`，当前窗口覆盖 `t`，先更新最短答案，再移出左端。
5. 左端移出时如果某类需求从 `0` 变回正数，窗口重新失效，停止收缩。

- 最优时间复杂度：`O(|s| + |t|)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> diff(256, 0);
        int missingTypes = 0;

        auto addDiff = [&](unsigned char ch, int delta) {
            int before = diff[ch];
            int after = before + delta;
            if (before == 0 && after > 0) {
                ++missingTypes;
            } else if (before > 0 && after == 0) {
                --missingTypes;
            }
            diff[ch] = after;
        };

        for (unsigned char ch : t) {
            addDiff(ch, 1);
        }

        int bestLen = (int)s.size() + 1;
        int bestLeft = -1;
        int left = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            addDiff((unsigned char)s[right], -1);

            while (missingTypes == 0) {
                // 当前窗口已覆盖 t，先记录答案，再尝试移出左端缩短窗口。
                if (right - left + 1 < bestLen) {
                    bestLen = right - left + 1;
                    bestLeft = left;
                }
                addDiff((unsigned char)s[left], 1);
                ++left;
            }
        }

        return bestLeft == -1 ? "" : s.substr(bestLeft, bestLen);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `diff` 是需求差值，`different` 是仍有缺口的种类数。 | `diff` 和 `missingTypes` 表达同一状态。 | 思路已正确，命名可更贴近覆盖需求。 |
| 更新逻辑 | 用 `addDiff` 统一处理需求变化。 | 同样用统一函数，并调整参数类型。 | 这是很好的抽象，建议保留。 |
| 边界处理 | 无答案返回空串，目标重复字符可覆盖。 | 同样覆盖，并规避负下标风险。 | 删掉未使用的 `n`，把字符下标转成 `unsigned char`。 |
| 复杂度 | `O(|s| + |t|)` / `O(1)` | `O(|s| + |t|)` / `O(1)` | 已达到最优。 |

## 下一步建议

这题可以作为今天的重点复盘题。建议把“覆盖型窗口：满足后先记录，再不断收缩到失效”整理成一句固定口径，之后遇到最短覆盖、最小区间类题会很有用。

## 后续练习

1. `727. Minimum Window Subsequence` - 题名相近但约束不同，适合训练先辨题再套模板。
2. `992. Subarrays with K Different Integers` - 继续练可变窗口，但目标从覆盖最短转成恰好计数。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/76.minimum-window-substring.cpp`
- 新函数名：`minWindowOpt`
- 保留用户原实现：是
