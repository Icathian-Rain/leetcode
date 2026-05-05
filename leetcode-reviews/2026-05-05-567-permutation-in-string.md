# 题解点评 - 567. Permutation in String

## 基本信息

- 日期：2026-05-05
- 主题：双指针与滑动窗口 - 固定窗口与频次窗口
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/567.permutation-in-string.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-01 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `cnt` 初始化 `s1` 中每个字符的需求次数。
2. 用 `num` 记录当前还有多少种字符频次没有匹配。
3. 扫描 `s2`，右指针每加入一个字符，就让对应需求减一。
4. 当窗口长度小于 `s1` 时，只扩张不判断。
5. 窗口长度达到 `s1` 后，如果 `num == 0`，说明存在一个排列作为 `s2` 的子串，直接返回 `true`。
6. 如果当前窗口不匹配，就移出左端字符，继续检查下一个等长窗口。

## 用户解法复杂度

- 时间复杂度：`O(|s1| + |s2|)`
- 空间复杂度：`O(1)`，只使用 26 个小写字母的频次数组。
- 复杂度来源：初始化扫描 `s1`，随后 `s2` 中每个字符最多进入和离开固定窗口一次。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n=s1.length(), m=s2.length();
        vector<int> cnt(26, 0);
        int num=0; // 当前差值不为 0 的字符种类数。
        for(auto ch: s1) {
            if(cnt[ch-'a'] == 0) {
                num++;
            }
            cnt[ch-'a']++;
        }

        for(int l=0, r=0; r<m; r++) {
            cnt[s2[r]-'a']--; // 右端字符进入窗口，抵消一个需求。
            if(cnt[s2[r]-'a'] == 0) {
                num--;
            } else if(cnt[s2[r]-'a'] == -1) {
                num++;
            }

            if(r+1 < n) continue; // 窗口长度不足 s1，暂时不能形成排列。

            if(num == 0) return true;

            cnt[s2[l]-'a']++; // 移出左端，准备检查下一个固定长度窗口。
            if(cnt[s2[l]-'a'] == 0) {
                num--;
            } else if(cnt[s2[l]-'a'] == 1) {
                num++;
            }
            l++;
        }
        return false;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 与 438 的关系 | 基本复用了 `cnt + num` 的固定窗口匹配模板。 | 迁移非常好，输出从“所有起点”变成“是否存在”也处理正确。 | 复盘时把 438 和 567 放一起讲，区别只在答案记录方式。 |
| 固定窗口判断 | 只在窗口长度达到 `s1` 后判断。 | 避免短窗口误判为排列。 | 可以显式写 `if (s1.size() > s2.size()) return false;`，让边界更清楚。 |
| 状态维护 | 加入和移出窗口时都正确维护 `num`。 | 保证判断 `num == 0` 是常数时间。 | 后续可以抽出更新函数，减少重复分支。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 直接继承 438 模板，逻辑正确，能提前返回。 | `num` 更新分支重复，边界条件可以更显式。 | 适合固定窗口排列存在性判断。 |
| 推荐最优解 | 统一差值更新逻辑，和 438 形成同一份模板。 | lambda 写法稍抽象，但可维护性更强。 | 适合把固定窗口频次题整理成长期模板。 |

## 最优解法

1. 如果 `s1` 长于 `s2`，直接返回 `false`。
2. 用 `diff` 记录 `s1` 需求减去当前窗口数量。
3. 用 `different` 记录差值不为 `0` 的字符种类。
4. 扫描 `s2`，加入右端字符；窗口超过 `s1` 长度时移出左端字符。
5. 当窗口长度达到 `s1` 且 `different == 0` 时返回 `true`。

- 最优时间复杂度：`O(|s1| + |s2|)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) {
            return false;
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

        for (char ch : s1) {
            addDiff(ch - 'a', 1);
        }

        int windowSize = s1.size();
        for (int right = 0; right < (int)s2.size(); ++right) {
            addDiff(s2[right] - 'a', -1);
            if (right >= windowSize) {
                // 始终只保留和 s1 等长的窗口。
                addDiff(s2[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                return true;
            }
        }

        return false;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cnt` 和 `num` 表示频次差异。 | `diff` 和 `different` 表示同一件事。 | 命名可以更贴近“差值”语义。 |
| 更新逻辑 | 加入和移出窗口分别处理 `0/-1/1` 变化。 | 统一根据修改前后是否为 0 更新。 | 把重复分支收束成一个更新函数。 |
| 边界处理 | 短窗口不判断，最终返回 `false`。 | 开头先排除 `s1` 更长的情况。 | 显式边界更利于面试讲解。 |
| 复杂度 | `O(|s1| + |s2|)` / `O(1)` | `O(|s1| + |s2|)` / `O(1)` | 已达到最优。 |

## 下一步建议

进入下一题即可；这题的核心是确认你已经能把 438 的“记录所有匹配窗口”迁移成“找到一个就返回”。

## 后续练习

1. `438. Find All Anagrams in a String` - 回看同模板下不同输出形式。
2. `424. Longest Repeating Character Replacement` - 继续练频次窗口，但窗口长度不再固定。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/567.permutation-in-string.cpp`
- 新函数名：`checkInclusionOpt`
- 保留用户原实现：是
