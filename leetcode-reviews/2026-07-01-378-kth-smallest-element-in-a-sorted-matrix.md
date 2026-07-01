# 题解点评 - 378. Kth Smallest Element in a Sorted Matrix

## 基本信息

- 日期：2026-07-01
- 主题：堆与优先队列
- 难度：中等
- 本次结果：通过倾向
- 对应源码：`src/378.kth-smallest-element-in-a-sorted-matrix.cpp`
- 资料来源：本地周计划与源码；尝试联网访问 LeetCode 官方页面但未取得可引用内容
- 查询日期：2026-07-01，信息待官方页面复核

## 用户思路概述

1. 把矩阵每一行都看成一个有序来源。
2. 初始时将每一行的第 `0` 列坐标加入小根堆。
3. 每次弹出当前最小坐标，并把同一行的下一个坐标加入堆。
4. 弹出 `k - 1` 次后，堆顶就是第 `k` 小元素。

## 用户解法复杂度

- 时间复杂度：`O((n + k) log n)`
- 空间复杂度：`O(n)`
- 复杂度来源：初始放入 `n` 行首元素，之后弹出并推进 `k - 1` 次。

## 用户代码注释版

```cpp
using pii = pair<int, int>;
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        auto cmp = [&](const pii& a, const pii& b) {
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        int m=matrix.size(), n=matrix[0].size();
        for(int i=0; i<m; i++) {
            pq.emplace(i, 0); // 每一行先放入最左侧元素。
        }

        for(int i=0;i<k-1; i++) {
            auto [x, y] = pq.top(); pq.pop();
            if(y+1 != n) {
                pq.emplace(x, y+1); // 推进同一行的下一个元素。
            }
        }

        auto [x, y] = pq.top();
        return matrix[x][y];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 行来源建模 | 每行放一个当前候选 | 正确复用多路合并模板 | 复盘时说清矩阵的行、列都有序，但堆解法主要用行有序 |
| 第 k 小定位 | 弹出 `k - 1` 次后取堆顶 | 正确避免多弹一次 | 这个边界值得单独记 |
| 方案取舍 | 使用堆推进 | 符合本周主题 | 本题也常用值域二分，适合和堆方案对比 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户堆解法 | 直观，和多路合并模板一致 | 当 `k` 很大时会弹出很多次 | 需要按顺序产生较小元素时 |
| 推荐最优解 | 值域二分能利用行列都有序，复杂度不直接依赖 `k` | 思维跳跃比堆方案更大 | `n x n` 有序矩阵查第 `k` 小值 |

## 最优解法

1. 在矩阵最小值和最大值之间二分答案值。
2. 对每个候选值 `mid`，统计矩阵中 `<= mid` 的元素个数。
3. 如果个数不少于 `k`，说明第 `k` 小不大于 `mid`，收缩右边界。
4. 否则收缩左边界到 `mid + 1`。

- 最优时间复杂度：`O(n log V)`，其中 `V` 是值域范围。
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
    int countLessEqual(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int row = n - 1, col = 0;
        int count = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] <= target) {
                // 当前列从 0 到 row 都不大于 target。
                count += row + 1;
                ++col;
            } else {
                --row;
            }
        }
        return count;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix.front().front();
        int right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (countLessEqual(matrix, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 堆中保存矩阵坐标 | 二分保存候选答案值 | 学会在“输出顺序”和“答案判定”之间切换 |
| 更新逻辑 | 弹出后推进同一行 | 根据计数收缩值域 | 二分方案更依赖单调性判断 |
| 边界处理 | `k - 1` 次后取堆顶 | `left == right` 时返回 | 两者边界都要能口述 |
| 复杂度 | `O((n + k) log n)` | `O(n log V)` | `k` 大时二分更稳定 |

## 下一步建议

做方案对比复盘。堆解法作为本周模板要保留，但这题建议再手写一遍值域二分，训练“有序矩阵 + 第 k 小”的另一条入口。

## 后续练习

1. `668. Kth Smallest Number in Multiplication Table` - 继续练习按答案值计数。
2. `373. Find K Pairs with Smallest Sums` - 回到堆式多路推进，比较两类思路。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/378.kth-smallest-element-in-a-sorted-matrix.cpp`
- 新函数名：`kthSmallestOpt`
- 保留用户原实现：是。
