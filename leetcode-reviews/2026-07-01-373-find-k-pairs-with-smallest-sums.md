# 题解点评 - 373. Find K Pairs with Smallest Sums

## 基本信息

- 日期：2026-07-01
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/373.find-k-pairs-with-smallest-sums.cpp`
- 资料来源：本地周计划与源码；尝试联网访问 LeetCode 官方页面但未取得可引用内容
- 查询日期：2026-07-01，信息待官方页面复核

## 用户思路概述

1. 把每个 `nums1[i]` 与 `nums2[0]` 组成的坐标 `(i, 0)` 放入小根堆。
2. 堆的优先级由 `nums1[i] + nums2[j]` 决定。
3. 每次弹出当前和最小的一对数字加入答案。
4. 弹出 `(i, j)` 后，只把同一行的下一个组合 `(i, j + 1)` 放回堆。

## 用户解法复杂度

- 时间复杂度：`O(min(k, m) + k log min(k, m))`
- 空间复杂度：`O(min(k, m))`
- 复杂度来源：初始最多放入 `min(k, m)` 个来源，最多弹出 `k` 次。

## 用户代码注释版

```cpp
using pii = pair<int, int>;
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m=nums1.size(), n=nums2.size();
        auto cmp = [&](const pii& a, const pii& b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        vector<vector<int>> ans;
        for(int i=0; i<min(k, m); i++) {
            pq.push({i, 0}); // 每个 nums1[i] 先只搭配 nums2[0]。
        }
        while(k-->0 && !pq.empty()) {
            auto [x, y] = pq.top(); pq.pop();
            ans.push_back({nums1[x], nums2[y]});
            if(y+1 < n) {
                pq.push({x, y+1}); // 只推进同一个 x 的下一个 y。
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态建模 | 用 `(i, j)` 表示一个组合 | 能避免直接存所有组合 | 复盘时说明每个 `i` 对应一条有序组合链 |
| 候选推进 | 弹出 `(i, j)` 后加入 `(i, j + 1)` | 不会漏掉同一 `i` 下更大的候选 | 这是本题不展开笛卡尔积的关键 |
| 空输入边界 | 原代码依赖 `n > 0` | 若 `nums2` 为空会访问不到合法候选 | 推荐函数中补空数组保护 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 候选扩展顺序正确，复杂度优秀 | 缺少空数组提前返回 | 两个有序数组求前 `k` 小组合 |
| 推荐最优解 | 加上边界保护，结构更稳 | 比较器依赖外部数组，需要保证数组生命周期 | 本题最常用的多路合并写法 |

## 最优解法

1. 如果任一数组为空或 `k == 0`，直接返回空结果。
2. 对每个 `nums1[i]`，先把 `(i, 0)` 作为该来源的首个候选放入堆。
3. 每次弹出全局最小组合。
4. 弹出 `(i, j)` 后，只推进到 `(i, j + 1)`。

- 最优时间复杂度：`O(min(k, m) + k log min(k, m))`
- 最优空间复杂度：`O(min(k, m))`

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        if (nums1.empty() || nums2.empty() || k == 0) {
            return {};
        }

        using State = pair<int, int>;
        auto cmp = [&](const State& a, const State& b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };

        priority_queue<State, vector<State>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < min<int>(k, nums1.size()); ++i) {
            heap.push({i, 0});
        }

        vector<vector<int>> ans;
        while (k-- > 0 && !heap.empty()) {
            auto [i, j] = heap.top();
            heap.pop();
            ans.push_back({nums1[i], nums2[j]});
            // 固定 nums1[i] 后，只推进 nums2 的下一个位置。
            if (j + 1 < nums2.size()) {
                heap.push({i, j + 1});
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `(x, y)` 坐标 | `(i, j)` 坐标 | 当前正确，命名可更语义化 |
| 更新逻辑 | 推进 `(x, y + 1)` | 同样逻辑 | 当前稳定 |
| 边界处理 | 未显式处理空数组 | 提前返回空结果 | 下次组合题先补空输入 |
| 复杂度 | `O(k log min(k, m))` | 同级别 | 重点理解没有展开 `m * n` |

## 下一步建议

补边界测试。建议测 `nums1 = []`、`nums2 = [1]`、`k = 3`，以及 `k` 大于总组合数的情况。

## 后续练习

1. `378. Kth Smallest Element in a Sorted Matrix` - 把每一行视为一个有序来源。
2. `23. Merge k Sorted Lists` - 回看链表来源推进的同构模式。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/373.find-k-pairs-with-smallest-sums.cpp`
- 新函数名：`kSmallestPairsOpt`
- 保留用户原实现：是。
