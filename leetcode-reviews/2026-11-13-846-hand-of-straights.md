# 题解点评 - 846. Hand of Straights（一手顺子）

## 基本信息

- 日期：2026-11-13
- 主题：第 10 周区间与贪心 - 局部合法性与资源平衡
- 难度：中等
- 本次结果：逻辑推演正确（用户未明确确认测试状态，暂记待验证）
- 对应源码：[src/846.hand-of-straights.cpp](../src/846.hand-of-straights.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/hand-of-straights/)，2026-11-13 查询
- 约束要点：`1 <= hand.length <= 10^4`，`0 <= hand[i] <= 10^9`，`1 <= groupSize <= hand.length`；与 1296. Divide Array in Sets of K Consecutive Numbers 为同一题

## 用户思路概述

1. 若 `n % groupSize != 0` 直接返回 `false`（无法整分）。
2. 排序 `hand`，用 `unordered_map` 统计每张牌的出现次数。
3. 按排序后的顺序遍历：若当前牌 `x` 已被消耗完（不在 map 中）则跳过；否则以 `x` 为起点，连续取 `x, x+1, ..., x+groupSize-1` 各一张——任何一张缺失即返回 `false`，取到则计数减一，减到零时从 map 中删除。
4. 全部牌消耗完则返回 `true`。

## 用户解法复杂度

- 时间复杂度：`O(n log n)`（排序主导；扫描与消耗总计 `O(n)` 摊还）
- 空间复杂度：`O(n)`（哈希表）
- 复杂度来源：排序；每张牌入 map 一次、出 map 一次，遍历排序数组的跳过操作不增加量级。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n=hand.size();
        if(n % groupSize != 0) {
            return false;            // 无法整分成等长组，直接排除
        }
        sort(hand.begin(), hand.end());
        unordered_map<int, int> mp;  // 牌值 -> 剩余张数
        for(auto x: hand) {
            mp[x]++;
        }
        for(auto x: hand) {         // 按升序遍历：保证每次处理的是当前最小起点
            if(mp.find(x) == mp.end()) {
                continue;           // 该牌已被之前的组消耗完
            }
            for(int j=0; j<groupSize; j++) {
                int num = x+j;      // 从最小值 x 开始连续取 groupSize 张
                if(mp.find(num) == mp.end()) {
                    return false;   // 连续结构断链，无法成组
                }
                mp[num]--;
                if(mp[num] == 0) {
                    mp.erase(num); // 计数归零即删除，统一用 find 判存在
                }
            }
        }
        return true;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 贪心方向 | 每次从当前最小剩余牌开始组顺子 | 正确：最小的牌只能作为组内最小值（它没有更小的邻居可依附），必须自己开头，这是本题贪心正确性的全部 | 口头证明"为什么最小牌必须当组头"——反证：它若不在组头，组内需要比它小的牌，不存在 |
| 整除预判 | `n % groupSize != 0` 提前返回 | 正确且必要，避免无意义扫描 | 已达标 |
| 计数归零即删除 | `mp[num] == 0` 时 `erase` | 让"存在性"判断统一为 `find`，避免计数为 0 的假存在 | 已达标；另一种写法是判 `mp[num] > 0`，两者等价 |
| 遍历对象 | 遍历排序后的 `hand` 而非 map | 正确：排序数组保证起点按升序处理；遍历 map（无序）则需改用有序 map | 想清"为什么遍历排序数组是安全的"——重复值被跳过时说明已消耗完 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（排序 + 哈希计数） | `O(n log n)` 标准最优级；起点选择与消耗逻辑清晰 | 排序后遍历有跳过操作，理解上多一步"为什么跳过安全" | 牌值范围大（`10^9`）时必须用哈希/排序，是本题通用解 |
| 有序 map 变体 | 免去显式排序，直接遍历有序键 | `unordered_map` 换 `map` 后常数略大；复杂度同阶 | 纯写法取舍，本次不展开 |
| 计数数组变体 | 常数最小 | 依赖牌值范围小，本题 `10^9` 不可行 | 值域小时才考虑 |

## 最优解法

1. 整除预判；排序并用哈希表计数。
2. 按升序遍历每张牌：计数已尽则跳过；否则以它为组头，向右连续消耗 `groupSize` 张，缺任一张即失败。
3. 全部组消耗成功返回 `true`。
- 关键不变量：每次处理的起点是当前未消耗牌中的最小值；最小值只可能作为组头（无更小邻居），故贪心无损。
- 最优时间复杂度：`O(n log n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = static_cast<int>(hand.size());
        if (n % groupSize != 0) return false; // 无法整分成等长组
        sort(hand.begin(), hand.end());
        unordered_map<int, int> cnt;
        for (int x : hand) cnt[x]++;
        for (int x : hand) {              // 升序遍历保证先处理最小起点
            if (cnt[x] == 0) continue;    // 已被之前的组消耗完
            for (int j = 0; j < groupSize; j++) {
                auto it = cnt.find(x + j);
                if (it == cnt.end() || it->second == 0) return false; // 连续结构断链
                if (--(it->second) == 0) cnt.erase(it);
            }
        }
        return true;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `mp` 计数 + 删除 | 同构 | 已达标 |
| 更新逻辑 | 升序遍历 + 连续消耗 | 相同 | 已达标 |
| 边界处理 | 整除预判、断链返回、重复消耗均正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(n log n)`、空间 `O(n)` | 相同 | 已达最优 |

用户解法与推荐最优解逐行同构，本题完成质量高。

## 下一步建议

- 补一次提交确认：本地推演正确，建议在 LeetCode 提交一次以确认记录状态。
- 复盘任务：写出"最小牌必须当组头"的反证论证（两三句即可），这是本日"局部判断推出全局结论"主题的最后一块。

## 后续练习

1. `1296. Divide Array in Sets of K Consecutive Numbers` - 与本题完全同题，可跳过；真正值得做的是 `659. Split Array into Consecutive Subsequences` - 顺子分组变体，但组长不固定，作为周末拔高。
2. `252. Meeting Rooms` - 第 6 天题单首题，从"资源消耗"转向"事件冲突"，衔接下一日主题。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/846.hand-of-straights.cpp](../src/846.hand-of-straights.cpp)
- 新函数名：`isNStraightHandOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
