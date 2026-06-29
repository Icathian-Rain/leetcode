# 题解点评 - 215. Kth Largest Element in an Array

## 基本信息

- 日期：2026-06-29
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/215.kth-largest-element-in-an-array.cpp`
- 资料来源：本地周计划与源码；尝试联网访问 LeetCode 官方页面但未取得可引用内容
- 查询日期：2026-06-29，信息待官方页面复核

## 用户思路概述

1. 写了快速选择方案 `s1`：随机选择基准，把数组划分后寻找下标 `n - k`。
2. 写了堆方案 `s2`：维护一个大小不超过 `k` 的小根堆。
3. 每加入一个数后，如果堆大小超过 `k`，就弹出最小值。
4. 最终堆中保留最大的 `k` 个数，堆顶就是第 `k` 大。

## 用户解法复杂度

- 时间复杂度：当前提交的 `s2` 为 `O(n log k)`；`s1` 平均 `O(n)`，最坏 `O(n^2)`
- 空间复杂度：当前提交的 `s2` 为 `O(k)`；`s1` 原地划分为 `O(1)`
- 复杂度来源：`s2` 中每个元素最多入堆一次，堆大小维持在 `k`。

## 用户代码注释版

```cpp
class Solution {
public:
    int partition(vector<int>& nums, int l, int r) {
        int randomIndex = l + rand() % (r - l + 1);
        swap(nums[randomIndex], nums[r]);
        int pivot = nums[r];
        int i=l;
        for(int j=l; j<r; j++) {
            if(nums[j] <= pivot) { // 小于等于 pivot 的元素放到左侧。
                swap(nums[i], nums[j]);
                i++;
            }
        }
        swap(nums[i], nums[r]);
        return i; // pivot 的最终有序位置。
    }

    int s2(vector<int>& nums, int k){
        priority_queue<int, vector<int>, greater<int>> pq; // 保留当前最大的 k 个数。
        for(int num : nums) {
            pq.push(num);
            if(pq.size() > k) {
                pq.pop(); // 弹掉最大的 k 个之外的最小候选。
            }
        }
        return pq.top(); // 最大的 k 个数里最小的一个，就是第 k 大。
    }

    int findKthLargest(vector<int>& nums, int k) {
        return s2(nums, k);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 方案取舍 | 同时写了快速选择和堆 | 说明你已经意识到本题不只有排序一种入口 | 面试复盘时主动说明为什么本周选择堆方案 |
| 堆顶语义 | 小根堆保留前 `k` 大 | 正确得到第 `k` 大 | 和 `703` 归为同一模板 |
| 随机化细节 | `srand(time(nullptr))` 放在算法函数内 | 多次调用时随机种子质量一般，但 LeetCode 单次调用影响不大 | 后续可以使用 `<random>` 或直接专注堆写法 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户堆解法 | 稳定、好写、符合本周主题 | 时间不是理论平均最优 | `k` 较小或需要和数据流题统一模板时 |
| 快速选择 | 平均时间 `O(n)`，空间 `O(1)` | 最坏情况可能退化，实现边界更敏感 | 静态数组、追求平均线性时间时 |
| 推荐最优解 | 本次推荐固定大小堆，迁移价值高 | 比快速选择多 `log k` 因子 | 本周堆主题和 Top K 题型复盘 |

## 最优解法

1. 建立小根堆保存当前最大的 `k` 个元素。
2. 遍历数组，把每个元素加入堆。
3. 一旦堆大小超过 `k`，弹出堆顶，也就是当前候选中最小的那个。
4. 遍历结束后，堆顶就是整体第 `k` 大。

- 最优时间复杂度：堆方案 `O(n log k)`；快速选择平均可达 `O(n)`
- 最优空间复杂度：堆方案 `O(k)`；快速选择为 `O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int num : nums) {
            heap.push(num);
            // 始终只保留当前最大的 k 个数，堆顶就是第 k 大。
            if (heap.size() > k) {
                heap.pop();
            }
        }

        return heap.top();
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `pq` 小根堆 | `heap` 小根堆 | 当前定义正确，命名可更语义化 |
| 更新逻辑 | 入堆后超过 `k` 就弹出 | 同样逻辑 | 当前已经稳定 |
| 边界处理 | 依赖题目保证 `1 <= k <= n` | 同样依赖题目保证 | 可在复盘中说明约束保证无需额外判断 |
| 复杂度 | `O(n log k)` | `O(n log k)` | 能进一步说出快速选择的平均 `O(n)` 取舍 |

## 下一步建议

做跟练题。你已经掌握“固定大小小根堆”的基本写法，下一步要把候选从数字扩展到频次、距离、字符串等复合优先级。

## 后续练习

1. `347. Top K Frequent Elements` - 从频次统计结果中维护 Top K。
2. `973. K Closest Points to Origin` - 把比较依据改成距离。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/215.kth-largest-element-in-an-array.cpp`
- 新函数名：`findKthLargestOpt`
- 保留用户原实现：是。
